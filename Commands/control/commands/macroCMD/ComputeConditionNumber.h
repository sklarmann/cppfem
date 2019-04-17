
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class ComputeConditionNumber : public GenericCommand<prec, uint> {
			public:
				ComputeConditionNumber(stringCommandHandler &cmd);
				~ComputeConditionNumber() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new ComputeConditionNumber(cmd); };
			private:
				
			};
		}
	}
}

instantiateHeader(Commands::Macro::GenericCommand)
