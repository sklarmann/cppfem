/*
* GenericSolver.h
*
*  Created on: 02.10.2016
*      Author: Klarmann
*/

#pragma once

#include <solver/GenericSolver.h>
#include <Eigen/SparseCore>
#ifdef USE_MKL
#include <Eigen/PardisoSupport>
#else
#include <Eigen/SparseLU>
#include <Eigen/OrderingMethods>
#endif

namespace FEMProject {

	template <typename prec, typename uint>
	class EigenPardisoLU : public GenericSolver<prec, uint> {
	public:
		EigenPardisoLU() {};
		~EigenPardisoLU();
		void analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
			Eigen::Dynamic, 1> &solution);
	private:
		
#ifdef USE_MKL
		Eigen::PardisoLU<Eigen::SparseMatrix<prec, 0, uint>> solver;
#else
		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::COLAMDOrdering<uint> > solver;
#endif // USE_MKL
		bool first;
	};


}