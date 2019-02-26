

#include <preprocessDefine.h>

#include <control/commands/GenericCommand.h>

#include <iostream>


namespace FEMProject {


	namespace Commands {
		template<typename prec, typename uint>
		void GenericCommand<prec, uint>::help() {
			{ std::cout << "Help not implemented for the command!" << std::endl; }
		}
	}
}

instantiate(Commands::GenericCommand)