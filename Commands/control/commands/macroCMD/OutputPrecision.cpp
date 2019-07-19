
#include <preprocessDefine.h>

#include <control/commands/macroCMD/OutputPrecision.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <math/Userconstants.h>
#include <control/HandlingStructs.h>
#include <iomanip>



namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			OutputPrecision<prec, uint>::OutputPrecision(stringCommandHandler &cmd) {
				this->precision = cmd.remainingCommands();

			}

			template<typename prec, typename uint>
			std::string OutputPrecision<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void OutputPrecision<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				InfoData *info = pointers.getInfoData();
				Userconstants<prec> *userCons = pointers.getUserConstants();

				int digits = static_cast<int>(userCons->process(this->precision));
				
				info->Log.setPrecision(digits);

			}
		}
	}
}

instantiate(Commands::Macro::OutputPrecision)