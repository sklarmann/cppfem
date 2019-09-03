/*
* TransientSolutionNewmark.h
*
*  Created on: 08.08.2016
*      Author: klari
*/

#pragma once

#include <forwarddeclaration.h>

#include <solver/GenericSolutionState.h>
#include <map>

#include <vector>

namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	template<typename prec, typename uint>
	class TransientSolutionNewmark : public GenericSolutionState<prec, uint> {
	public:
		TransientSolutionNewmark(PointerCollection<prec, uint> *pointers, std::map<std::string, prec> &parameter);
		~TransientSolutionNewmark();
		void setValues(std::map<std::string,prec> &values);
		void setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations);
		
		void setTripletList(std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		void setSparseMatrix();
		void insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);

		
		void computeLoads(PointerCollection<prec, uint> &pointers);

		virtual void assembleSystem();
		void setEquationZero();

		virtual Eigen::Matrix<prec, Eigen::Dynamic, 1> getSolution(
			std::vector<DegreeOfFreedom<prec, uint>*> Dofs);
		//void factorize();
		//void solve();
		//void setEquationZero();
		//void updateSolution();
		//void computeEigenValues();
		//
		//prec getSolution(const uint &globalId);

	private:
		void insertMassMatrix(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		prec beta, gamma;

		Eigen::Matrix<prec, Eigen::Dynamic, 1> Solution, IncSolution, dIncSolution;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> velocity, acceleration;
		Eigen::SparseMatrix<prec, 0, uint> Stiffness, Mass, Damping;
		Eigen::SparseMatrix<prec, 0, uint> SpMat;

		Eigen::Matrix<prec, Eigen::Dynamic, 1> Rhs;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> eqSol;
		std::vector<Eigen::Triplet<prec, uint>> tripletList;

		//		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::COLAMDOrdering<uint> > solver;



		//Eigen::Matrix<prec, Eigen::Dynamic, 1> Rhs;
		//Eigen::Matrix<prec, Eigen::Dynamic, 1> eqSol;
		//std::vector<Eigen::Triplet<prec, uint>> tripletList;
	};
} /* namespace FEMProject */
