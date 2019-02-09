/*
* Solutionstate.h
*
*  Created on: 08.08.2016
*      Author: klari
*/

#include <preprocessDefine.h>

#include <solver/GenericSolutionState.h>

#include <loads/PropfunctionHandler.h>

#include <solver/EigenPardisoLDLT.h>
#include <solver/EigenPardisoLLT.h>
#include <solver/EigenPardisoLU.h>
#include <solver/EigenSimplicialLDLT.h>
#include <solver/EigenSimplicialLLT.h>
#include <solver/EigenSparseLU.h>
#include <solver/EigenSparseQR.h>


namespace FEMProject {


	template<typename prec, typename uint>
	GenericSolutionState<prec, uint>::GenericSolutionState(PointerCollection<prec, uint> *pointers) {
		this->pointers = pointers;
		this->numberOfEquations = 0;
		this->NumberOfActiveEquations = 0;
		this->solver = 0;
		this->symmetricSolver = false;
		this->props = 0;
	}

	template<typename prec, typename uint>
	GenericSolutionState<prec, uint>::~GenericSolutionState() {
		delete this->solver;
		this->pointers = 0;
		if (this->props != 0) delete this->props;
	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations)
	{
		
	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setTripletList(std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {
		
	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setSparseMatrix() {
		
	}


	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
		, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {

		

	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setEquationZero() {
		
	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::factorize() {

	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::solve() {

	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setSolver(SolverTypes &type) {

		switch (type) {
		case SolverTypes::EigenPardisoLDLT:
			this->solver = new EigenPardisoLDLT<prec, uint>;
			break;
		case SolverTypes::EigenPardisoLLT:
			this->solver = new EigenPardisoLLT<prec, uint>;
			this->symmetricSolver = true;
			this->upper = true;
			break;
		case SolverTypes::EigenPardisoLU:
			this->solver = new EigenPardisoLU<prec, uint>;
			break;
		case SolverTypes::EigenSimplicialLDLT:
			this->solver = new EigenSimplicialLDLT<prec, uint>;
			break;
		case SolverTypes::EigenSimplicialLLT:
			this->solver = new EigenSimplicialLLT<prec, uint>;
			break;
		case SolverTypes::EigenSparseLU:
			this->solver = new EigenSparseLU<prec, uint>;
			break;
		case SolverTypes::EigenSparseQR:
			this->solver = new EigenSparseQR<prec, uint>;
			break;
		}

	}

	template<typename prec, typename uint>
	void GenericSolutionState<prec, uint>::setProps() {
		if (this->props == 0) {
			this->props = new PropfunctionHandler<prec, uint>;
		}
	}



} /* namespace FEMProject */


instantiate(GenericSolutionState)
