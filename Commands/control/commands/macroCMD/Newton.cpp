

#include <preprocessDefine.h>

#include <control/commands/macroCMD/Newton.h>

#include <pointercollection/pointercollection.h>

#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

#include <control/FEMProgram.h>

#include <solver/GenericSolutionState.h>

namespace FEMProject {
  namespace Commands {
    namespace Macro {
      
      
      template<typename prec, typename uint>
      Newton<prec, uint>::Newton(stringCommandHandler &cmd) {
        this->maxItStr = cmd.getRhs("maxiteration");
        this->refResStr = cmd.getRhs("residual");
      }
      
      template<typename prec, typename uint>
      std::string Newton<prec, uint>::printCommand() {
        std::string ret;
        return ret;
      }
      
      template<typename prec, typename uint>
      void Newton<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
        prec refResidual;uint maxIt;
        
        if(this->refResStr.empty()){
          refResidual = 1e-12;
        } else {
          refResidual = pointers.getUserConstants()->process(this->refResStr);
        }
        if(this->maxItStr.empty()){
          maxIt=10;
        } else {
          maxIt = static_cast<uint>(pointers.getUserConstants()->process(this->maxItStr));
        }
        
        InfoData *info;
        info = pointers.getInfoData();
        info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
          "Started Newton Iteration with Maximum " << maxIt << 
          " Iterations.\n" << 
          "Stopping if Residual is less than " << refResidual << "." 
          << std::endl;
        
        GenericSolutionState<prec,uint> *sol = pointers.getSolutionState();
        sol->assembleSystem();
        
        prec residual0 = sol->residual();
        prec residual = 1;
        uint currIteration = 0;
        while(currIteration<maxIt && residual > refResidual){
          ++currIteration;
          sol->factorize();
          sol->solve();
          sol->updateSolution();
          sol->assembleSystem();
          residual = sol->residual();
          residual /= residual0;
          info->Log(LogLevel::BasicLog,LogLevel::BasicLog) 
            << "Current residual norm: " << residual 
            << "  initial residual " << residual0 
            << std::endl;
        }
      }
    }
  }
}

instantiate(Commands::Macro::Newton)
