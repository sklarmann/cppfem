
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			class PrintPropFunctions : public GenericCommand<prec, uint> {
			public:
				PrintPropFunctions(stringCommandHandler &cmd);
				~PrintPropFunctions() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new PrintPropFunctions(cmd); };
			private:


			};

		}
	}
}
