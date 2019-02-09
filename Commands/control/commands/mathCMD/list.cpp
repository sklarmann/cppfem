
#include <preprocessDefine.h>

#include <control/commands/mathCMD/list.h>
#include <control/stringCommandHandler.h>
#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>
#include <math/Userconstants.h>


namespace FEMProject {
	namespace Commands {
		namespace Math {

			template<typename prec, typename uint>
			List<prec, uint>::List(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string List<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void List<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				pointers.getInfoData()->Log(LogLevel::BasicLog, LogLevel::BasicLog) << *pointers.getUserConstants() << std::endl;
			}
		}
	}
}

instantiate(Commands::Math::List)