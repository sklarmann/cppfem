
#include <preprocessDefine.h>

#include <control/commands/macroCMD/OpenFiles.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>


#include <filehandling/filehandling.h>


#include <iomanip>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
#define NAME OpenFiles


			template<typename prec, typename uint>
			OpenFiles<prec, uint>::OpenFiles(stringCommandHandler &cmd) {
				
			}

			template<typename prec, typename uint>
			std::string OpenFiles<prec, uint>::printCommand() {
				std::string ret;
				ret = "open()";
				return ret;
			}

			template<typename prec, typename uint>
			void OpenFiles<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				
				set_files(pointers.getInfoData()->fileNames);

				pointers.getInfoData()->Log(BasicLog, BasicLog) << std::setw(30) << std::left << "Current Directory: "
					<< std::setw(70) << std::right << pointers.getInfoData()->fileNames[FileHandling::directory] << std::endl
					<< std::setw(30) << std::left << "InputFile: "
					<< std::setw(70) << std::right << pointers.getInfoData()->fileNames[FileHandling::infile] << std::endl
					<< std::setw(30) << std::left << "LogFile: "
					<< std::setw(70) << std::right << pointers.getInfoData()->fileNames[FileHandling::outfile] << std::endl;

			}
		}
	}
}

instantiate(Commands::Macro::OpenFiles)
