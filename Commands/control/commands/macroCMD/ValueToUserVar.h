
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class ValueToUserVar : public GenericCommand<prec, uint> {
			public:
				ValueToUserVar(stringCommandHandler &cmd);
				~ValueToUserVar() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				void help();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new ValueToUserVar(cmd); };
			private:
				std::string type, nodeset, node, dof, name, tnum;

			};
		}
	}
}

instantiateHeader(Commands::Macro::GenericCommand)
