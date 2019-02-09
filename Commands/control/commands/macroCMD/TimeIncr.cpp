
#include <preprocessDefine.h>

#include <control/commands/macroCMD/TimeIncr.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			TimeIncr<prec, uint>::TimeIncr(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string TimeIncr<prec, uint>::printCommand() {
				std::string ret;
				ret = "timeincr()";
				return ret;
			}

			template<typename prec, typename uint>
			void TimeIncr<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getPropLoads()->incrTime(pointers);
			}
		}
	}
}

instantiate(Commands::Macro::TimeIncr)