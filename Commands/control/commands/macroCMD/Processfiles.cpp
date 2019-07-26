
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Processfiles.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/commands/InputParser.h>
#include <control/FEMProgram.h>

#include <filehandling/filehandling.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Processfiles<prec, uint>::Processfiles(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string Processfiles<prec, uint>::printCommand() {
				std::string ret;
				ret = "processfiles()";
				return ret;
			}

			template<typename prec, typename uint>
			void Processfiles<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				std::string outfile;
				outfile = pointers.getInfoData()->fileNames[FileHandling::directory] + pointers.getInfoData()->fileNames[FileHandling::outfile];
				//outfile = pointers.getInfoData()->fileNames[FileHandling::outfile];
				pointers.getInfoData()->Log.openLogFile(outfile);
				pointers.getInfoData()->Log(LogLevel::FullLog, LogLevel::FullLog) << "Output File opened!" << std::endl;

				std::ifstream tempiFile;
				std::string tempStr;
				stringCommandHandler Command;
				tempiFile.open(pointers.getInfoData()->fileNames[FileHandling::directory] + pointers.getInfoData()->fileNames[FileHandling::infile]);
				//tempiFile.open(pointers.getInfoData()->fileNames[FileHandling::infile]);

				std::string comment = "!%";

				while (std::getline(tempiFile, tempStr)) {
					std::size_t pos = tempStr.find_first_of(comment);
					if (pos == std::string::npos) pos = tempStr.length();
					Command += tempStr.substr(0, pos);
				}
				tempiFile.close();
				//this->MacroInteraction(Command);
				std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
				InputParser<prec, uint> Parser;
				Parser.parseMacro(Command, cmdQueue);
				program->processCommands(&pointers,cmdQueue);
				//while (!cmdQueue.empty()) {
				//	Commands::GenericCommand<prec, uint>* procCommand;
				//	procCommand = cmdQueue.front();
				//	cmdQueue.pop();
				//	this->CommandHistory.push_back(procCommand);
				//	procCommand->run(this->pointers, this);
				//}

			}
		}
	}
}

instantiate(Commands::Macro::Processfiles)
