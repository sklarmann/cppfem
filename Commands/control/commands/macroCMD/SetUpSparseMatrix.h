
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class SetUpSparseMatrix : public GenericCommand<prec, uint> {
			public:
				SetUpSparseMatrix(stringCommandHandler &cmd);
				~SetUpSparseMatrix() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new SetUpSparseMatrix(cmd); };
			private:


			};
		}
	}
}
