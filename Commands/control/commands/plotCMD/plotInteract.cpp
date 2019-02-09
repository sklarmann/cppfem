
#include <preprocessDefine.h>

#include <control/commands/plotCMD/plotInteract.h>

#include <pointercollection/pointercollection.h>

#include <plot/vtkplotClassBase.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {

			template<typename prec, typename uint>
			Interact<prec, uint>::Interact(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string Interact<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Interact<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getVtkPlotInterface()->interact();
			}

#undef NAME
		}
	}
}

instantiate(Commands::Plot::Interact)
