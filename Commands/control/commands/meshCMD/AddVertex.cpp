
#include <preprocessDefine.h>

#include <control/commands/meshCMD/AddVertex.h>


#include <iostream>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			AddVertex<prec, uint>::AddVertex(stringCommandHandler &cmd) {
				this->coordinates = cmd.getRhsArray("coordinates");
			}
			template<typename prec, typename uint>
			void AddVertex<prec, uint>::run(PointerCollection<prec, uint>& ptrCol, FEMProgram<prec, uint>* program)
			{
				uint numcoords = static_cast<uint>(this->coordinates.size());
				if (numcoords % 3 == 0) {

				}
				else {
					std::cout << "Error in AddVertex" << std::endl;
				}
			}
			template<typename prec, typename uint>
			std::string AddVertex<prec, uint>::printCommand()
			{
				return std::string();
			}
		}
	}
}

instantiate(Commands::Mesh::AddVertex)