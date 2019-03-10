#include <preprocessDefine.h>

#include <control/commands/macroCMD/PrintSolution.h>
#include <control/stringCommandHandler.h>
#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>
#include <equations/GeometryData.h>
#include <equations/NodeSet.h>
#include <equations/EquationHandler.h>
#include <equations/GenericNodes.h>
#include <solver/GenericSolutionState.h>
#include <equations/DegreeOfFreedom.h>
#include <control/OutputHandler.h>
#include <control/HandlingStructs.h>
#include <pointercollection/pointercollection.h>
#include <math/Userconstants.h>
#include <geometry/GenericGeometryElement.h>
#include <iomanip>
#include <sstream>

namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			PrintSolution<prec, uint>::PrintSolution(stringCommandHandler &cmd) {
				this->type = cmd.getRhs("type");
				this->number = cmd.getRhs("number");
				this->meshId = cmd.getRhs("meshid");
			}

			template<typename prec, typename uint>
			std::string PrintSolution<prec, uint>::printCommand() {
				std::string ret;
				return ret;
			}

			template<typename prec, typename uint>
			void PrintSolution<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				GeometryData<prec, uint> *geoData = pointers.getGeometryData();
				InfoData *info = pointers.getInfoData();
				Userconstants<prec> *userCons = pointers.getUserConstants();
				userCons = pointers.getUserConstants();
				uint number = static_cast<uint>(pointers.getUserConstants()->process(this->number));
				GenericGeometryElement<prec, uint> *geoTemp=0;
				info->Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;
				if (this->type == "vertex") {
					geoTemp =geoData->getVertex(number);
					if (geoTemp != 0) {
						info->Log(LogLevel::NoLog, LogLevel::NoLog) <<
							"Solution of vertex: " << number << std::endl;
					}
					else {
						info->Log(LogLevel::NoLog, LogLevel::NoLog) <<
							"Vertex: " << number << " does not exist!" << std::endl;
					}
					
				}
				
				if (geoTemp != 0) {
					//uint meshId = userCons->process(this->meshId);
					std::vector<NodeSet<prec, uint>*> NodeSets;
					geoTemp->getSets(pointers, NodeSets);
					if (NodeSets.empty()) {
						info->Log(LogLevel::NoLog, LogLevel::NoLog) <<
							"No degrees of freedom are assigned!" << std::endl;
					}
					NodeSet<prec, uint> *tempSet;
					GenericSolutionState<prec, uint> *solState = pointers.getSolutionState();
					for (auto it = NodeSets.begin(); it != NodeSets.end(); ++it) {
						tempSet = *it;
						std::vector<GenericNodes<prec, uint>*> Nodes;
						pointers.getEquationHandler()->getNodes(Nodes, *tempSet);
						GenericNodes<prec, uint>* tempNode;

						info->Log(LogLevel::NoLog, LogLevel::NoLog) << "Mesh id: " <<
							tempSet->getMeshId() << std::endl;
						for (auto i = 0; i < 3; ++i) {
							std::stringstream toOut;
							toOut << "Dof " << i;
							std::string toPrint;
							toOut >> toPrint;
							info->Log(LogLevel::NoLog, LogLevel::NoLog) << std::scientific
								<< std::setw(20) << toOut.str();
						}
							
							
							
						info->Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;

						for (auto jt = Nodes.begin(); jt != Nodes.end(); ++jt) {
							tempNode = *jt;
							std::vector<DegreeOfFreedom<prec, uint>*>Dofs;
							tempNode->getDegreesOfFreedom(pointers, Dofs);
							DegreeOfFreedom<prec, uint>* tempDof;
							for (auto kt = Dofs.begin(); kt != Dofs.end(); ++kt) {
								tempDof = *kt;
								info->Log(LogLevel::NoLog,LogLevel::NoLog) << std::setw(20)
									<< solState->getSolution(tempDof->getId());
							}
						}
						info->Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;
					}
				
				}
				info->Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;
			}
		}
	}
}

instantiate(Commands::Macro::PrintSolution)