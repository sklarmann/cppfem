/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/


#include<preprocessDefine.h>
#include <solver/GenericSolver.h>
#include <solver/EigenPardisoLU.h>
#include <Eigen/SparseCore>
#include <iostream>

namespace FEMProject {


	template <typename prec, typename uint>
	EigenPardisoLU<prec, uint>::~EigenPardisoLU() {
		this->first = true;
		//Eigen::SparseMatrix<prec, 0, uint> SpMat;
		//SpMat.resize(0, 0);
		//this->solver.analyzePattern(SpMat);
		//std::cout << "Pardiso LU destructor called" << std::endl;

	}


	template <typename prec, typename uint>
	void EigenPardisoLU<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		//this->solver.compute(SpMat);
	}

	template <typename prec, typename uint>
	void EigenPardisoLU<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		//if (first) {
		//	this->solver.compute(SpMat);
		//	this->first = false;
		//	std::cout << "frist" << std::endl;
		//}
		//else
		//{
		//	this->solver.factorize(SpMat);
		//	std::cout << "second" << std::endl;
		//}
		this->solver.compute(SpMat);
		std::cout << this->solver.info();
	}

	template <typename prec, typename uint>
	void EigenPardisoLU<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution) {

		if (this->solver.info() == Eigen::ComputationInfo::Success) {
			solution = this->solver.solve(Rhs);
		}
		else {
			solution.setZero();
		}
	};


}

instantiate(EigenPardisoLU)
