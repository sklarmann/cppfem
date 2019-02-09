
#include <preprocessDefine.h>

#include <control/commands/macroCMD/PropFunction.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>


#include <loads/PropfunctionHandler.h>

#include <math/Userconstants.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PropFunction<prec, uint>::PropFunction(stringCommandHandler &cmd) {
				this->snum = cmd.getRhs("num");
				this->function = cmd.getRhs("function");
				this->stmin = cmd.getRhs("tmin");
				this->stmax = cmd.getRhs("tmax");
			}

			template<typename prec, typename uint>
			std::string PropFunction<prec, uint>::printCommand() {
				std::string ret;
				ret = "propfunction(num=" + this->snum +
					";function=" + this->function +
					";tmin=" + this->stmin +
					";tmax=" + this->stmax + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void PropFunction<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				prec tmin = pointers.getUserConstants()->process(stmin);
				prec tmax = pointers.getUserConstants()->process(stmax);
				uint num = static_cast<uint>(pointers.getUserConstants()->process(snum));

				pointers.getPropLoads()->addFunction(pointers, num, this->function, tmin, tmax);
			}
		}
	}
}

instantiate(Commands::Macro::PropFunction)