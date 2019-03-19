#include <preprocessDefine.h>

#include <control/commands/meshCMD/AddFiniteElement.h>
#include <control/stringCommandHandler.h>

#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>

#include <geometry/GeometryTypes.h>
#include <equations/GeometryData.h>
#include <geometry/GenericGeometryElement.h>

#include <finiteElements/GenericFiniteElement.h>
#include <finiteElements/ElementTypes.h>
#include <finiteElements/ElementList.h>


#include <materials/Material.h>
#include <materials/MaterialList.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			AddFiniteElement<prec, uint>::AddFiniteElement(stringCommandHandler & cmd)
			{
				this->elementtype = cmd.getRhs("type");
				this->material = cmd.getRhs("material");
				this->vertexNumbers = cmd.getRhsArray("verts");
				this->edgeNumbers = cmd.getRhsArray("edges");
				this->faceNumbers = cmd.getRhsArray("faces");
			}
			template<typename prec, typename uint>
			void AddFiniteElement<prec, uint>::run(PointerCollection<prec, uint>& ptrCol, FEMProgram<prec, uint>* program)
			{
				Elementtypes type;
				if (this->elementtype == "linearline") {
					type = Elementtypes::LinearLine;
				}


				std::vector<uint> edgeNums;
				Userconstants<prec> *ucons = ptrCol.getUserConstants();
				uint matnum = static_cast<uint>(ucons->process(this->material));

				switch (type) {
				case Elementtypes::LinearLine:
				{
					for (auto i = this->edgeNumbers.begin(); i != this->edgeNumbers.end(); ++i) {
						edgeNums.push_back(static_cast<uint>(ucons->process(*i)));
					}
					
					this->addLinearLineElement(ptrCol, edgeNums, matnum);

				}
				break;

				}


			}
			template<typename prec, typename uint>
			std::string AddFiniteElement<prec, uint>::printCommand()
			{
				return std::string();
			}
			template<typename prec, typename uint>
			void AddFiniteElement<prec, uint>::addLinearLineElement(PointerCollection<prec, uint>& ptrCol, std::vector<uint> edgeNumbers, uint material)
			{
				ElementList<prec, uint> *elemlist;
				GenericFiniteElement<prec, uint> *tempelem;
				GeometryData<prec, uint> *geoData;
				GenericGeometryElement<prec, uint> *geoEdge;
				MaterialList<prec, uint> *matList;
				Material<prec, uint> *mat;
				matList = ptrCol.getMaterialList();
				mat = matList->getMaterial(material);

				elemlist = ptrCol.getElementList();
				geoData = ptrCol.getGeometryData();

				for (auto i = edgeNumbers.begin(); i != edgeNumbers.end(); ++i) {
					std::vector<uint> edges;
					edges.push_back(*i);
					geoEdge = geoData->getEdge(*i);
					tempelem = elemlist->requestNewElement(Elementtypes::LinearLine);
					tempelem->setEdges(edges);
					edges.clear();
					geoEdge->getVerts(edges);
					tempelem->setVerts(edges);
					tempelem->setMatrial(mat);
				}

			}
		}
	}
}

instantiate(Commands::Mesh::AddFiniteElement)