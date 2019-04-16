
#include <preprocessDefine.h>

#include <math/Userconstants.h>

#include <control/commands/macroCMD/ComputeEigenValues.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {


			template<typename prec, typename uint>
			eigenValues<prec, uint>::eigenValues(stringCommandHandler &cmd) {

				this->max = cmd.getRhs("max");
				this->number = cmd.getRhs("number");
				this->number2 = cmd.getRhs("search");
				this->tol = cmd.getRhs("tol");

			}

			template<typename prec, typename uint>
			std::string eigenValues<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void eigenValues<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				Userconstants<prec> *ucons = pointers.getUserConstants();
				bool pmax = false;
				uint n1, n2;
				prec ptol;

				if (this->max == "true") pmax = true;
				if (!this->number.empty()) {
					n1 = ucons->process(this->number);
				}
				if (!this->number2.empty()) {
					n2 = ucons->process(this->number2);
				}
				else {
					n2 = n1 * (prec)2;
				}

				if (!this->tol.empty()) {
					ptol = ucons->process(this->tol);
				}
				else {
					ptol = (prec) 1e-10;
				}

				pointers.getSolutionState()->computeEigenValues(n1,n2,pmax,ptol);

			}

		}
	}
}

instantiate(Commands::Macro::eigenValues)