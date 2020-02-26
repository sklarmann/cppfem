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
	class EigenPardisoLLT : public GenericSolver<prec, uint> {
	public:
		EigenPardisoLLT() {};
		~EigenPardisoLLT() {};
		void analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
			Eigen::Dynamic, 1> &solution);
	private:

		
#ifdef USE_MKL
		Eigen::PardisoLDLT<Eigen::SparseMatrix<prec, 0, uint>> solver;
#else
		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::AMDOrdering<uint> > solver;
#endif // USE_MKL

		
	};


}
