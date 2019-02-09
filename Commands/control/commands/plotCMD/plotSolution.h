
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {
			template<typename prec, typename uint>
			class Solution : public GenericCommand<prec, uint> {
			public:
				Solution(stringCommandHandler &cmd);
				~Solution() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:
				std::string meshId, comp;

			};
		}
	}
}
