
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
			class SingleBC : public GenericCommand<prec, uint> {
			public:
				SingleBC(stringCommandHandler &cmd);
				~SingleBC() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new SingleBC(cmd); };
			private:
				void setBC(
					PointerCollection<prec,uint> &pointers
					, const uint &number
					, const GeometryTypes& type
					, const std::vector<uint> &nodes
					, const std::vector<prec> &bc
					, const uint &meshId
					, const bool add = false);

				std::vector<std::string> bc;
				std::vector<std::string> snodes;

				std::string type;
				std::string number;
				std::string meshId;
				std::string ladd;

			};
		}
	}
}
