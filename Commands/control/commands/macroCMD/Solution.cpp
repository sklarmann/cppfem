
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Solution.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <solver/SolutionTypes.h>
#include <solver/StaticSolutionState.h>
#include <solver/TransientSolutionNewmark.h>

#include <math/Userconstants.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Solution<prec, uint>::Solution(stringCommandHandler &cmd) {
				this->name = cmd.getStringTillDelim();
				while (!cmd.empty()) {
					this->params.insert(cmd.getNextPair());
				}
			}

			template<typename prec, typename uint>
			std::string Solution<prec, uint>::printCommand() {
				std::string ret;
				ret = "solution(" + this->name + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void Solution<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				Userconstants<prec> *ucons = pointers.getUserConstants();

				std::map<std::string, prec> passParam;
				for (auto it = this->params.begin(); it != this->params.end(); ++it) {
					passParam[it->first] = ucons->process(it->second);
				}


				SolutionTypes type = SolutionTypes::GenericSolutionState;
				if (this->name == "static") {
					type = SolutionTypes::StaticSolutionState;
				}
				else if (this->name == "transnewmark") {
					type = SolutionTypes::TransientSolutionNewmark;
				}
				switch (type) {
				case SolutionTypes::StaticSolutionState:
					pointers.setSolutionState(new StaticSolutionState<prec, uint>(&pointers, passParam));
					break;
				case SolutionTypes::TransientSolutionNewmark:
					pointers.setSolutionState(new TransientSolutionNewmark<prec, uint>(&pointers, passParam));
					break;
				}
			}
		}
	}
}

instantiate(Commands::Macro::Solution)
