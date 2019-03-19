
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>

#include <geometry/GeometryTypes.h>

#include <vector>
#include <string>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			class AddFiniteElement : public GenericCommand<prec, uint> {
			public:
				AddFiniteElement(stringCommandHandler &cmd);
				~AddFiniteElement() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec, uint> *NewCommand(stringCommandHandler &cmd) { return new AddFiniteElement<prec, uint>(cmd); };
			private:
				void addLinearLineElement(PointerCollection<prec, uint> &ptrCol, std::vector<uint> edgeNums, uint material);
				std::string elementtype;
				std::string material;
				std::vector<std::string> vertexNumbers;
				std::vector<std::string> edgeNumbers;
				std::vector<std::string> faceNumbers;
			};

		}
	}
}
