
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class Solution : public GenericCommand<prec, uint> {
			public:
				Solution(stringCommandHandler &cmd);
				~Solution() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Solution(cmd); };
			private:
				std::string name;

			};
		}
	}
}
