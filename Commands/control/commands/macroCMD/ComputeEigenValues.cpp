
#include <preprocessDefine.h>

#include <control/commands/macroCMD/ComputeEigenValues.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {


			template<typename prec, typename uint>
			eigenValues<prec, uint>::eigenValues(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string eigenValues<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void eigenValues<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getSolutionState()->computeEigenValues();

			}

		}
	}
}

instantiate(Commands::Macro::eigenValues)