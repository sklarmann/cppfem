
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Threads.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <math/Userconstants.h>

#include <omp.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Threads<prec, uint>::Threads(stringCommandHandler &cmd) {
				this->numThreads = cmd.getStringTillDelim();
			}

			template<typename prec, typename uint>
			std::string Threads<prec, uint>::printCommand() {
				std::string ret;
				ret = "threads(" + this->numThreads + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void Threads<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				uint n = static_cast<uint>(pointers.getUserConstants()->process(this->numThreads));
				omp_set_num_threads(n);
			}
		}
	}
}

instantiate(Commands::Macro::Threads)