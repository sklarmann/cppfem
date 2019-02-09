
#include <preprocessDefine.h>

#include <control/commands/macroCMD/CommandHistory.h>
#include <control/stringCommandHandler.h>
#include <control/FEMProgram.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PrintHistory<prec, uint>::PrintHistory(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string PrintHistory<prec, uint>::printCommand() {
				std::string ret;
				ret = "history()";
				return ret;
			}

			template<typename prec, typename uint>
			void PrintHistory<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				program->printHist();
			}
		}
	}
}

instantiate(Commands::Macro::PrintHistory)