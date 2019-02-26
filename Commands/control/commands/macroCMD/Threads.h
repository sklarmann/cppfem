
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class Threads : public GenericCommand<prec, uint> {
			public:
				Threads(stringCommandHandler &cmd);
				~Threads() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new Threads(cmd); };
			private:
				std::string numThreads;

			};
		}
	}
}