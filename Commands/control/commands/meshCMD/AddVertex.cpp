
#include <preprocessDefine.h>

#include <control/commands/meshCMD/AddVertex.h>



#pragma once

#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			AddVertex<prec, uint>::AddVertex(stringCommandHandler &cmd) {};
		}
	}
}

instantiate(Commands::Mesh::AddVertex)