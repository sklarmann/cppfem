
#include <preprocessDefine.h>

#include <control/commands/plotCMD/plotSolution.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <math/Userconstants.h>

#include <plot/vtkplotClassBase.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {

			template<typename prec, typename uint>
			Solution<prec, uint>::Solution(stringCommandHandler &cmd) {
				this->meshId = cmd.getRhs("meshid");
				this->comp = cmd.getRhs("comp");
			}

			template<typename prec, typename uint>
			std::string Solution<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Solution<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				uint idnum = static_cast<uint>(pointers.getUserConstants()->process(this->meshId));
				uint comp = static_cast<uint>(pointers.getUserConstants()->process(this->comp));
				pointers.getVtkPlotInterface()->solution(pointers, idnum, comp);
			}
		}
	}
}

instantiate(Commands::Plot::Solution)