
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class SetDt : public GenericCommand<prec, uint> {
			public:
				SetDt(stringCommandHandler &cmd);
				~SetDt() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:
				std::string dt;

			};
		}
	}
}

instantiateHeader(Commands::Macro::GenericCommand)