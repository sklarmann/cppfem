
#include <preprocessDefine.h>

#include <control/commands/macroCMD/ResetSolution.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			ResetSolution<prec, uint>::ResetSolution(stringCommandHandler &cmd) {
			}

			template<typename prec, typename uint>
			std::string ResetSolution<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void ResetSolution<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				pointers.getSolutionState()->resetSolution();
			}
		}
	}
}

instantiate(Commands::Macro::ResetSolution)