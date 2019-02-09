/*
 * GenericSolver.h
 *
 *  Created on: 02.10.2016
 *      Author: Klarmann
 */

#pragma once

#include <solver/GenericSolver.h>
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>
#include <Eigen/OrderingMethods>

namespace FEMProject {

	template <typename prec, typename uint>
	class EigenSparseLU : public GenericSolver<prec,uint> {
	public:
		EigenSparseLU() {};
		~EigenSparseLU() {};
		void analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		void solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
			Eigen::Dynamic, 1> &solution);
	private:
		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::COLAMDOrdering<uint> > solver;
	};
	

}