
#include <preprocessDefine.h>

#include <control/commands/meshCMD/inplaneload.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <geometry/GenericGeometryElement.h>

#include <equations/GeometryData.h>
#include <equations/DegreeOfFreedom.h>

#include <math/Userconstants.h>

#include <loads/LoadList.h>

#include <stack>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			InplaneLoad<prec, uint>::InplaneLoad(stringCommandHandler &cmd) {
				this->Normal = cmd.getRhsArray("normal");
				this->Point = cmd.getRhsArray("point");
				this->load = cmd.getRhsArray("load");
				this->snodes = cmd.getRhsArray("nodes");

				this->type = cmd.getRhs("type");
				this->meshId = cmd.getRhs("meshid");
				this->ladd = cmd.getRhs("add");
				this->sprop = cmd.getRhs("propnum");
			}

			template<typename prec, typename uint>
			std::string InplaneLoad<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}


			template<typename prec, typename uint>
			void InplaneLoad<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				uint propnum = static_cast<uint>(pointers.getUserConstants()->process(this->sprop));

				std::vector<prec> nvec;
				nvec.resize(3);
				for (auto i = 0; i < Normal.size(); ++i) {
					nvec[i] = pointers.getUserConstants()->process(this->Normal[i]);
				}

				std::vector<prec> pvec;
				pvec.resize(3);
				for (auto i = 0; i < Point.size(); ++i) {
					pvec[i] = pointers.getUserConstants()->process(this->Point[i]);
				}

				std::vector<prec> loadvec;
				loadvec.resize(load.size());
				for (auto i = 0; i < load.size(); ++i) {
					loadvec[i] = pointers.getUserConstants()->process(this->load[i]);
				}

				std::vector<uint> nodes;
				nodes.resize(snodes.size());
				for (auto i = 0; i < snodes.size(); ++i) {
					nodes[i] = static_cast<uint>(pointers.getUserConstants()->process(this->snodes[i]));
				}

				GeometryTypes gtype;
				//Vertex, Edges, LinearEdgeType, Faces, LinearTriangle

				if (this->type.compare("vertex") == 0) {
					gtype = GeometryTypes::Vertex;
				}
				else if (this->type.compare("edge") == 0) {
					gtype = GeometryTypes::Edges;
				}

				uint MeshId = static_cast<uint>(pointers.getUserConstants()->process(this->meshId));

				bool add = false;
				if (this->ladd.compare("true") == 0) add = true;

				//this->controlProgram->setBoundaryConditionsInPlane(
				//	nvec, pvec, gtype, bcvec, MeshId, Set);
				this->setLoadInPlane(
					pointers, nvec, pvec, gtype, nodes, loadvec, propnum, MeshId, add);

			}


			template<typename prec, typename uint>
			void InplaneLoad<prec, uint>::setLoadInPlane(
				PointerCollection<prec, uint>& pointers, 
				const std::vector<prec>& normal, 
				const std::vector<prec>& point, 
				const GeometryTypes & type, 
				const std::vector<uint>& nodes, 
				const std::vector<prec>& load, 
				const uint & propnum, 
				const uint & meshId, 
				const bool add) {


				std::stack<GenericGeometryElement<prec, uint>*> elems;
				GeometryData<prec, uint> *geometryData = pointers.getGeometryData();
				geometryData->getGeometricElementInPlane(normal, point, type, elems);
				std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
				uint loadnum = static_cast<uint> (load.size());
				while (!elems.empty()) {
					for (auto j = 0; j < nodes.size(); ++j) {
						elems.top()->getNodeEquationIds(pointers, Dofs, meshId, nodes[j]);
						for (auto i = 0; i < loadnum; ++i) {
							uint DofId = Dofs[i]->getId();
							pointers.getLoadList()->setLoad(propnum, DofId, load[i], add);
						}
					}
					elems.pop();
				}

			}
		}
	}
}

instantiate(Commands::Mesh::InplaneLoad)