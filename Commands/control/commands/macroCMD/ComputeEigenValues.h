
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class eigenValues : public GenericCommand<prec, uint> {
			public:
				eigenValues(stringCommandHandler &cmd);
				~eigenValues() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new eigenValues(cmd); };
			private:
				std::string max, number, number2, tol;
			};
		}
	}
}

instantiateHeader(Commands::Macro::GenericCommand)
