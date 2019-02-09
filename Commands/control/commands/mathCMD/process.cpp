
#include <preprocessDefine.h>

#include <control/commands/mathCMD/process.h>
#include <control/stringCommandHandler.h>
#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>



namespace FEMProject {
	namespace Commands {
		namespace Math {

			template<typename prec, typename uint>
			Process<prec, uint>::Process(stringCommandHandler &cmd) {

				while (!cmd.empty()) {
					this->inputs.push_back(cmd.getStringTillDelim());
				}

			}

			template<typename prec, typename uint>
			std::string Process<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Process<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				auto size = this->inputs.size();
				for (auto i = 0; i < size; ++i) {
					pointers.getUserConstants()->process(this->inputs[i]);
				}
			}
		}
	}
}

instantiate(Commands::Math::Process)