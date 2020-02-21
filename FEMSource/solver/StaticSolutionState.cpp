/*
 * Solutionstate.h
 *
 *  Created on: 08.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>


#include <solver/GenericSolutionState.h>
#include <solver/StaticSolutionState.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>

#include <finiteElements/ElementList.h>

#include <math/Userconstants.h>

#include <fstream>

#include <equations/DofStatus.h>
#include <equations/DegreeOfFreedom.h>
#include <equations/EquationHandler.h>

#include <loads/LoadList.h>
#include <loads/PropfunctionHandler.h>

#include <solver/GenericSolver.h>

#include <vector>
#include <sstream>

#include <Eigen/SparseCore>
#include <Eigen/Dense>


#ifdef USE_SPECTRA
#include <GenEigsSolver.h>
#include <MatOp/SparseGenMatProd.h>
#include <MatOp/SparseSymMatProd.h>
#include <MatOp/SparseSymShiftSolve.h>
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
	StaticSolutionState<prec,uint>::StaticSolutionState(PointerCollection<prec, uint> *pointers, std::map<std::string, prec> &parameter) : GenericSolutionState<prec, uint>(pointers, parameter) {
		
		
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
			if (Dofs[i]->getStatus() != dofStatus::inactive) {
				for (auto j = 0; j < Dofs.size(); ++j) {
					if (Dofs[j]->getStatus() != dofStatus::inactive) {
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
        
        InfoData *info;
        info = this->pointers->getInfoData();
        
		info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
		"Number of Equations: " << this->NumberOfActiveEquations << "\n"
			"Number of non-zero terms: " << this->SpMat.nonZeros() << std::endl;
	}
	
	
	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
		, std::vector<DegreeOfFreedom<prec,uint>*> &Dofs) {
	
		uint vsize = static_cast<uint>(Dofs.size());
		//this->assembleCsrMatrix(this->SpMat, stiffness, Dofs);
		this->modifyLinked(stiffness, residual, Dofs);
#pragma omp critical
		for (uint i = 0; i < vsize; ++i) {
			if (Dofs[i]->getStatus() != dofStatus::inactive) {
				for (uint j = 0; j < vsize; ++j) {
					if (Dofs[j]->getStatus() != dofStatus::inactive) {
						if (this->symmetricSolver) {
							if (this->upper) {
								if (Dofs[i]->getEqId() <= Dofs[j]->getEqId()) {
#pragma omp critical (assembleOne)
									this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
								}
							}
							else {
								if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) {
#pragma omp critical (assembleTwo)
									this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
								}
							}
						}
						else {
#pragma omp critical (assembleOne)
							this->SpMat.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
						}
					}
					else {
						this->Rhs(Dofs[i]->getEqId()) -= stiffness(i, j) *this->dIncSolution(Dofs[j]->getId());
					}
				}
#pragma omp critical (assembleThree)
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
		this->solver->solve(this->Rhs, this->eqSol);
		this->pointers->getPropLoads()->update();
		
		//std::cout << "Solution: " << this->eqSol << std::endl;
		//std::cout << "Solution: " << this->eqSol << std::endl;
		//Eigen::Matrix<prec, Eigen::Dynamic, 1> temp;
		//temp.resize(this->numberOfEquations);
		
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
			if (Dofs[ids[i]].getStatus() != dofStatus::inactive) {
				this->Rhs(Dofs[ids[i]].getEqId()) += load[i];
			}
			else {
				this->dIncSolution(Dofs[ids[i]].getId()) += loadinc[i];
			}
		}
	}
    template<typename prec, typename uint>
    void StaticSolutionState<prec,uint>::assembleSystem(){
        uint numberOfElements;
		ElementList<prec, uint> *elemList = this->pointers->getElementList();
		numberOfElements = elemList->getNumberOfElements();
		GenericFiniteElement<prec, uint> *elem;
		this->setEquationZero();

		Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> stiffness;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> residual;
		std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
		
		this->computeLoads(*(this->pointers));
        
#pragma omp parallel for private(elem,stiffness,residual, Dofs) schedule(dynamic)
        for (uint i = 0; i < numberOfElements; ++i) {
			Dofs.clear();
			elem = elemList->getElement(i);
			elem->GenericSetTangentResidual(stiffness, residual, Dofs);
			this->insertStiffnessResidual(stiffness, residual, Dofs);
					//		elementLibrary(*elem, ControlOptions::BuildStiffnessResidual);
        }/**
				testtimer.stop();
				std::cout << "Assembly of System took: " << testtimer << std::endl;
				testtimer.start();
				pointers.getSolutionState()->factorize();
				testtimer.stop();
				std::cout << "Factorization took: " << testtimer << std::endl;
				pointers.getSolutionState()->solve();
				pointers.getSolutionState()->updateSolution();**/
    }

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::updateSolution() {
		std::vector<DegreeOfFreedom<prec, uint>> *DofList;
		DofList=this->pointers->getEquationHandler()->getDegreesOfFreedomList();

		for (auto i = 0; i < DofList->size(); ++i) {
			uint eqid, id;
			id = (*DofList)[i].getId();
			if ((*DofList)[i].getStatus() != dofStatus::inactive) {
				eqid = (*DofList)[i].getEqId();
				if ((*DofList)[i].getStatus() == dofStatus::linked) {
					this->IncSolution(id) = this->eqSol(eqid)*(*DofList)[i].getLinkFact();
				}
				else {
					this->IncSolution(id) = this->eqSol(eqid);
				}
				
			}
			else {
				this->IncSolution(id) = this->dIncSolution(id);
			}
		}
		this->Solution += this->IncSolution;
	}
	
	template <typename prec, typename uint>
	void StaticSolutionState<prec,uint>::dampedSolutionUpdate(){
        prec cres = this->residual();
        Eigen::Matrix<prec, Eigen::Dynamic, 1> BSolution, BIncSolution, BdIncSolution;
        BSolution = this->Solution;
        BIncSolution = this->IncSolution;
        BdIncSolution = this->dIncSolution;
        this->updateSolution();
        this->assembleSystem();
        prec nres = this->residual();
        uint cc = 0;
        while(nres > cres){
            cc+=1;
            this->Solution=BSolution;
            this->IncSolution=BIncSolution;
            this->dIncSolution=BdIncSolution;
            this->eqSol/=2;
            this->updateSolution();
            this->assembleSystem();
            nres = this->residual();
            
        }
    }

	template<typename prec, typename uint>
	void StaticSolutionState<prec, uint>::computeEigenValues(
		uint number,
		uint addNumber /* = 0 */ ,
		bool max /* = false */,
		prec tol /* = 1e-10 */,
		prec shift /* = 1e-10 */) {
#ifdef USE_SPECTRA
		OutputHandler &Log = this->pointers->getInfoData()->Log;
		
		this->eigenValues.clear();
		this->eigenVectors.clear();


		if (addNumber > this->SpMat.cols()) addNumber = static_cast<uint>(this->SpMat.cols());

		Eigen::Matrix<prec, 1, Eigen::Dynamic> evalues;
		Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> evectors;

		if (max) {
            
            
			Spectra::SparseSymMatProd<prec> op(this->SpMat);
			Spectra::SymEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseSymMatProd<prec>> eigs(&op, number, addNumber);
			eigs.init();
			try {
				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
			}
			catch (const std::exception& e) {
				Log(LogLevel::NoLog, LogLevel::NoLog)
					<< "Eigenvalue solver failed: \n"
					<< e.what() << std::endl;
			}
			if (eigs.info() == Spectra::SUCCESSFUL) {
				evalues = eigs.eigenvalues();
				evectors = eigs.eigenvectors();
				for (auto i = 0; i < number; ++i) {
					this->eigenValues.push_back(evalues(i));
					if (this->eigenVectors.size() < i+1) this->eigenVectors.emplace_back();
					for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
						this->eigenVectors[i].push_back(evectors(j, i));
					}
				}
			}
		}
		else {
			
			Spectra::SparseSymShiftSolve<prec> op(this->SpMat);
			Spectra::SymEigsShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseSymShiftSolve<prec>> eigs(&op, number, addNumber, shift);
			
			eigs.init();
			try {
				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
			}
			catch (const std::exception& e) {
				Log(LogLevel::NoLog, LogLevel::NoLog) 
					<< "Eigenvalue solver failed: \n"
					<< e.what() << std::endl;
			}
			
			if (eigs.info() == Spectra::SUCCESSFUL) {
				evalues = eigs.eigenvalues();
				evectors = eigs.eigenvectors();
				for (auto i = 0; i < number; ++i) {
					this->eigenValues.push_back(evalues(i));
					if (this->eigenVectors.size() < i + 1) this->eigenVectors.emplace_back();
					for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
						this->eigenVectors[i].push_back(evectors(j, i));
					}
				}
			}
		}

		Log(LogLevel::NoLog, LogLevel::NoLog) << evalues.transpose() << std::endl;


		//if (this->symmetricSolver) {
		//
		//}
		//else {
		//	Eigen::Matrix< std::complex<prec>, 1, Eigen::Dynamic > evalues;
		//	Eigen::Matrix< std::complex<prec>, Eigen::Dynamic, Eigen::Dynamic > evectors;
		//	if (max) {
		//		Eigen::Matrix<prec, 1, Eigen::Dynamic > evalues2;
		//		Spectra::SparseSymMatProd<prec> op(this->SpMat);
		//		Spectra::SymEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseSymMatProd<prec>> eigs(&op, number, addNumber);
		//		//Spectra::SparseGenMatProd<prec> op(this->SpMat);
		//		//Spectra::GenEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenMatProd<prec>> eigs(&op, number, addNumber);
		//		eigs.init();
		//		int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
		//		if (eigs.info() == Spectra::SUCCESSFUL) {
		//			evalues2 = eigs.eigenvalues();
		//
		//			std::cout << "Eigenvalues found:\n" << evalues2.transpose() << std::endl;
		//		//	evectors = eigs.eigenvectors();
		//			//for (auto i = 0; i < number; ++i) {
		//			//	this->eigenValues.push_back(evalues(i).real());
		//			//	if (this->eigenVectors.size() < i+1) this->eigenVectors.emplace_back();
		//			//	for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
		//			//		this->eigenVectors[i].push_back(evectors(j, i).real());
		//			//	}
		//			//}
		//		}
		//	}
		//	else {
		//		Spectra::SparseGenRealShiftSolve<prec, 0, uint> op(this->SpMat);
		//		Spectra::GenEigsRealShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenRealShiftSolve<prec, 0, uint>> eigs(&op, number, addNumber, 1e-12);
		//		eigs.init();
		//		int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
		//		if (eigs.info() == Spectra::SUCCESSFUL) {
		//			evalues = eigs.eigenvalues();
		//			evectors = eigs.eigenvectors();
		//			for (auto i = 0; i < number; ++i) {
		//				this->eigenValues.push_back(evalues(i).real());
		//				if (this->eigenVectors.size() < i + 1) this->eigenVectors.emplace_back();
		//				for (auto j = 0; j < this->NumberOfActiveEquations; ++j) {
		//					this->eigenVectors[i].push_back(evectors(j, i).real());
		//				}
		//			}
		//		}
		//		//std::cout << "Eigenvalues found:\n" << evalues.transpose() << std::endl;
		//	}
		//	std::cout << "Eigenvalues found:\n" << evalues.transpose() << std::endl;
		//}

