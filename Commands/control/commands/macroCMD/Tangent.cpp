
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Tangent.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/Timer.h>

#include <finiteElements/ElementList.h>

#include <solver/GenericSolutionState.h>

#include <Eigen/SparseCore>
#include <Eigen/Dense>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Tangent<prec, uint>::Tangent(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string Tangent<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Tangent<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				uint numberOfElements;
				ElementList<prec, uint> *elemList = pointers.getElementList();
				numberOfElements = elemList->getNumberOfElements();
				GenericFiniteElement<prec, uint> *elem;
				pointers.getSolutionState()->setEquationZero();

				Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> stiffness;
				Eigen::Matrix<prec, Eigen::Dynamic, 1> residual;
				std::vector<DegreeOfFreedom<prec, uint>*> Dofs;

				Timer<sec> testtimer;

				testtimer.start();
				GenericSolutionState<prec, uint> *solutionstate = pointers.getSolutionState();
				solutionstate->computeLoads(pointers);
#pragma omp parallel for private(elem,stiffness,residual, Dofs) schedule(dynamic)
				for (uint i = 0; i < numberOfElements; ++i) {
					Dofs.clear();
					elem = elemList->getElement(i);
					elem->GenericSetTangentResidual(stiffness, residual, Dofs);
					solutionstate->insertStiffnessResidual(stiffness, residual, Dofs);
					//		elementLibrary(*elem, ControlOptions::BuildStiffnessResidual);
				}
				testtimer.stop();
				std::cout << "Assembly of System took: " << testtimer << std::endl;
				testtimer.start();
				pointers.getSolutionState()->factorize();
				testtimer.stop();
				std::cout << "Factorization took: " << testtimer << std::endl;
				pointers.getSolutionState()->solve();
				pointers.getSolutionState()->updateSolution();
			}
		}
	}
}

instantiate(Commands::Macro::Tangent)