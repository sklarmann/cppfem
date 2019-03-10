
#include <preprocessDefine.h>

#include <control/commands/meshCMD/AddVertex.h>
#include <pointercollection/pointercollection.h>
#include <equations/GeometryData.h>
#include <geometry/GenericGeometryElement.h>
#include <math/Userconstants.h>

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
					GeometryData<prec, uint> *geoData = ptrCol.getGeometryData();
					uint numcoords = static_cast<uint>(this->coordinates.size());
					uint numVerts = numcoords / 3;


					GenericGeometryElement<prec, uint> *vert;

					Userconstants<prec> *ucons = ptrCol.getUserConstants();

					for (auto i = 0; i < numVerts; ++i) {
						uint vertNum = geoData->requestNewGeometryObject(GeometryTypes::Vertex);
						vert = geoData->getVertex(vertNum);
						prec x, y, z;
						x = ucons->process(this->coordinates[3 * i]);
						y = ucons->process(this->coordinates[3 * i + 1]);
						z = ucons->process(this->coordinates[3 * i + 2]);
						vert->setCoordinates(x, y, z);
					}
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
