
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Tangent.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/Timer.h>

#include <finiteElements/ElementList.h>

#include <solver/GenericSolutionState.h>

#include <math/Userconstants.h>

#include <Eigen/SparseCore>
#include <Eigen/Dense>

#include <control/OutputHandler.h>
#include <control/HandlingStructs.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Tangent<prec, uint>::Tangent(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string Tangent<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Tangent<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
                InfoData *info;
                info = pointers.getInfoData();
				Timer<sec> testtimer;

				testtimer.start();
                pointers.getSolutionState()->assembleSystem();
				testtimer.stop();
                
				info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << "Assembly of System took: " << testtimer.time() << std::endl;
                std::stringstream temp;
                temp << "CPPFEMAssemblyTime=";
                temp << testtimer.timeVal();
                std::string tempi = temp.str();
                std::cout << tempi << std::endl;
                pointers.getUserConstants()->process(tempi);
				testtimer.start();
				pointers.getSolutionState()->factorize();
				testtimer.stop();
                temp.str(std::string());
                temp << "CPPFEMFactorizationTime=" << testtimer.timeVal();
                tempi = temp.str();
                std::cout << tempi << std::endl;
                pointers.getUserConstants()->process(tempi);
				info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << "Factorization took: " << testtimer.time() << std::endl;
                
                testtimer.start();
				pointers.getSolutionState()->solve();
				pointers.getSolutionState()->updateSolution();
                testtimer.stop();
                
                temp.str(std::string());
                temp << "CPPFEMSolveTime=" << testtimer.timeVal();
                tempi = temp.str();
                std::cout << tempi << std::endl;
                pointers.getUserConstants()->process(tempi);
				info->Log(LogLevel::BasicLog,LogLevel::BasicLog) << "Solution step took: " << testtimer.time() << std::endl;
			}
		}
	}
}

instantiate(Commands::Macro::Tangent)
