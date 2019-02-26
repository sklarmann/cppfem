
#pragma once
#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			class printInfo : public GenericCommand<prec, uint> {
			public:
				printInfo(stringCommandHandler &cmd);
				~printInfo() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new printInfo(cmd); };
			private:


			};

		}
	}
}

instantiateHeader(Commands::Macro::printInfo)