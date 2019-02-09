
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <finiteElements/ElementTypes.h>

#include <vector>
#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			enum blockTypes { quadlinear };


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
			class Block : public GenericCommand<prec, uint> {
			public:
				Block(stringCommandHandler &cmd);
				~Block() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
			private:
				void blockGeneration(PointerCollection<prec, uint> &pointers, 
					const blockTypes &blockType,
					const Elementtypes &elementType,
					std::vector<std::vector<prec>> &coordinates,
					const uint &firstIncr, const uint &secondIncr, const uint &thirdIncr,
					const uint &materialNumber);

				std::string mat;
				std::string blocktype;
				std::string elementtype;
				std::string firstinc;
				std::string secondinc;
				std::string thirdinc;
				std::vector<std::string> nodes;

			};
		}
	}
}