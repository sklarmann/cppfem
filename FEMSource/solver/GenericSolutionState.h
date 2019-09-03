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

#include <Eigen/Dense>



namespace FEMProject {

	template<typename prec, typename uint>
	class GenericSolutionState {
	public:
		GenericSolutionState(PointerCollection<prec, uint> *pointers, std::map<std::string,prec> &parameter);
		virtual ~GenericSolutionState();

		virtual void setValues(std::map<std::string, prec> &values) {};

		virtual void setTripletList(std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		virtual void setSparseMatrix();
		virtual void insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);

		virtual void computeLoads(PointerCollection<prec, uint> &pointers) {};
        virtual void assembleSystem(){};
		virtual void factorize();
		virtual void solve();
        virtual prec residual(){return 0;};
		virtual void setEquationZero();
		virtual void updateSolution() {};
		virtual void computeEigenValues(
			uint number, 
			uint addNumber=0, 
			bool max=false, 
			prec tol = 1e-10,
			prec shift = 1e-10) {};

		virtual void setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations);
		void setSolver(SolverTypes &type);

		void setProps();
		PropfunctionHandler<prec, uint> *getProps() { return this->props; };

		virtual prec getSolution(const uint &globalId){ return 0; };
		virtual Eigen::Matrix<prec, Eigen::Dynamic, 1> getSolution(
			std::vector<DegreeOfFreedom<prec, uint>*> Dofs) {
			return Eigen::Matrix<prec, Eigen::Dynamic, 1>(0);
		};

		virtual void resetSolution() {
			this->eigenVectors.clear();
			this->eigenValues.clear();
		};

		virtual uint numberOfEigenValues() { return static_cast<uint>(this->eigenValues.size()); };
		virtual prec getEigenVectorComp(uint eqId, uint evId);

		virtual void printSpMat();

		virtual void computeConditionNumber() {};

		prec getEigenValue(uint &number) { return this->eigenValues[number]; };


	protected:
		void assembleCsrMatrix(
			Eigen::SparseMatrix<prec, 0, uint> &SpMat,
			Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness,
			std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		void modifyLinked(
			Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness,
			Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual,
			std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		PropfunctionHandler<prec, uint> *props;
		PointerCollection<prec, uint> *pointers;
		uint numberOfEquations, NumberOfActiveEquations;
		GenericSolver<prec, uint> *solver;
		bool symmetricSolver;
		bool upper;

		std::vector<std::vector<prec>> eigenVectors;
		std::vector<prec> eigenValues;
 

	private:

		
	};



} /* namespace FEMProject */

