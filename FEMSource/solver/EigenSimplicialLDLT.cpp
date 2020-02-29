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
#include <Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>
#include <control/HandlingStructs.h>

#include <iostream>

namespace FEMProject {



	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.analyzePattern(SpMat);
	}

	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat) {
		this->solver.factorize(SpMat);
        prec mn = 0, mx=0, temp;
        mn = this->solver.vectorD().minCoeff();
        mx = this->solver.vectorD().maxCoeff();
        std::cout << "Conditioning: " << mn << " max " << mx << " rel: " << mx/mn << std::endl;
		//std::cout << "-------------------------------------------" << std::endl;
		//std::cout << this->solver.vectorD() << std::endl;
		//std::cout << "-------------------------------------------" << std::endl;
	}

	template <typename prec, typename uint>
	void EigenSimplicialLDLT<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution) {
		if (this->solver.info() == Eigen::ComputationInfo::Success) {
			solution = this->solver.solve(Rhs);
		}
		else {
			solution.setZero();
		}
		

	};


}


instantiate(EigenSimplicialLDLT)
