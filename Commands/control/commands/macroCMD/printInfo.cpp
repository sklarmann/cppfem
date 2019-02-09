
#include <preprocessDefine.h>

#include <control/commands/macroCMD/printInfo.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <equations/GeometryData.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			printInfo<prec, uint>::printInfo(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string printInfo<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void printInfo<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				pointers.getGeometryData()->print();
			}

		}
	}
}

instantiate(Commands::Macro::printInfo)