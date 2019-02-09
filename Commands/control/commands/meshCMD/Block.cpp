
#include <preprocessDefine.h>

#include <control/commands/meshCMD/Block.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>


#include <finiteElements/ElementList.h>
#include <finiteElements/GenericFiniteElement.h>

#include <equations/GeometryData.h>

#include <geometry/GenericGeometryElement.h>

#include <materials/Material.h>
#include <materials/MaterialList.h>

#include <math/Userconstants.h>

#include <shapefunctions/Lobatto.h>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			Block<prec, uint>::Block(stringCommandHandler &cmd) {
				this->mat = cmd.getRhs("material");
				this->blocktype = cmd.getRhs("blocktype");
				this->elementtype = cmd.getRhs("elementtype");
				this->firstinc = cmd.getRhs("firstinc");
				this->secondinc = cmd.getRhs("secondinc");
				this->thirdinc = cmd.getRhs("thirdinc");
				this->nodes = cmd.getRhsArray("nodes");
			}

			template<typename prec, typename uint>
			std::string Block<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void Block<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				uint matnum = static_cast<uint>(pointers.getUserConstants()->process(this->mat));
				uint firstIncr = static_cast<uint>(pointers.getUserConstants()->process(this->firstinc));
				uint secondIncr = static_cast<uint>(pointers.getUserConstants()->process(this->secondinc));
				uint thirdIncr = static_cast<uint>(pointers.getUserConstants()->process(this->thirdinc));

				uint n = 0;
				std::vector<prec> temp;
				temp.resize(3);

				std::vector<std::vector<prec>> coordinates;
				for (auto i = 0; i < this->nodes.size(); ++i) {
					++n;
					temp[n - 1] = pointers.getUserConstants()->process(this->nodes[i]);
					if (n == 3) {
						coordinates.push_back(temp);
						n = 0;
					}
				}

				Elementtypes elementType;

				if (this->elementtype.compare("line") == 0) {
					elementType = Elementtypes::Line;
				}
				else if (this->elementtype.compare("lineartriangle") == 0) {
					elementType = Elementtypes::LinearTriangle;
				}

				blockTypes blockType;

				if (blocktype.compare("quadlinear") == 0) {
					blockType = quadlinear;
				}

				this->blockGeneration(pointers, blockType, elementType, coordinates,
					firstIncr, secondIncr, thirdIncr,
					matnum);
			}


			template<typename prec, typename uint>
			void Block<prec, uint>::blockGeneration(PointerCollection<prec, uint> &pointers,
				const blockTypes &blockType,
				const Elementtypes &elementType,
				std::vector<std::vector<prec>> &coordinates,
				const uint &firstIncr, const uint &secondIncr, const uint &thirdIncr,
				const uint &materialNumber)
			{
				ElementList<prec, uint> *elemList;
				elemList = pointers.getElementList();
				GeometryData<prec, uint> *geoData = pointers.getGeometryData();


				switch (blockType) {
				case blockTypes::quadlinear:
					uint firstVertex = geoData->getNumberOfVertices();
					uint firstEdge = geoData->getNumberOfEdges();
					{
						prec coor1;
						prec coor2;
						prec shapev1, shapev2, shapev3, shapev4;
						prec tempshape, tempshapederiv;
						prec dinc1 = static_cast<prec>(2) / firstIncr;
						prec dinc2 = static_cast<prec>(2) / secondIncr;
						std::vector<prec> vertexCoor;
						vertexCoor.resize(3);
						uint vertnumber;
						GenericGeometryElement<prec, uint> *vertoAdd;


						for (uint i = 0; i <= secondIncr; ++i) {
							for (uint j = 0; j <= firstIncr; ++j) {
								coor1 = -static_cast<prec>(1) + j*dinc1;
								coor2 = -static_cast<prec>(1) + i*dinc2;
								LobattoShape<prec, uint>(tempshape, tempshapederiv, coor1, 0);
								shapev1 = tempshape;
								shapev4 = tempshape;
								LobattoShape<prec, uint>(tempshape, tempshapederiv, coor1, 1);
								shapev2 = tempshape;
								shapev3 = tempshape;
								LobattoShape<prec, uint>(tempshape, tempshapederiv, coor2, 0);
								shapev1 *= tempshape;
								shapev2 *= tempshape;
								LobattoShape<prec, uint>(tempshape, tempshapederiv, coor2, 1);
								shapev3 *= tempshape;
								shapev4 *= tempshape;

								for (auto l = 0; l<3; ++l) {
									vertexCoor[l] = coordinates[0][l] * shapev1
										+ coordinates[1][l] * shapev2
										+ coordinates[2][l] * shapev3
										+ coordinates[3][l] * shapev4;
								}
								vertnumber = geoData->requestNewGeometryObject(GeometryTypes::Vertex);
								vertoAdd = geoData->getGeometryElement(GeometryTypes::Vertex, vertnumber);
								vertoAdd->setCoordinates(vertexCoor[0]
									, vertexCoor[1]
									, vertexCoor[2]);
								//				vertoAdd->print();
								//				std::cout << vertnumber << "first: " << (firstIncr+1)*(secondIncr+1)-1 <<  std::endl;
							}
						}

						switch (elementType) {
						case Elementtypes::Line:
							std::cout << "Error" << std::endl;
							break;
						case Elementtypes::LinearTriangle: {
							GenericGeometryElement<prec, uint> *EdgeToAdd;
							uint edgeNumber;
							std::vector<uint> vertsAdd;
							vertsAdd.resize(2);
							//			uint firstEdge = this->geometryData->getNumberOfEdges();
							for (uint i = 0; i<secondIncr + 1; ++i) {
								for (uint j = 0; j<firstIncr; ++j) {
									edgeNumber = geoData->requestNewGeometryObject(GeometryTypes::LinearEdge);
									EdgeToAdd = geoData->getGeometryElement(GeometryTypes::LinearEdge, edgeNumber);

									vertsAdd[0] = firstVertex + (firstIncr + 1)*i + j;
									vertsAdd[1] = vertsAdd[0] + 1;
									EdgeToAdd->setVerts(vertsAdd);
								}
							}
							for (uint i = 0; i<secondIncr; ++i) {
								for (uint j = 0; j<firstIncr + 1; ++j) {
									edgeNumber = geoData->requestNewGeometryObject(GeometryTypes::LinearEdge);
									EdgeToAdd = geoData->getGeometryElement(GeometryTypes::LinearEdge, edgeNumber);

									vertsAdd[0] = firstVertex + (firstIncr + 1)*i + 0 + j;
									vertsAdd[1] = vertsAdd[0] + (firstIncr + 1);
									EdgeToAdd->setVerts(vertsAdd);
								}
							}
							for (uint i = 0; i<secondIncr; ++i) {
								for (uint j = 0; j<firstIncr; ++j) {
									edgeNumber = geoData->requestNewGeometryObject(GeometryTypes::LinearEdge);
									EdgeToAdd = geoData->getGeometryElement(GeometryTypes::LinearEdge, edgeNumber);

									vertsAdd[0] = firstVertex + (firstIncr + 1)*i + 0 + j;
									vertsAdd[1] = vertsAdd[0] + (firstIncr + 2);
									EdgeToAdd->setVerts(vertsAdd);

								}
							}

							uint vert1, vert2, vert3, vert4;
							uint edge1, edge2, edge3, edge4, edge5;
							uint face;

							std::vector<uint> verts, edges;

							GenericFiniteElement<prec, uint> *temp;
							GenericGeometryElement<prec, uint> *faceToAdd;
							for (uint i = 0; i<secondIncr; ++i) {
								for (uint j = 0; j<firstIncr; ++j) {
									vert1 = firstVertex + j + (firstIncr + 1)*i;
									vert2 = vert1 + 1;
									vert3 = vert2 + firstIncr;
									vert4 = vert3 + 1;

									edge1 = firstEdge + firstIncr*i + j;
									edge2 = edge1 + firstIncr;
									edge3 = edge1 + firstIncr*(secondIncr + 1);
									edge4 = edge3 + 1;
									edge5 = edge3 + secondIncr*(firstIncr + 1);

									verts.clear();
									verts.push_back(vert1);
									verts.push_back(vert2);
									verts.push_back(vert4);

									face = geoData->requestNewGeometryObject(GeometryTypes::LinearTriangle);
									faceToAdd = geoData->getGeometryElement(GeometryTypes::LinearTriangle, face);
									faceToAdd->setVerts(verts);
									
									edges.clear();
									edges.push_back(edge1);
									edges.push_back(edge4);
									edges.push_back(edge5);
									faceToAdd->setEdges(edges);

									temp = elemList->requestNewElement(Elementtypes::LinearTriangle);
									temp->setVerts(verts);
									temp->setEdges(edges);
									temp->setFace(face);

									temp->setMatrial(pointers.getMaterialList()->getMaterial(materialNumber));

									verts.clear();
									verts.push_back(vert4);
									verts.push_back(vert3);
									verts.push_back(vert1);
									edges.clear();
									edges.push_back(edge2);
									edges.push_back(edge3);
									edges.push_back(edge5);

									face = geoData->requestNewGeometryObject(GeometryTypes::LinearTriangle);
									faceToAdd = geoData->getGeometryElement(GeometryTypes::LinearTriangle, face);
									faceToAdd->setVerts(verts);
									faceToAdd->setEdges(edges);

									temp = elemList->requestNewElement(Elementtypes::LinearTriangle);
									temp->setVerts(verts);
									temp->setEdges(edges);
									temp->setFace(face);

									temp->setMatrial(pointers.getMaterialList()->getMaterial(materialNumber));

								}
							}
						}
														   break;
						case Elementtypes::QuadrilateralNodal: {

						} break;
						default:
							//TODO throw exception
							std::cout << "Error" << std::endl;
						}
					}
					break;
				}
			}
		}
	}
}

instantiate(Commands::Mesh::Block)