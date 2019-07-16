
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class OutputPrecision : public GenericCommand<prec, uint> {
			public:
				OutputPrecision(stringCommandHandler &cmd);
				~OutputPrecision() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new OutputPrecision(cmd); };
			private:
				std::string precision;

			};
		}
	}
}
