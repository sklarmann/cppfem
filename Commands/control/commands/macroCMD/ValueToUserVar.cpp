
#include <preprocessDefine.h>

#include <control/commands/macroCMD/ValueToUserVar.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			ValueToUserVar<prec, uint>::ValueToUserVar(stringCommandHandler &cmd) {
				this->name = cmd.getRhs("varname");
				this->type = cmd.getRhs("type");
				this->nodeset = cmd.getRhs("nodeset");
				this->node = cmd.getRhs("node");
				this->dof = cmd.getRhs("dof");
				this->tnum = cmd.getRhs("tnum");

			}

			template<typename prec, typename uint>
			std::string ValueToUserVar<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void ValueToUserVar<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				std::string VarName = this->name;
				if (this->type == "vertex") {

				}
				else if (this->type == "edge") {

				}
				//pointers.getPropLoads()->setDt(pointers, this->dt);

			}
		}
	}
}

instantiate(Commands::Macro::ValueToUserVar)