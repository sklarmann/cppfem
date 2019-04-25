/*
 * Solutionstate.h
 *
 *  Created on: 08.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <vector>

#include <solver/GenericSolutionState.h>
#include <solver/StaticSolutionState.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>

#include <fstream>

#include <equations/DofStatus.h>
#include <equations/DegreeOfFreedom.h>
#include <equations/EquationHandler.h>

#include <loads/LoadList.h>
#include <loads/PropfunctionHandler.h>

#include <solver/GenericSolver.h>


#include <Eigen/SparseCore>
#include <Eigen/Dense>


#ifdef USE_SPECTRA
#include <GenEigsSolver.h>
#include <MatOp/SparseGenMatProd.h>
#include <SymEigsSolver.h>
#include <SymEigsShiftSolver.h>
#include <GenEigsRealShiftSolver.h>
#include <MatOp/SparseSymShiftSolve.h>
#include <MatOp/SparseSymShiftSolve.h>
#include <MatOp/SparseGenRealShiftSolve.h>
#endif // USE_SPECTRA



#include <iostream>



namespace FEMProject {

	template<typename prec,typename uint>
	StaticSolutionState<prec,uint>::StaticSolutionState(PointerCollection<prec, uint> *pointers) : GenericSolutionState<prec, uint>(pointers) {
		
		
	}
	
	template<typename prec, typename uint>
	StaticSolutionState<prec,uint>::~StaticSolutionState(){
		this->SpMat.setZero();
	}
	
	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations)
	{
		this->numberOfEquations = numberOfActiveEquations;
		this->NumberOfActiveEquations = numberOfActiveEquations;
		this->Solution.resize(numberOfEquations);
		this->IncSolution.resize(numberOfEquations);
		this->dIncSolution.resize(numberOfEquations);
		this->SpMat.resize(this->NumberOfActiveEquations, this->NumberOfActiveEquations);
		this->tripletList.reserve(numberOfActiveEquations);
		this->Rhs.resize(numberOfActiveEquations);
		this->eqSol.resize(numberOfActiveEquations);

		this->Solution.setZero();
		
	}
	
	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::setTripletList(std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {
		Eigen::Triplet<prec> test;
		test = Eigen::Triplet<prec>(1, 1, 0.0);
		for (auto i = 0; i < Dofs.size(); ++i) {
			if (Dofs[i]->getStatus() == dofStatus::active) {
				for (auto j = 0; j < Dofs.size(); ++j) {
					if (Dofs[j]->getStatus() == dofStatus::active) {
						if (this->symmetricSolver) {
							if (this->upper) {
								if(Dofs[i]->getEqId()<= Dofs[j]->getEqId()) this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
							}
							else {
								if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
							}
						}
						else {
							this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
						}
					}
				}
			}
		}
	}
	
	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::setSparseMatrix() {
		this->SpMat.setFromTriplets(this->tripletList.begin(), this->tripletList.end());
		this->tripletList.clear();
		this->solver->analyze(this->SpMat);
		std::cout << "Number of Equations: " << this->NumberOfActiveEquations << "\n"
			"Number of non-zero terms: " << this->SpMat.nonZeros() << std::endl;
	}
	
	
	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
		, std::vector<DegreeOfFreedom<prec,uint>*> &Dofs) {
	
		uint vsize = static_cast<uint>(Dofs.size());
		//this->assembleCsrMatrix(this->SpMat, stiffness, Dofs);
#pragma omp critical
		for (uint i = 0; i < vsize; ++i) {
			if (Dofs[i]->getStatus() == dofStatus::active) {
				for (uint j = 0; j < vsize; ++j) {
					if (Dofs[j]->getStatus() == dofStatus::active) {
						if (this->symmetricSolver) {
							if (this->upper) {
								if (Dofs[i]->getEqId() <= Dofs[j]->getEqId()) {
//#pragma omp atomic
									//this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
								}
							}
							else {
								if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) {
//#pragma omp atomic
									//this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
								}
							}
						}
						else {
//#pragma omp atomic
							this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
						}
					}
					else {
						this->Rhs(Dofs[i]->getEqId()) -= stiffness(i, j) *this->dIncSolution(Dofs[j]->getId());
						//std::cout << this->dIncSolution(Dofs[j]->getId()) << std::endl;
					}
				}
//#pragma omp atomic
				this->Rhs(Dofs[i]->getEqId()) -= residual(i);
			}
		}
		//Eigen::SparseMatrix<prec, 0, uint> SpMat

	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::setEquationZero() {
        typedef typename Eigen::SparseMatrix<prec, 0, uint>::InnerIterator eigenIt;
		for (auto k = 0; k < this->SpMat.outerSize(); ++k) {
			for (eigenIt it(this->SpMat, k); it; ++it) {
				it.valueRef() = 0.0;
			}
		}
		this->Rhs.setZero();
		this->dIncSolution.setZero();
		this->IncSolution.setZero();
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::factorize() {
		
		this->solver->factorize(this->SpMat);
		
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::solve() {

		//this->Rhs(this->numberOfEquations - 1) = 1.0;
		
		//this->eqSol = this->solver.solve(this->Rhs);
		prec residual = this->Rhs.dot(this->Rhs);
		std::cout << "Residual norm: " << sqrt(residual) << std::endl;
		this->solver->solve(this->Rhs, this->eqSol);
		this->pointers->getPropLoads()->update();
		
		//std::cout << "Solution: " << this->eqSol << std::endl;
		//std::cout << "Solution: " << this->eqSol << std::endl;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> temp;
		temp.resize(this->numberOfEquations);
		
        //temp = this->SpMat.selfadjointView<Eigen::Upper>()* this->eqSol;
        //this->SpMat.selfadjointView<Eigen::Upper>();
		//std::cout << "Solutionnirm: " << (temp - this->Rhs).norm() << //std::endl;
	}


	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::computeLoads(PointerCollection<prec, uint> &pointers) {
		std::vector<DegreeOfFreedom<prec, uint>> *temp = this->pointers->getEquationHandler()->getDofList();
		std::vector<DegreeOfFreedom<prec, uint>> &Dofs = *temp;
		std::vector<prec> load, loadinc;
		std::vector<uint> ids;
		
		this->pointers->getLoadList()->computeLoads(pointers, ids,load,loadinc);
		for (auto i = 0; i < ids.size(); ++i) {
			if (Dofs[ids[i]].getStatus() == dofStatus::active) {
				this->Rhs(Dofs[ids[i]].getEqId()) += load[i];
			}
			else {
				this->dIncSolution(Dofs[ids[i]].getId()) += loadinc[i];
			}
		}
	}


	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::updateSolution() {
		std::vector<DegreeOfFreedom<prec, uint>> *DofList;
		DofList=this->pointers->getEquationHandler()->getDegreesOfFreedomList();

		for (auto i = 0; i < DofList->size(); ++i) {
			uint eqid, id;
			id = (*DofList)[i].getId();
			if ((*DofList)[i].getStatus() == dofStatus::active) {
				eqid = (*DofList)[i].getEqId();
				this->IncSolution(id) = this->eqSol(eqid);
			}
			else {
				this->IncSolution(id) = this->dIncSolution(id);
			}
		}
		this->Solution += this->IncSolution;
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::computeEigenValues(
		uint number,
		uint addNumber = 0,
		bool max = false,
		prec tol = 1e-10) {
#ifdef USE_SPECTRA

		 
		if (addNumber > this->SpMat.cols()) addNumber = static_cast<uint>(this->SpMat.cols());

		if (this->symmetricSolver) {

		}
		else {
			Eigen::Matrix< std::complex<prec>, 1, Eigen::Dynamic > evalues;
			Eigen::Matrix< std::complex<prec>, Eigen::Dynamic, Eigen::Dynamic > evectors;
			if (max) {
				Spectra::SparseGenMatProd<prec> op(this->SpMat);
				Spectra::GenEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenMatProd<prec>> eigs(&op, number, addNumber);
				eigs.init();
				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
				if (eigs.info() == Spectra::SUCCESSFUL) {
					evalues = eigs.eigenvalues();
					evectors = eigs.eigenvectors();
					for (auto i = 0; i < number; ++i) {
						this->eigenValues.push_back(evalues(i).real());
						if (this->eigenVectors.size() < i+1) this->eigenVectors.emplace_back();
						for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
							this->eigenVectors[i].push_back(evectors(j, i).real());
						}
					}
				}
			}
			else {
				Spectra::SparseGenRealShiftSolve<prec, 0, uint> op(this->SpMat);
				Spectra::GenEigsRealShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenRealShiftSolve<prec, 0, uint>> eigs(&op, number, addNumber, 1e-12);
				eigs.init();
				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
				if (eigs.info() == Spectra::SUCCESSFUL) {
					evalues = eigs.eigenvalues();
					evectors = eigs.eigenvectors();
					for (auto i = 0; i < number; ++i) {
						this->eigenValues.push_back(evalues(i).real());
						if (this->eigenVectors.size() < i + 1) this->eigenVectors.emplace_back();
						for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
							this->eigenVectors[i].push_back(evectors(j, i).real());
						}
					}
				}
				//std::cout << "Eigenvalues found:\n" << evalues.transpose() << std::endl;
			}
			std::cout << "Eigenvalues found:\n" << evalues.transpose() << std::endl;
		}

		this->computeConditionNumber();


		//typedef std::complex<prec> Complex;
		//Spectra::SparseGenMatProd<prec, 0, uint> op(this->SpMat);
		//Spectra::SymEigsSolver<prec, Spectra::SMALLEST_MAGN, Spectra::SparseGenMatProd<prec, 0, uint>> eigs(&op,3,test);

		// Initialize and compute
		//eigs.init();
		//int nconv = eigs.compute();

		//bool compute = true;
		//uint test = 10;
		//Eigen::Matrix< std::complex<prec>, 1, Eigen::Dynamic > evalues;
		//while (compute) {
		//	Spectra::SparseGenMatProd<prec, 0, uint> op(this->SpMat);
		//	Spectra::SymEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenMatProd<prec, 0, uint>> eigs(&op, 6, test);
		//	//Spectra::SparseGenRealShiftSolve<prec, 0, uint> op(this->SpMat);
		//	//Spectra::GenEigsRealShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenRealShiftSolve<prec, 0, uint>> eigs(&op, 6, test,0.0);
		//	eigs.init();
		//	int nconv = eigs.compute(500,1e-6,Spectra::LARGEST_MAGN);
		//	if (eigs.info() == Spectra::SUCCESSFUL) {
		//		compute = false;
		//		//Eigen::Matrix<Complex, Eigen::Dynamic, 1> evalues;
		//		evalues = eigs.eigenvalues();
		//		std::cout << "Number of Iterations: " << eigs.num_iterations() << std::endl;
		//	}
		//	else {
		//		test = test * 2;
		//		test > this->SpMat.cols() ? test = this->SpMat.cols()-1 : test = test;
		//		std::cout << "Increase search eigenvalues to " << test << std::endl;
		//	}
		//
		//}

		
		
			

		//std::cout << "Eigenvalues found:\n" << evalues.transpose() << std::endl;
#endif // USE_SPECTRA
	}

	template<typename prec, typename uint>
	prec StaticSolutionState<prec, uint>::getSolution(const uint & globalId)
	{
		prec ret = this->Solution(globalId);
		
		return ret;
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::resetSolution()
	{
		this->Solution.setZero();
		this->IncSolution.setZero();
		this->dIncSolution.setZero();
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::printSpMat()
	{
		InfoData *infos = this->pointers->getInfoData();
		std::string directory = infos->fileNames[FileHandling::directory];
		std::string filename = infos->fileNames[FileHandling::infile];
		filename += ".ma";
		std::string temp = directory + filename;
		//std::cout << temp;
		std::ofstream myfile;
		myfile.open(temp);

		for (int k = 0; k < this->SpMat.outerSize(); ++k)
			for (Eigen::SparseMatrix<prec>::InnerIterator it(this->SpMat, k); it; ++it)
			{
				myfile << it.row()+1 << " " << it.col()+1
					<< " " << it.value() << std::endl;
				it.value();
				it.row();   // row index
				it.col();   // col index (here it is equal to k)
				it.index(); // inner index, here it is equal to it.row()
			}

		myfile.close();
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::computeConditionNumber()
	{
		if (this->symmetricSolver) {

		}
		else {

			Eigen::Matrix< std::complex<prec>, 1, Eigen::Dynamic > maxEval, minEval;

			Spectra::SparseGenMatProd<prec, 0, uint> op(this->SpMat);
			Spectra::GenEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenMatProd<prec, 0, uint>> eigs(&op, 1, 30);
			eigs.init();
			int nconv = eigs.compute(500, 1e-12, Spectra::LARGEST_MAGN);
			if (eigs.info() == Spectra::SUCCESSFUL) {
				maxEval = eigs.eigenvalues();
			}
			Spectra::SparseGenRealShiftSolve<prec, 0, uint> op2(this->SpMat);
			Spectra::GenEigsRealShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenRealShiftSolve<prec, 0, uint>> eigs2(&op2, 1, 30, 1e-12);
			eigs2.init();
			int nconv2 = eigs2.compute(500, 1e-12, Spectra::LARGEST_MAGN);
			if (eigs2.info() == Spectra::SUCCESSFUL) {
				minEval = eigs2.eigenvalues();
				
			}

			std::cout << "Condition Number: " << maxEval(0) / minEval(0) << std::endl;
		}
	}

} /* namespace FEMProject */


instantiate(StaticSolutionState)
