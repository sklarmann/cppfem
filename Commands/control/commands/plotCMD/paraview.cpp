
#include <preprocessDefine.h>

#include <control/commands/plotCMD/paraview.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <math/Userconstants.h>

#include <plot/vtkplotClassBase.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {

			template<typename prec, typename uint>
			Paraview<prec, uint>::Paraview(stringCommandHandler &cmd) {
			}

			template<typename prec, typename uint>
			std::string Paraview<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Paraview<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				pointers.getVtkPlotInterface()->toFile(pointers);
			}
		}
	}
}

instantiate(Commands::Plot::Paraview)
