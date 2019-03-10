
#pragma once

#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>
#include <string>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class PrintSolution : public GenericCommand<prec, uint> {
			public:
				PrintSolution(stringCommandHandler &cmd);
				~PrintSolution() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new PrintSolution(cmd); };
			private:
				std::string type, number, meshId;

			};
		}
	}
}