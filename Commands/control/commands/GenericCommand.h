


#pragma once

#include <forwarddeclaration.h>

#include <preprocessDefine.h>

#include <string>


namespace FEMProject {

	namespace Commands {

		template <typename prec, typename uint>
		class GenericCommand {
		public:
			GenericCommand() {};
			virtual ~GenericCommand() {};
			virtual void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program) {};
			virtual std::string printCommand() { std::string a; return a; };
			friend std::ostream &operator<<(std::ostream &output,
				GenericCommand<prec,uint> &cmd) {
				std::string pr = cmd.printCommand();
				output << pr;
				return output;
			}

		};
	}
}

instantiateHeader(Commands::GenericCommand)