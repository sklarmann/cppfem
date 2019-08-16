
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			class linkDofs : public GenericCommand<prec, uint> {
			public:
				linkDofs(stringCommandHandler &cmd);
				~linkDofs() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new linkDofs(cmd); };
			private:
				std::string maType, maTnum, maNodeset, maNode, maDof;
				std::string slType, slTnum, slNodeset, slNode, slDof;
				std::string fact;

			};
		}
	}
}
