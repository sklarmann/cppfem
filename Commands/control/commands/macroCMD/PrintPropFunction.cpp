
#include <preprocessDefine.h>

#include <control/commands/macroCMD/PrintPropFunction.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PrintPropFunctions<prec, uint>::PrintPropFunctions(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string PrintPropFunctions<prec, uint>::printCommand() {
				std::string ret;
				ret = "printpropfunction()";
				return ret;
			}

			template<typename prec, typename uint>
			void PrintPropFunctions<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getPropLoads()->print(pointers);

			}
		}
	}
}

instantiate(Commands::Macro::PrintPropFunctions)