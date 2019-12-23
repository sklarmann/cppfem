
#include <preprocessDefine.h>

#include <control/commands/meshCMD/singleBC.h>

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
			SingleBC<prec, uint>::SingleBC(stringCommandHandler &cmd) {
				//this->Normal = cmd.getRhsArray("normal");
				//this->Point = cmd.getRhsArray("point");
				this->bc = cmd.getRhsArray("bc");
				this->snodes = cmd.getRhsArray("nodes");

				this->type = cmd.getRhs("type");
				this->number = cmd.getRhs("number");
				this->meshId = cmd.getRhs("meshid");
				this->ladd = cmd.getRhs("set");
			}

			template<typename prec, typename uint>
			std::string SingleBC<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}


			template<typename prec, typename uint>
			void SingleBC<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {

				
				std::vector<prec> bcvec;
				bcvec.resize(this->bc.size());
				for (auto i = 0; i < this->bc.size(); ++i) {
					bcvec[i] = pointers.getUserConstants()->process(this->bc[i]);
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

				uint number = static_cast<uint>(pointers.getUserConstants()->process(this->number));

				uint MeshId = static_cast<uint>(pointers.getUserConstants()->process(this->meshId));

				bool add = false;
				if (this->ladd.compare("true") == 0) add = true;

				//this->controlProgram->setBoundaryConditionsInPlane(
				//	nvec, pvec, gtype, bcvec, MeshId, Set);
				this->setBC(
					pointers, number, gtype, nodes, bcvec, MeshId, add);

			}


			template<typename prec, typename uint>
			void SingleBC<prec, uint>::setBC(
				PointerCollection<prec, uint>& pointers, 
				const uint& number,
				const GeometryTypes & type, 
				const std::vector<uint>& nodes, 
				const std::vector<prec>& bc, 
				const uint & meshId, 
				const bool set) {


				GenericGeometryElement<prec, uint>* elems;
				GeometryData<prec, uint> *geometryData = pointers.getGeometryData();
				elems = geometryData->getGeometryElement(type, number);
				std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
                DegreeOfFreedom<prec,uint> *tempDof;
                
                
                for(auto j=0;j<nodes.size();++j){
                    elems->getNodeEquationIds(pointers, Dofs, meshId, nodes[j]);
                    for(auto i=0;i<bc.size();++i){
                        tempDof=Dofs[i];
                        if(tempDof->getStatus()==dofStatus::active) {
                            if(bc[i]>0) tempDof->setStatus(dofStatus::inactive);
                        } else {
                            if(set){
                                if(bc[i]>0) tempDof->setStatus(dofStatus::inactive);
                            }
                        }
                    }
                }
                
                
                
				

			}
		}
	}
}

instantiate(Commands::Mesh::SingleBC)
