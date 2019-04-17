
#include <preprocessDefine.h>

#include <math/Userconstants.h>

#include <control/commands/macroCMD/ComputeConditionNumber.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {


			template<typename prec, typename uint>
			ComputeConditionNumber<prec, uint>::ComputeConditionNumber(stringCommandHandler &cmd) {


			}

			template<typename prec, typename uint>
			std::string ComputeConditionNumber<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void ComputeConditionNumber<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {


			}

		}
	}
}

instantiate(Commands::Macro::ComputeConditionNumber)