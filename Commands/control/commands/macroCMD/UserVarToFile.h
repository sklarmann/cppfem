
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>


namespace FEMProject {
	namespace Commands {
		namespace Macro {
			template<typename prec, typename uint>
			class UserVarToFile : public GenericCommand<prec, uint> {
			public:
				UserVarToFile(stringCommandHandler &cmd);
				~UserVarToFile() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				void help();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new UserVarToFile(cmd); };
			private:
				std::string varName, fileName, newFile;

			};
		}
	}
}
