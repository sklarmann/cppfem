
#pragma once

#include <preprocessDefine.h>

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			class PrintHistory : public GenericCommand<prec, uint> {
			public:
				PrintHistory(stringCommandHandler &cmd);
				~PrintHistory() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new PrintHistory<prec,uint>(cmd); };
			private:


			};
		}
	}
}

// instantiateHeader(Commands::Macro::PrintHistory)
