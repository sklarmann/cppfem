
#include <preprocessDefine.h>

#include <control/commands/macroCMD/RunFile.h>

#include <control/stringCommandHandler.h>


#include <control/FEMProgram.h>
#include <control/HandlingStructs.h>
#include <pointercollection/pointercollection.h>

#include <algorithm>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			RunFile<prec, uint>::RunFile(stringCommandHandler &cmd) {
				this->file = cmd.getStringTillDelim();
				std::replace(this->file.begin(), this->file.end(), '\\', '/');
			}

			template<typename prec, typename uint>
			std::string RunFile<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void RunFile<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				PointerCollection<prec, uint> ptr;
				InfoData *nInfo = new InfoData;
				ptr.setInfoData(nInfo);
				FEMProgram<prec, uint> prog(&ptr);

				std::string fileWDir, toParse;
				fileWDir = pointers.getInfoData()->fileNames[FileHandling::directory];
				fileWDir += this->file;
				toParse = "open(" + fileWDir + ")";
				toParse += "processfiles()";

				prog.parseExternalMacro(&ptr, toParse);

				delete nInfo;

			}
		}
	}
}

instantiate(Commands::Macro::RunFile)