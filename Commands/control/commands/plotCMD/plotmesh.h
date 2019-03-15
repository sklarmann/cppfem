
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

namespace FEMProject {
	namespace Commands {
		namespace Plot {
			template<typename prec, typename uint>
			class Mesh : public GenericCommand<prec, uint> {
			public:
				Mesh(stringCommandHandler &cmd);
				~Mesh() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Mesh(cmd); };
			private:


			};
		}
	}
}
