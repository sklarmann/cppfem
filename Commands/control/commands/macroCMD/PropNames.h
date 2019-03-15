
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class PropNames : public GenericCommand<prec, uint> {
			public:
				PropNames(stringCommandHandler &cmd);
				~PropNames() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new PropNames(cmd); };
			private:
				std::string timename, dtname;

			};
		}
	}
}

instantiateHeader(Commands::Macro::PropNames)
