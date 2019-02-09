
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Solution.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <solver/SolutionTypes.h>
#include <solver/StaticSolutionState.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Solution<prec, uint>::Solution(stringCommandHandler &cmd) {
				this->name = cmd.getStringTillDelim();
			}

			template<typename prec, typename uint>
			std::string Solution<prec, uint>::printCommand() {
				std::string ret;
				ret = "solution(" + this->name + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void Solution<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				SolutionTypes type = SolutionTypes::GenericSolutionState;
				if (this->name == "static") {
					type = SolutionTypes::StaticSolutionState;
				}
				switch (type) {
				case SolutionTypes::StaticSolutionState:
					pointers.setSolutionState(new StaticSolutionState<prec, uint>(&pointers));
					break;
				}
			}
		}
	}
}

instantiate(Commands::Macro::Solution)
