/*
 * Solutionstate.h
 *
 *  Created on: 08.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <solver/GenericSolutionState.h>

#include <vector>

namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	template<typename prec, typename uint>
	class StaticSolutionState : public GenericSolutionState<prec,uint> {
	public:
		StaticSolutionState(PointerCollection<prec, uint> *pointers);
		~StaticSolutionState();
		void setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations);

		void setTripletList(std::vector<DegreeOfFreedom<prec,uint>*> &Dofs);
		void setSparseMatrix();
		void insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
	
		void computeLoads(PointerCollection<prec, uint> &pointers);

		void factorize();
		void solve();
		void setEquationZero();
		void updateSolution();
		void computeEigenValues();

		prec getSolution(const uint &globalId);

		void resetSolution();
	private:
	
		Eigen::Matrix<prec, Eigen::Dynamic, 1> Solution, IncSolution, dIncSolution;
		
//		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::COLAMDOrdering<uint> > solver;

		

		Eigen::Matrix<prec, Eigen::Dynamic, 1> Rhs;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> eqSol;
		std::vector<Eigen::Triplet<prec,uint>> tripletList;
		Eigen::SparseMatrix<prec, 0, uint> SpMat;
	};
} /* namespace FEMProject */
