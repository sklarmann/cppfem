
#include <preprocessDefine.h>

#include <control/commands/macroCMD/ReInput.h>

#include <control/FEMProgram.h>
#include <control/stringCommandHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			ReInput<prec, uint>::ReInput(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string ReInput<prec, uint>::printCommand() {
				std::string ret;
				ret = "rinp()";
				return ret;
			}

			template<typename prec, typename uint>
			void ReInput<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				program->ReInput(pointers);
			}
		}
	}
}

instantiate(Commands::Macro::ReInput)