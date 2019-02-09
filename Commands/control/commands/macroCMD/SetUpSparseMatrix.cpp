
#include <preprocessDefine.h>

#include <control/commands/macroCMD/SetUpSparseMatrix.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/Timer.h>

#include <equations/EquationHandler.h>

#include <finiteElements/ElementList.h>

#include <solver/GenericSolutionState.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			SetUpSparseMatrix<prec, uint>::SetUpSparseMatrix(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string SetUpSparseMatrix<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void SetUpSparseMatrix<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				
				Timer<sec> testtimer;

				testtimer.start();

				ElementList<prec, uint> *elemList = pointers.getElementList();

				uint numberOfElements;
				pointers.getEquationHandler()->updateEquations();
				numberOfElements = elemList->getNumberOfElements();
				GenericFiniteElement<prec, uint> *elem;
				pointers.getEquationHandler()->initSolutionState();

				for (uint i = 0; i < numberOfElements; ++i) {
					elem = elemList->getElement(i);
					elem->setUpSparseMatrix(pointers);
				}
				pointers.getSolutionState()->setSparseMatrix();
				testtimer.stop();
				std::cout << "Time to setup profile: " << testtimer << std::endl;

			}
		}
	}
}

instantiate(Commands::Macro::SetUpSparseMatrix)