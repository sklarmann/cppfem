
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class ReInput : public GenericCommand<prec, uint> {
			public:
				ReInput(stringCommandHandler &cmd);
				~ReInput() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new ReInput(cmd); };
			private:


			};
		}
	}
}

instantiateHeader(Commands::Macro::ReInput)
