
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Output.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {


			template<typename prec, typename uint>
			Output<prec, uint>::Output(stringCommandHandler &cmd) {
				this->writeInfo = cmd.getRhs("writeinfo");
				this->printInfo = cmd.getRhs("printinfo");
			}

			template<typename prec, typename uint>
			std::string Output<prec, uint>::printCommand() {
				std::string ret;
				ret = "output(writeinfo=" + this->writeInfo + ";printinfo=" + this->printInfo + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void Output<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				uint writeInfoNum = static_cast<uint>(pointers.getUserConstants()->process(this->writeInfo) + 0.5);
				uint printInfoNum = static_cast<uint>(pointers.getUserConstants()->process(this->printInfo) + 0.5);
				

				LogLevel File, Print;

				switch (writeInfoNum) {
				case 0:
					File = NoLog;
					break;
				case 1:
					File = BasicLog;
					break;
				case 2:
					File = FullLog;
					break;
				}


				switch (printInfoNum) {
				case 0:
					Print = NoLog;
					break;
				case 1:
					Print = BasicLog;
					break;
				case 2:
					Print = FullLog;
					break;
				}


				pointers.getInfoData()->Log.setLogLevel(File, Print);

				
			}
		}
	}
}

instantiate(Commands::Macro::Output)