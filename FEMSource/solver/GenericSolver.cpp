/*
 * GenericSolver.h
 *
 *  Created on: 02.10.2016
 *      Author: Klarmann
 */

#include <preprocessDefine.h>

#include <solver/GenericSolver.h>


namespace FEMProject {



	template<typename prec, typename uint>
	inline GenericSolver<prec, uint>::GenericSolver()
	{
	}

	template<typename prec, typename uint>
	GenericSolver<prec, uint>::~GenericSolver()
	{
	}

	template<typename prec, typename uint>
	void GenericSolver<prec, uint>::analyze(Eigen::SparseMatrix<prec, 0, uint>& SpMat)
	{
	}

	template<typename prec, typename uint>
	void GenericSolver<prec, uint>::factorize(Eigen::SparseMatrix<prec, 0, uint>& SpMat)
	{
	}

	template<typename prec, typename uint>
	void GenericSolver<prec, uint>::solve(Eigen::Matrix<prec, Eigen::Dynamic, 1> &Rhs, Eigen::Matrix<prec,
		Eigen::Dynamic, 1> &solution)
	{
	}


}

instantiate(GenericSolver)

