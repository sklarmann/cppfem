
#include <preprocessDefine.h>

#include <control/commands/meshCMD/inplanebc.h>
#include <control/stringCommandHandler.h>
#include <geometry/GeometryTypes.h>
#include <stack>
#include <geometry/GenericGeometryElement.h>
#include <equations/GeometryData.h>
#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>

#include <vector>


namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			InplaneBC<prec, uint>::InplaneBC(stringCommandHandler &cmd) {
				this->Normal = cmd.getRhsArray("normal");
				this->Point = cmd.getRhsArray("point");
				this->bc = cmd.getRhsArray("bc");
				this->type = cmd.getRhs("type");
				this->meshId = cmd.getRhs("meshid");
				this->set = cmd.getRhs("set");
			}

			template<typename prec, typename uint>
			std::string InplaneBC<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void InplaneBC<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				
				std::vector<prec> nvec;
				nvec.resize(3);
				for (auto i = 0; i < this->Normal.size(); ++i) {
					nvec[i] = pointers.getUserConstants()->process(this->Normal[i]);
				}

				std::vector<prec> pvec;
				pvec.resize(3);
				for (auto i = 0; i < this->Point.size(); ++i) {
					pvec[i] = pointers.getUserConstants()->process(this->Point[i]);
				}

				std::vector<uint> bcvec;
				bcvec.resize(this->bc.size());
				for (auto i = 0; i < this->bc.size(); ++i) {
					bcvec[i] = static_cast<uint>(pointers.getUserConstants()->process(this->bc[i]));
				}

				GeometryTypes gtype;
				//Vertex, Edges, LinearEdgeType, Faces, LinearTriangle

				if (this->type.compare("vertex") == 0) {
					gtype = GeometryTypes::Vertex;
				}
				else if (this->type.compare("edge") == 0) {
					gtype = GeometryTypes::Edges;
				}
				else if (this->type.compare("linearedge") == 0) {
					gtype = GeometryTypes::LinearEdge;
				}
				else if (this->type.compare("lineartriangle") == 0) {
					gtype = GeometryTypes::LinearTriangle;
				}
				else if (this->type.compare("linearquadrilateral") == 0) {
					gtype = GeometryTypes::LinearQuadrilateral;
				}

				uint MeshId = static_cast<uint>(pointers.getUserConstants()->process(meshId));

				bool Set = false;
				if (this->set.compare("true") == 0) Set = true;

				this->setBoundaryConditionsInPlane(
					pointers, nvec, pvec, gtype, bcvec, MeshId, Set);


			}


			template<typename prec, typename uint>
			void InplaneBC<prec, uint>::setBoundaryConditionsInPlane(
				PointerCollection<prec, uint> &pointers
				, const std::vector<prec> &normal
				, const std::vector<prec> &point
				, const GeometryTypes &type
				, const std::vector<uint> &bc
				, const uint &meshId
				, const bool set)
			{
				std::stack<GenericGeometryElement<prec, uint>*> elems;
				GeometryData<prec, uint> *geometryData = pointers.getGeometryData();
				geometryData->getGeometricElementInPlane(normal, point, type, elems);

				uint bcnum = static_cast<uint> (bc.size());
				while (!elems.empty()) {
					for (uint i = 0; i < bcnum; ++i) {
						if (bc[i] > 0) {

							elems.top()->setAllNodeBoundaryConditionMeshId(pointers, meshId, i);
						}
					}
					elems.pop();
				}
			}
		}
	}
}

instantiate(Commands::Mesh::InplaneBC)
