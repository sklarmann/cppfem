
#include <preprocessDefine.h>

#include <control/commands/plotCMD/plotmesh.h>

#include <pointercollection/pointercollection.h>

#include <plot/vtkplotClassBase.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {

			template<typename prec, typename uint>
			Mesh<prec, uint>::Mesh(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string Mesh<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Mesh<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				pointers.getVtkPlotInterface()->mesh(pointers);

			}
		}
	}
}

instantiate(Commands::Plot::Mesh)