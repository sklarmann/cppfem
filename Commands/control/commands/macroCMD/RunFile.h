
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class RunFile : public GenericCommand<prec, uint> {
			public:
				RunFile(stringCommandHandler &cmd);
				~RunFile() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new RunFile(cmd); };
			private:
				std::string file;

			};
		}
	}
}

instantiateHeader(Commands::Macro::GenericCommand)
