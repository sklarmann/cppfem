/*
* Solutionstate.h
*
*  Created on: 08.08.2016
*      Author: klari
*/

#pragma once

#include <forwarddeclaration.h>

#include <solver/SolverTypes.h>

#include <Eigen/SparseCore>

namespace FEMProject {

	template<typename prec, typename uint>
	class GenericSolutionState {
	public:
		GenericSolutionState(PointerCollection<prec, uint> *pointers);
		virtual ~GenericSolutionState();

		virtual void setValues(std::map<std::string, prec> &values) {};

		virtual void setTripletList(std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		virtual void setSparseMatrix();
		virtual void insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);

		virtual void computeLoads(PointerCollection<prec, uint> &pointers) {};
		virtual void factorize();
		virtual void solve();
		virtual void setEquationZero();
		virtual void updateSolution() {};
		virtual void computeEigenValues() {};

		virtual void setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations);
		void setSolver(SolverTypes &type);

		void setProps();
		PropfunctionHandler<prec, uint> *getProps() { return this->props; };

		virtual prec getSolution(const uint &globalId){ return 0; };

	protected:
		void assembleCsrMatrix(
			Eigen::SparseMatrix<prec, 0, uint> &SpMat,
			Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness,
			std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		PropfunctionHandler<prec, uint> *props;
		PointerCollection<prec, uint> *pointers;
		uint numberOfEquations, NumberOfActiveEquations;
		GenericSolver<prec, uint> *solver;
		bool symmetricSolver;
		bool upper;


	private:

		
	};



} /* namespace FEMProject */

