
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			class Output : public GenericCommand<prec, uint> {
			public:
				Output(stringCommandHandler &cmd);
				~Output() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new Output(cmd); };
			private:
				std::string writeInfo;
				std::string printInfo;

			};

		}
	}
}

instantiateHeader(Commands::Macro::Output)