
#pragma once

#include <forwarddeclaration.h>

#include <control/commands/GenericCommand.h>
#include <vector>
#include <geometry/GeometryTypes.h>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			class InplaneBC : public GenericCommand<prec, uint> {
			public:
				InplaneBC(stringCommandHandler &cmd);
				~InplaneBC() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new InplaneBC(cmd); };
			private:
				void setBoundaryConditionsInPlane(
					PointerCollection<prec, uint> &pointers
					, const std::vector<prec> &normal
					, const std::vector<prec> &point
					, const GeometryTypes &type
					, const std::vector<uint> &bc
					, const uint &meshId
					, const bool set = false);

				std::vector<std::string> Normal;
				std::vector<std::string> Point;
				std::vector<std::string> bc;
				std::string type;
				std::string meshId;
				std::string set;

			};
		}
	}
}
