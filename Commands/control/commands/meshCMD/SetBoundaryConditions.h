
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <geometry/GeometryTypes.h>

#include <vector>
#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {


			/**
			* @brief Block mesh generator.
			* @param blockType		Specifies the block type, see enum blockTypes
			* @param elementType   Specifies the element type. see Elementlist.h
			* @param coordinates   Coordinates used for generation, depend on the specified block type.
			* @param firstIncr     Section increment in the first direction.
			* @param secondIncr    Section increment in the second direction.
			* @param thirdIncr     Section increment in the third direction.
			*
			* Used to mesh simple geometries like lines, quads, cubes. Generates the nodes, edges,
			* faces and the specified elements.
			*/

			template<typename prec, typename uint>
			class SetBoundaryConditions : public GenericCommand<prec, uint> {
			public:
				SetBoundaryConditions(stringCommandHandler &cmd);
				~SetBoundaryConditions() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec, uint> *NewCommand(stringCommandHandler &cmd) { return new SetBoundaryConditions<prec, uint>(cmd); };
			private:
				std::string geotype;
				std::string meshid;
				std::string nodeNum;
				std::vector<std::string> elemList;
				std::vector<std::string> bcList;
			};

		}
	}
}
