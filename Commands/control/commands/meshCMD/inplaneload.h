
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
			class InplaneLoad : public GenericCommand<prec, uint> {
			public:
				InplaneLoad(stringCommandHandler &cmd);
				~InplaneLoad() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new InplaneLoad(cmd); };
			private:
				void setLoadInPlane(
					PointerCollection<prec,uint> &pointers
					, const std::vector<prec> &normal
					, const std::vector<prec> &point
					, const GeometryTypes &type
					, const std::vector<uint> &nodes
					, const std::vector<prec> &load
					, const uint &propnum
					, const uint &meshId
					, const bool add = false);

				std::vector<std::string> Normal;
				std::vector<std::string> Point;
				std::vector<std::string> load;
				std::vector<std::string> snodes;

				std::string type;
				std::string meshId;
				std::string ladd;
				std::string sprop;

			};
		}
	}
}
