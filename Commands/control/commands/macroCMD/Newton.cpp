

#include <preprocessDefine.h>

#include <control/commands/macroCMD/Newton.h>

#include <pointercollection/pointercollection.h>

#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

#include <control/FEMProgram.h>

#include <solver/GenericSolutionState.h>

#include <control/Timer.h>
#include <sstream>

namespace FEMProject {
  namespace Commands {
    namespace Macro {
      
      
      template<typename prec, typename uint>
      Newton<prec, uint>::Newton(stringCommandHandler &cmd) {
        this->maxItStr = cmd.getRhs("maxiteration");
        this->refResStr = cmd.getRhs("residual");
        this->damped = cmd.getRhs("damped");
      }
      
      template<typename prec, typename uint>
      std::string Newton<prec, uint>::printCommand() {
        std::string ret;
        return ret;
      }
      
      template<typename prec, typename uint>
      void Newton<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
        prec refResidual;uint maxIt;
        uint damp;
        if(this->refResStr.empty()){
          refResidual = static_cast<prec>(1e-12);
        } else {
          refResidual = pointers.getUserConstants()->process(this->refResStr);
        }
        if(this->maxItStr.empty()){
          maxIt=10;
        } else {
          maxIt = static_cast<uint>(pointers.getUserConstants()->process(this->maxItStr));
        }
        if(this->damped.empty()){
            damp=0;
        } else {
          damp = static_cast<uint>(pointers.getUserConstants()->process(this->damped));
        }
        
        InfoData *info;
        info = pointers.getInfoData();
        info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
          "Started Newton Iteration with Maximum " << maxIt << 
          " Iterations.\n" << 
          "Stopping if Residual is less than " << refResidual << "." 
          << std::endl;
        
          
        Timer<sec> testtimer;
          
        GenericSolutionState<prec,uint> *sol = pointers.getSolutionState();
        testtimer.start();
        sol->assembleSystem();
        testtimer.stop();
        info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
           "  Time for assembly of system:         "  << testtimer.time() << std::endl;
        
        prec residual0 = sol->residual();
        prec residual = 1;
        uint currIteration = 0;
        
        
        
        
        while(currIteration<maxIt && residual > refResidual){
          ++currIteration;
          testtimer.start();
          sol->factorize();
          testtimer.stop();
          info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
             "  Time for factorization of system:  "  << testtimer.time() << std::endl;
          testtimer.start();
          
          sol->solve();
          if(currIteration == 1 || damp == 0 ){
              sol->updateSolution();
          } else {
              sol->dampedSolutionUpdate();
          }
          testtimer.stop();
          info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
             "  Time for solution of system:       "  << testtimer.time() << std::endl;
          testtimer.start();
          sol->assembleSystem();
          testtimer.stop();
          info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << 
           "  Time for assembly of system:         "  << testtimer.time() << std::endl;
          residual = sol->residual();
          prec cres = residual;
          residual /= residual0;
          
          info->Log(LogLevel::BasicLog,LogLevel::BasicLog) 
            << "  Initial residual:      " << residual0 << "\n"
            << "  Current residual:      " << cres << "\n"
            << "  Current residual norm: " << residual << "\n"
            << "    Iteration " << currIteration << " / " << maxIt <<std::endl;
        }
      }
    }
  }
}

instantiate(Commands::Macro::Newton)
