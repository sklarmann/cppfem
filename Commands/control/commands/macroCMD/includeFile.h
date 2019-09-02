
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>
#include <control/stringCommandHandler.h>

namespace FEMProject {
  namespace Commands {
    namespace Macro {
      
      template<typename prec, typename uint>
      class includeFile : public GenericCommand<prec, uint> {
      public:
        includeFile(stringCommandHandler &cmd);
        ~includeFile() {};
        void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
        std::string printCommand();
        static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new includeFile(cmd); };
      private:
        std::string fileName;
      };
      
    }
  }
}

instantiateHeader(Commands::Macro::includeFile)

