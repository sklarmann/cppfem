
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Do.h>

#include <pointercollection/pointercollection.h>

#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

#include <control/FEMProgram.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {


			template<typename prec, typename uint>
			Do<prec, uint>::Do(stringCommandHandler &cmd) {
				this->times = cmd.getRhs("times");
				this->toProcess = cmd;
			}

			template<typename prec, typename uint>
			std::string Do<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Do<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				
				Userconstants<prec> *userCons = pointers.getUserConstants();
				uint endLoop = static_cast<uint>(userCons->process(this->times));
				stringCommandHandler toPass;
				for (uint i = 0; i < endLoop; ++i) {
					toPass = this->toProcess;
					program->processCommands(&pointers, toPass);
				}
				
			}
		}
	}
}

instantiate(Commands::Macro::Do)