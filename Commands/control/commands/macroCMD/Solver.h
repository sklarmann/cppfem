
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class Solver : public GenericCommand<prec, uint> {
			public:
				Solver(stringCommandHandler &cmd);
				~Solver() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Solver(cmd); };
				void help();
			private:
				std::string solver;

			};
		}
	}
}
