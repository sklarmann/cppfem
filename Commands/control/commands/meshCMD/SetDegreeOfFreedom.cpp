

#include <preprocessDefine.h>

#include <control/commands/meshCMD/SetDegreeOfFreedom.h>

#include <pointercollection/pointercollection.h>

#include <equations/EquationHandler.h>

#include <finiteElements/ElementList.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			SetDegreesOfFreedom<prec, uint>::SetDegreesOfFreedom(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string SetDegreesOfFreedom<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void SetDegreesOfFreedom<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				ElementList<prec, uint> *elemList = pointers.getElementList();
				uint numberOfElements;
				numberOfElements = elemList->getNumberOfElements();


				for (uint i = 0; i < numberOfElements; ++i) {
					GenericFiniteElement<prec, uint> *elem;
					elem = elemList->getElement(i);
					elem->GenericSetDegreesOfFreedom();
				}

				pointers.getEquationHandler()->update();
				pointers.getEquationHandler()->updateEquations();
			}
		}
	}
}

instantiate(Commands::Mesh::SetDegreesOfFreedom)