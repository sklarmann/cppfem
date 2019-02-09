/*
 * GenericSolver.h
 *
 *  Created on: 02.10.2016
 *      Author: Klarmann
 */

#pragma once


#include <Eigen/SparseCore>
#include <Eigen/Dense>


namespace FEMProject {


	template <typename prec, typename uint>
	class GenericSolver {
	public:
		GenericSolver();
		virtual ~GenericSolver();
		virtual void analyze(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		virtual void factorize(Eigen::SparseMatrix<prec, 0, uint> &SpMat);
		virtual void solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
						   Eigen::Dynamic, 1> &solution);
	};



}