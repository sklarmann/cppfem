
#include <preprocessDefine.h>

#include <control/commands/macroCMD/PrintSpMat.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>

#include <loads/PropfunctionHandler.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PrintSpMat<prec, uint>::PrintSpMat(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string PrintSpMat<prec, uint>::printCommand() {
				std::string ret;
				ret = "printspmat()";
				return ret;
			}

			template<typename prec, typename uint>
			void PrintSpMat<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getSolutionState()->printSpMat();

			}
		}
	}
}

instantiate(Commands::Macro::PrintSpMat)