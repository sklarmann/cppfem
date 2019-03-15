
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <string>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class Tangent : public GenericCommand<prec, uint> {
			public:
				Tangent(stringCommandHandler &cmd);
				~Tangent() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new Tangent(cmd); };
			private:


			};
		}
	}
}
