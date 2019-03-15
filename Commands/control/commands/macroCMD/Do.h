
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>
#include <control/stringCommandHandler.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			class Do : public GenericCommand<prec, uint> {
			public:
				Do(stringCommandHandler &cmd);
				~Do() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Do(cmd); };
			private:
				stringCommandHandler toProcess;
				std::string times;
			};

		}
	}
}

instantiateHeader(Commands::Macro::Output)
