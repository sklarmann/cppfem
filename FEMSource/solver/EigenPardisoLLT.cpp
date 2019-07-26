/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/


#include<preprocessDefine.h>
#include <solver/EigenPardisoLLT.h>
#include <iostream>

namespace FEMProject {


	template <typename prec, typename uint>
	void EigenPardisoLLT<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.analyzePattern(SpMat);
	}

	template <typename prec, typename uint>
	void EigenPardisoLLT<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.factorize(SpMat);
		std::cout << this->solver.info();
	}

	template <typename prec, typename uint>
	void EigenPardisoLLT<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution) {
		if (this->solver.info() == Eigen::ComputationInfo::Success) {
			solution = this->solver.solve(Rhs);
		}
		else {
			solution.setZero();
		}
	};


}

instantiate(EigenPardisoLLT)
