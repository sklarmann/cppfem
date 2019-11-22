
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
			class SingleLoad : public GenericCommand<prec, uint> {
			public:
				SingleLoad(stringCommandHandler &cmd);
				~SingleLoad() {};
				void run(PointerCollection<prec, uint> &ptrCol, FEMProgram<prec, uint> *program);
				std::string printCommand();
				static GenericCommand<prec,uint> *NewCommand(stringCommandHandler &cmd) { return new SingleLoad(cmd); };
			private:
				void setLoad(
					PointerCollection<prec,uint> &pointers
					, const uint &number
					, const GeometryTypes& type
					, const std::vector<uint> &nodes
					, const std::vector<prec> &load
					, const uint &propnum
					, const uint &meshId
					, const bool add = false);

				std::vector<std::string> load;
				std::vector<std::string> snodes;

				std::string type;
				std::string number;
				std::string meshId;
				std::string ladd;
				std::string sprop;

			};
		}
	}
}
