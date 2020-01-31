

#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>
#include <control/stringCommandHandler.h>

namespace FEMProject {
  namespace Commands {
    namespace Macro {
      
      template<typename prec, typename uint>
      class Newton : public GenericCommand<prec, uint> {
      public:
        Newton(stringCommandHandler &cmd);
        ~Newton() {};
        void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
        std::string printCommand();
        static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Newton(cmd); };
      private:
        std::string maxItStr, refResStr, damped;
      }; 
      
    }
  }
}

instantiateHeader(Commands::Macro::Newton)
