/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/

#include <preprocessDefine.h>
#include <solver/GenericSolver.h>
#include <solver/EigenSimplicialLDLT.h>
#include <Eigen/SparseCore>
#include<Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>


#include <iostream>

namespace FEMProject {



	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.analyzePattern(SpMat);
	}

	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.factorize(SpMat);
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << this->solver.vectorD() << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
	}

	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution) {

		solution = this->solver.solve(Rhs);

	};


}


instantiate(EigenSimplicialLDLT)
