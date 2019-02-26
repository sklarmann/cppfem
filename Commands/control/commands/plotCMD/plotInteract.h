
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Plot {
			template<typename prec, typename uint>
			class Interact : public GenericCommand<prec, uint> {
			public:
				Interact(stringCommandHandler &cmd);
				~Interact() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new Interact(cmd); };
			private:


			};
		}
	}
}