#endif // USE_SPECTRA
	}

	template<typename prec, typename uint>
	prec StaticSolutionState<prec, uint>::getSolution(const uint & globalId)
	{
		prec ret = this->Solution(globalId);
		
		return ret;
	}

	template<typename prec, typename uint>
	Eigen::Matrix<prec, Eigen::Dynamic, 1> StaticSolutionState<prec, uint>::getSolution(std::vector<DegreeOfFreedom<prec, uint>*> Dofs)
	{
		Eigen::Matrix<prec, Eigen::Dynamic, 1> RetVec;

		uint Size = static_cast<uint>(Dofs.size());
		if (Size > 0) {
			RetVec.resize(Size);
			for (auto i = 0; i < Size; ++i) {
				RetVec(i) = this->Solution(Dofs[i]->getId());
			}
		}

		return RetVec;
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
		myfile << std::setprecision(20);
		myfile << std::scientific;
		for (int k = 0; k < this->SpMat.outerSize(); ++k)
			for (typename Eigen::SparseMatrix<prec>::InnerIterator it(this->SpMat, k); it; ++it)
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
        
		OutputHandler &Log = this->pointers->getInfoData()->Log;
        
        Eigen::Matrix<prec,Eigen::Dynamic,1> rr;
        auto numEq = this->SpMat.cols();
        rr.resize(numEq);
        rr = Eigen::Matrix<prec,Eigen::Dynamic,1>::Random(numEq,1);
        auto rrNorm = sqrt(rr.dot(rr));
        for (auto i=0;i<10;++i){
            rr /= rrNorm;
            rr = this->SpMat*rr;
            rrNorm = sqrt(rr.dot(rr));
        }
        auto evMax = rrNorm;    
        
        rr = Eigen::Matrix<prec,Eigen::Dynamic,1>::Random(numEq,1);
        this->solver->solve(rr,rr);
        rrNorm = sqrt(rr.dot(rr));
        for (auto i=0;i<10;++i){
            rr /= rrNorm;
            this->solver->solve(rr,rr);
            rrNorm = sqrt(rr.dot(rr));
        }
        auto evMin=(prec)1/rrNorm;
        
        std::stringstream convert;
        convert << "ConditionNumber=" << evMax/evMin;
        
        std::string pass = convert.str();
        
        this->pointers->getUserConstants()->process(pass);
        
        Log(LogLevel::BasicLog, LogLevel::BasicLog) <<
        "\nResult of Condition Number Computation:\n" << 
        "   Minimum Eigenvalue: " << evMin << "\n" <<
        "   Maximum Eigenvalue: " << evMax << "\n" <<
        "     Condition Number: " << evMax/evMin << "\n" << std::endl;
        
        
        
// #ifdef USE_SPECTRA
// 		OutputHandler &Log = this->pointers->getInfoData()->Log;
// 		prec tol = static_cast<prec>(1e-12);
// 		uint number = 2;
// 		uint addNumber = 10;
// 		if (addNumber > this->SpMat.cols()) addNumber = static_cast<uint>(this->SpMat.cols());
// 
// 		Eigen::Matrix<prec, 1, Eigen::Dynamic> min, max;
// 		prec minV=1, maxV=1;
// 		{
// 			Spectra::SparseSymMatProd<prec> op(this->SpMat);
// 			Spectra::SymEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseSymMatProd<prec>> eigs(&op, number, addNumber);
// 			eigs.init();
// 			try {
// 				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
// 			}
// 			catch (const std::exception& e) {
// 				Log(LogLevel::NoLog, LogLevel::NoLog)
// 					<< "Eigenvalue solver failed: \n"
// 					<< e.what() << std::endl;
// 			}
// 			if (eigs.info() == Spectra::SUCCESSFUL) {
// 				max = eigs.eigenvalues();
// 				maxV = max(0);
// 			}
// 
// 		}
// 		{
// 			Spectra::SparseSymShiftSolve<prec> op(this->SpMat);
// 			Spectra::SymEigsShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseSymShiftSolve<prec>> eigs(&op, number, addNumber, 1e-12);
// 
// 			eigs.init();
// 			try {
// 				int nconv = eigs.compute(500, tol, Spectra::LARGEST_MAGN);
// 			}
// 			catch (const std::exception& e) {
// 				Log(LogLevel::NoLog, LogLevel::NoLog)
// 					<< "Eigenvalue solver failed: \n"
// 					<< e.what() << std::endl;
// 			}
// 			if (eigs.info() == Spectra::SUCCESSFUL) {
// 				min = eigs.eigenvalues();
// 				minV = min(1);
// 			}
// 		}
// 		
// 		Log(LogLevel::NoLog, LogLevel::NoLog) 
// 			<< "Condition Number of current equation system: \n"
// 			<< maxV / minV << std::endl;
// 
// 		
// 		if (this->symmetricSolver) {
// 		
// 		}
// 		else {
// 		
// 			Eigen::Matrix< std::complex<prec>, 1, Eigen::Dynamic > maxEval, minEval;
// 		
// 			Spectra::SparseGenMatProd<prec, 0, uint> op(this->SpMat);
// 			Spectra::GenEigsSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenMatProd<prec, 0, uint>> eigs(&op, 1, 30);
// 			eigs.init();
// 			int nconv = eigs.compute(500, 1e-12, Spectra::LARGEST_MAGN);
// 			if (eigs.info() == Spectra::SUCCESSFUL) {
// 				maxEval = eigs.eigenvalues();
// 			}
// 			Spectra::SparseGenRealShiftSolve<prec, 0, uint> op2(this->SpMat);
// 			Spectra::GenEigsRealShiftSolver<prec, Spectra::LARGEST_MAGN, Spectra::SparseGenRealShiftSolve<prec, 0, uint>> eigs2(&op2, 1, 30, 1e-12);
// 			eigs2.init();
// 			int nconv2 = eigs2.compute(500, 1e-12, Spectra::LARGEST_MAGN);
// 			if (eigs2.info() == Spectra::SUCCESSFUL) {
// 				minEval = eigs2.eigenvalues();
// 				
// 			}
// 		
// 			std::cout << "Condition Number: " << maxEval(0) / minEval(0) << std::endl;
// 		}
// #endif
	}

} /* namespace FEMProject */


instantiate(StaticSolutionState)
