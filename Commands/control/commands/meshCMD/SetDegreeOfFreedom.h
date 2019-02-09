
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			class SetDegreesOfFreedom : public GenericCommand<prec, uint> {
			public:
				SetDegreesOfFreedom(stringCommandHandler &cmd);
				~SetDegreesOfFreedom() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:


			};
		}
	}
}