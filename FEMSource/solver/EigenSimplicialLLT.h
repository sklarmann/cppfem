/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/

#pragma once

#include <solver/GenericSolver.h>
#include <Eigen/SparseCore>
#include<Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>

namespace FEMProject {

	template <typename prec, typename uint>
	class EigenSimplicialLLT : public GenericSolver<prec, uint> {
	public:
		EigenSimplicialLLT() {};
		~EigenSimplicialLLT() {};
		void analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
			Eigen::Dynamic, 1> &solution);
	private:
		Eigen::SimplicialLLT<Eigen::SparseMatrix<prec, 0, uint>, Eigen::Lower, Eigen::COLAMDOrdering<uint> > solver;
	};

}