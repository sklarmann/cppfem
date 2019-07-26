/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/

#include <preprocessDefine.h>

#include <solver/EigenSimplicialLLT.h>
#include <Eigen/SparseCore>
#include<Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>

namespace FEMProject {


	template <typename prec, typename uint>
	void EigenSimplicialLLT<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.analyzePattern(SpMat);
	}

	template <typename prec, typename uint>
	void EigenSimplicialLLT<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.factorize(SpMat);
		//std::cout << "Determinant:  " << this->solver.determinant();
		//std::cout << "Solver Info:  " << this->solver.info() << "   " << Eigen::Success;
	}

	template <typename prec, typename uint>
	void EigenSimplicialLLT<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution) {
		if (this->solver.info() == Eigen::ComputationInfo::Success) {
			solution = this->solver.solve(Rhs);
		}
		else {
			solution.setZero();
		}
	};


}


instantiate(EigenSimplicialLLT)
