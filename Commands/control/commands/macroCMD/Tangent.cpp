
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Tangent.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/Timer.h>

#include <finiteElements/ElementList.h>

#include <solver/GenericSolutionState.h>

#include <Eigen/SparseCore>
#include <Eigen/Dense>


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

				Timer<sec> testtimer;

				testtimer.start();
                pointers.getSolutionState()->assembleSystem();
				testtimer.stop();
                
				std::cout << "Assembly of System took: " << testtimer << std::endl;
				testtimer.start();
				pointers.getSolutionState()->factorize();
				testtimer.stop();
				std::cout << "Factorization took: " << testtimer << std::endl;
				pointers.getSolutionState()->solve();
				pointers.getSolutionState()->updateSolution();
			}
		}
	}
}

instantiate(Commands::Macro::Tangent)
