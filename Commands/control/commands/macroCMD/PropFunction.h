
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <preprocessDefine.h>

namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class PropFunction : public GenericCommand<prec, uint> {
			public:
				PropFunction(stringCommandHandler &cmd);
				~PropFunction() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new PropFunction(cmd); };
			private:
				std::string snum;
				std::string function;
				std::string stmin;
				std::string stmax;

			};
		}
	}
}

instantiateHeader(Commands::Macro::PropFunction)
