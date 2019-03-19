#include <preprocessDefine.h>

#include <control/commands/meshCMD/AddGeometryElement.h>
#include <control/stringCommandHandler.h>

#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>

#include <geometry/GeometryTypes.h>
#include <equations/GeometryData.h>
#include <geometry/GenericGeometryElement.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			AddGeometryElement<prec, uint>::AddGeometryElement(stringCommandHandler & cmd)
			{
				this->type = cmd.getRhs("type");
				this->vertexNumbers = cmd.getRhsArray("verts");
				this->edgeNumbers = cmd.getRhsArray("edges");
				this->edgeNumbers = cmd.getRhsArray("faces");
			}
			template<typename prec, typename uint>
			void AddGeometryElement<prec, uint>::run(PointerCollection<prec, uint>& ptrCol, FEMProgram<prec, uint>* program)
			{
				GeometryTypes type;
				if (this->type == "linearedge") {
					type = GeometryTypes::LinearEdge;
				}



				switch (type) {
				case GeometryTypes::LinearEdge:
				{
					std::vector<uint> vertNums;
					Userconstants<prec> *ucons = ptrCol.getUserConstants();
					if (this->vertexNumbers.size() % 2 == 0) {
						for (auto i = this->vertexNumbers.begin(); i != this->vertexNumbers.end(); ++i) {
							vertNums.emplace_back(ucons->process(*i));
						}
						this->addLinearEdge(ptrCol, vertNums);
					}
					
				}
				break;

				}


			}
			template<typename prec, typename uint>
			std::string AddGeometryElement<prec, uint>::printCommand()
			{
				return std::string();
			}
			template<typename prec, typename uint>
			void AddGeometryElement<prec, uint>::addLinearEdge(PointerCollection<prec, uint>& ptrCol, std::vector<uint> vertNums)
			{
				GeometryData<prec, uint> *geoData = ptrCol.getGeometryData();
				GenericGeometryElement<prec, uint> *tempElem;
				uint numedges = vertNums.size() / 2;
				uint edgeNum;
				auto vertIt = vertNums.begin();
				
				for (auto i = 0; i < numedges; ++i) {
					std::vector<uint> toAdd;
					toAdd.emplace_back(*vertIt); ++vertIt;
					toAdd.emplace_back(*vertIt); ++vertIt;
					edgeNum = geoData->requestNewGeometryObject(GeometryTypes::LinearEdge);
					tempElem = geoData->getEdge(edgeNum);
					tempElem->setVerts(toAdd);
				}

			}
		}
	}
}

instantiate(Commands::Mesh::AddGeometryElement)