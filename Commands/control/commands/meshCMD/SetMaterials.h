
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <control/stringCommandHandler.h>

#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			class SetMaterial : public GenericCommand<prec, uint> {
			public:
				SetMaterial(stringCommandHandler &cmd);
				~SetMaterial() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:
				std::string number, elform, matform;
				stringCommandHandler elpara, matpara;

			};
		}
	}
}
