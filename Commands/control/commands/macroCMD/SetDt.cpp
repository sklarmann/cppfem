
#include <preprocessDefine.h>

#include <control/commands/macroCMD/SetDt.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			SetDt<prec, uint>::SetDt(stringCommandHandler &cmd) {
				this->dt = cmd.getStringTillDelim();
			}

			template<typename prec, typename uint>
			std::string SetDt<prec, uint>::printCommand() {
				std::string ret;
				ret = "dt(" + this->dt + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void SetDt<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getPropLoads()->setDt(pointers, this->dt);

			}
		}
	}
}

instantiate(Commands::Macro::SetDt)