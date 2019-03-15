
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class OpenFiles : public GenericCommand<prec, uint> {
			public:
				OpenFiles(stringCommandHandler &cmd);
				~OpenFiles() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new OpenFiles(cmd); };
			private:


			};
		}
	}
}

instantiateHeader(Commands::Macro::OpenFiles)
