
#include <preprocessDefine.h>

#include <control/commands/macroCMD/ValueToUserVar.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <loads/PropfunctionHandler.h>

#include <math/Userconstants.h>

#include <geometry/GeometryTypes.h>
#include <geometry/GenericGeometryElement.h>
#include <equations/GeometryData.h>
#include <equations/GenericNodes.h>
#include <equations/DegreeOfFreedom.h>

#include <solver/GenericSolutionState.h>

#include <control/HandlingStructs.h>

#include <sstream>
#include <vector>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			ValueToUserVar<prec, uint>::ValueToUserVar(stringCommandHandler &cmd) {
				this->name = cmd.getRhs("varname");
				this->type = cmd.getRhs("type");
				this->nodeset = cmd.getRhs("nodeset");
				this->node = cmd.getRhs("node");
				this->dof = cmd.getRhs("dof");
				this->tnum = cmd.getRhs("tnum");

			}

			template<typename prec, typename uint>
			std::string ValueToUserVar<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void ValueToUserVar<prec, uint>::help()
			{
				std::cout << "This Command is used to bind a solution value to a user constant \n" <<
					"Input:\n" <<
					"varname= Name of user value in math mode\n" <<
					"type=vertex or edge or face or eigen\n" <<
					"tnum= Geometry element number or eigenvalue number\n" <<
					"nodeset= NodeSet number in case of a geometry element for type\n" <<
					"node= Node number in the NodeSet\n" <<
					"dof= Degree of freedom Number of selected node, ranges from 0 to 2\n\n" <<
					"Example:\n" <<
					"getval(varname=var;type=vertex;tnum=1;nodeset=1;node=1;dof=0;)\n or \n" <<
					"getval(varname=var;type=eigen;tnum=1;)" << std::endl;


					
			}

			template<typename prec, typename uint>
			void ValueToUserVar<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				std::stringstream VarName; 
				VarName << this->name;
				prec VarVal;
				InfoData *out = pointers.getInfoData();
				if (this->type == "vertex" || 
					this->type == "edge" ||
					this->type == "face") {
					GenericGeometryElement<prec, uint> *geoElem = NULL;
					uint geoNum = static_cast<uint>(pointers.getUserConstants()->process(this->tnum));
					if (this->type == "vertex") {
						geoElem = pointers.getGeometryData()->getVertex(geoNum);
					}
					else if (this->type == "edge") {
						geoElem = pointers.getGeometryData()->getEdge(geoNum);
					}
					else if (this->type == "face") {
						geoElem = pointers.getGeometryData()->getFace(geoNum);
					}

					if (geoElem != NULL) {
						uint nodSetNumber = static_cast<uint>(pointers.getUserConstants()->process(this->nodeset));
						std::vector<GenericNodes<prec, uint>*> nodes;
						geoElem->getNodesOfSet(pointers, nodes, nodSetNumber);
						if (nodes.size() > 0) {
							uint nodeNumber = static_cast<uint>(pointers.getUserConstants()->process(this->node));
							if (nodeNumber < nodes.size()) {
								GenericNodes<prec, uint> *tempNode;
								tempNode = nodes[nodeNumber];
								std::vector<DegreeOfFreedom<prec, uint> *> Dofs;
								tempNode->getDegreesOfFreedom(pointers, Dofs);
								uint dofNumber = static_cast<uint>(pointers.getUserConstants()->process(this->dof));
								DegreeOfFreedom<prec, uint> *tempDof;
								if (dofNumber < Dofs.size()) {
									tempDof = Dofs[dofNumber];
									uint solId = tempDof->getId();
									VarVal = pointers.getSolutionState()->getSolution(solId);
								}
							}
							else {
								out->Log(LogLevel::NoLog, LogLevel::NoLog) <<
									"Node " << nodeNumber <<
									"does not exist in NodeSet " << nodSetNumber <<
									" of geometry element " << this->type << " "
									<< geoNum << std::endl;
							}
						}
						else {
							out->Log(LogLevel::NoLog, LogLevel::NoLog) <<
								"Nodeset " << nodSetNumber <<
								" of geometry element " << this->type << " "
								<< geoNum << " does not exist!" << std::endl;
						}
					}
					else {
						out->Log(LogLevel::NoLog, LogLevel::NoLog) <<
							"Geometry element of type=" << this->type <<
							" with number: " << geoNum << " does not exist!" << std::endl;
					}
				}
				else if (this->type == "eigen") {
					uint EigenNumber = static_cast<uint>(pointers.getUserConstants()->process(this->tnum));
					VarVal = pointers.getSolutionState()->getEigenValue(EigenNumber);
				}
				//pointers.getPropLoads()->setDt(pointers, this->dt);
				VarName << std::setprecision(out->Log.getNumberPrecision()) << "=" << VarVal;
				pointers.getUserConstants()->process(VarName.str());

			}
		}
	}
}

instantiate(Commands::Macro::ValueToUserVar)