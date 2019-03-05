/*
 * Solutionstate.h
 *
 *  Created on: 08.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <solver/StaticSolutionState.h>

#include <pointercollection/pointercollection.h>

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
		this->assembleCsrMatrix(this->SpMat, stiffness, Dofs);
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
							//this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
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
		std::cout << std::setprecision(60) << this->Solution << std::endl;
	}

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::computeEigenValues() {
#ifdef USE_SPECTRA



		typedef std::complex<prec> Complex;

		Spectra::SparseGenMatProd<prec, 0, uint> op(this->SpMat);
		Spectra::GenEigsSolver<prec, Spectra::SMALLEST_MAGN, Spectra::SparseGenMatProd<prec, 0, uint>> eigs(&op,3,40);

		// Initialize and compute
		eigs.init();
		int nconv = eigs.compute();

		std::cout << "Number of Iterations: " << eigs.num_iterations() << std::endl;
		// Retrieve results
		//Eigen::VectorXcd evalues;
		Eigen::Matrix<Complex, Eigen::Dynamic,1> evalues;
		if (eigs.info() == Spectra::SUCCESSFUL)
			evalues = eigs.eigenvalues();

		std::cout << "Eigenvalues found:\n" << evalues << std::endl;
#endif // USE_SPECTRA
	}

	template<typename prec, typename uint>
	prec StaticSolutionState<prec, uint>::getSolution(const uint & globalId)
	{
		prec ret = this->Solution(globalId);
		
		return ret;
	}

} /* namespace FEMProject */


instantiate(StaticSolutionState)
