
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class TimeIncr : public GenericCommand<prec, uint> {
			public:
				TimeIncr(stringCommandHandler &cmd);
				~TimeIncr() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new TimeIncr(cmd); };
			private:


			};
		}
	}
}