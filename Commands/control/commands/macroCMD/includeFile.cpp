

#include <preprocessDefine.h>
#include <globals.h>

#include <control/commands/macroCMD/includeFile.h>

#include <pointercollection/pointercollection.h>
#include <control/commands/InputParser.h>

#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <control/FEMProgram.h>

namespace FEMProject {
  extern std::string commentSymbols;
  namespace Commands {
    namespace Macro {
      
      
      template<typename prec, typename uint>
      includeFile<prec, uint>::includeFile(stringCommandHandler &cmd) {
        this->fileName = cmd.getStringTillDelim();
      }
      
      template<typename prec, typename uint>
      std::string includeFile<prec, uint>::printCommand() {
        std::string ret;
        return ret;
      }
      
      template<typename prec, typename uint>
      void includeFile<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
        
        std::string toOpen;
        toOpen = pointers.getInfoData()->fileNames[FileHandling::directory] + this->fileName;
        
        std::ifstream tempFile;
        tempFile.open(toOpen);
        stringCommandHandler Command;
        if(tempFile.is_open()){
          std::string tempStr;
          while(std::getline(tempFile,tempStr)){
            std::size_t pos = tempStr.find_first_of(commentSymbols);
            if (pos == std::string::npos) pos = tempStr.length();
            Command += tempStr.substr(0, pos);
          }
          tempFile.close();
          std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
          InputParser<prec, uint> Parser;
          Parser.parseMacro(Command, cmdQueue);
          program->processCommands(&pointers,cmdQueue);
        }
      }
    }
  }
}

instantiate(Commands::Macro::includeFile)
