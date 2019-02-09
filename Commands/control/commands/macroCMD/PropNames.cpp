
#include <preprocessDefine.h>

#include <control/commands/macroCMD/PropNames.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PropNames<prec, uint>::PropNames(stringCommandHandler &cmd) {
				this->timename = cmd.getRhs("timename");
				this->dtname = cmd.getRhs("dtname");
			}

			template<typename prec, typename uint>
			std::string PropNames<prec, uint>::printCommand() {
				std::string ret;
				ret = "propnames(timename=" + this->timename
					+ ";dtname=" + this->dtname + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void PropNames<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				pointers.getPropLoads()->setNames(pointers, this->timename, this->dtname);

			}
		}
	}
}

instantiate(Commands::Macro::PropNames)