
#pragma once

#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>
#include <vector>
#include <string>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			class AddVertex : public GenericCommand<prec, uint> {
			public:
				AddVertex(stringCommandHandler &cmd);
				~AddVertex() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new AddVertex(cmd); };
			private:
				std::vector<std::string> coordinates;

			};
		}
	}
}
