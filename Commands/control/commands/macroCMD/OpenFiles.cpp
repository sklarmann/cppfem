
#include <preprocessDefine.h>

#include <control/commands/macroCMD/OpenFiles.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>


#include <filehandling/filehandling.h>


#include <iomanip>
#include <algorithm>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
#define NAME OpenFiles


			template<typename prec, typename uint>
			OpenFiles<prec, uint>::OpenFiles(stringCommandHandler &cmd) {
				this->file = cmd.getStringTillDelim();

				std::replace(this->file.begin(), this->file.end(), '\\', '/');
			}

			template<typename prec, typename uint>
			std::string OpenFiles<prec, uint>::printCommand() {
				std::string ret;
				ret = "open()";
				return ret;
			}

			template<typename prec, typename uint>
			void OpenFiles<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				#ifdef WIN32
				if (this->file.empty()) {
					set_files(pointers.getInfoData()->fileNames);
				}
				else {
					std::size_t pos = this->file.find_last_of('/');
					pointers.getInfoData()->fileNames[FileHandling::directory] = this->file.substr(0, pos + 1);
					pointers.getInfoData()->fileNames[FileHandling::infile] = this->file.substr(pos + 1, this->file.length() - pos);
					pointers.getInfoData()->fileNames[FileHandling::outfile] = pointers.getInfoData()->fileNames[FileHandling::infile] + ".log";
				}
				  
				#else
				  std::cout << "Please input filename with path:" << std::endl;
					std::string filename;
                    char ffilename[1024];
                    FILE *f = popen("zenity --file-selection", "r");
                    fgets(ffilename, 1024, f);
                    filename = ffilename;
                    std::size_t tpos = filename.find_last_not_of(" \t");
                    filename = filename.substr(0,tpos);
                    int pos = static_cast<int>(filename.find_last_of('/'));
                    pointers.getInfoData()->fileNames[FileHandling::directory] = filename.substr(0, pos + 1);
                    pointers.getInfoData()->fileNames[FileHandling::infile] = filename.substr(pos + 1, filename.length() - pos);
                    pointers.getInfoData()->fileNames[FileHandling::outfile]= pointers.getInfoData()->fileNames[FileHandling::infile] + ".log";
				#endif
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
