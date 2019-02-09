
#pragma once

#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
#define NAME OpenFiles
			template<typename prec, typename uint>
			class NAME : public GenericCommand<prec, uint> {
			public:
				NAME(stringCommandHandler &cmd);
				~NAME() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:


			};

			template<typename prec, typename uint>
			NAME<prec, uint>::NAME(stringCommandHandler &cmd) {

			}

			template<typename prec, typename uint>
			std::string NAME<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void NAME<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {


			}

#undef NAME
		}
	}
}