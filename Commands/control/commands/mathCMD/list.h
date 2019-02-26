
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Math {
			template<typename prec, typename uint>
			class List : public GenericCommand<prec, uint> {
			public:
				List(stringCommandHandler &cmd);
				~List() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand *New(stringCommandHandler &cmd) { return new List(cmd); };
			private:


			};
		}
	}
}