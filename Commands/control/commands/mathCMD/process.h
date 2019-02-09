
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>
#include <string>
#include <vector>


namespace FEMProject {
	namespace Commands {
		namespace Math {
			template<typename prec, typename uint>
			class Process : public GenericCommand<prec, uint> {
			public:
				Process(stringCommandHandler &cmd);
				~Process() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:
				std::vector<std::string> inputs;

			};
		}
	}
}