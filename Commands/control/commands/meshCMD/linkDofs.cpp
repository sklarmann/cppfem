

#include <preprocessDefine.h>

#include <control/commands/meshCMD/linkDofs.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <equations/EquationHandler.h>
#include <math/Userconstants.h>
#include <equations/GeometryData.h>
#include <geometry/GenericGeometryElement.h>
#include <equations/NodeSet.h>
#include <equations/GenericNodes.h>
#include <equations/DegreeOfFreedom.h>

#include <finiteElements/ElementList.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			linkDofs<prec, uint>::linkDofs(stringCommandHandler &cmd) {
				this->maType = cmd.getRhs("matype");
				this->maTnum = cmd.getRhs("matnum");
				this->maNodeset = cmd.getRhs("manodeset");
				this->maNode = cmd.getRhs("manode");
				this->maDof = cmd.getRhs("madof");
				this->slType = cmd.getRhs("sltype");
				this->slTnum = cmd.getRhs("sltnum");
				this->slNodeset = cmd.getRhs("slnodeset");
				this->slNode = cmd.getRhs("slnode");
				this->slDof = cmd.getRhs("sldof");

				this->fact = cmd.getRhs("fact");
			}

			template<typename prec, typename uint>
			std::string linkDofs<prec, uint>::printCommand() {
				std::string ret;
				std::cout << "Usage:\n" <<
					"linkdofs(matype=type;matnum=number;manodeset=number;manode=number;madof=number\n" <<
					"sltype = type; sltnum = number; slnodeset = number; slnode = number; sldof = number)\n\n" <<
					"matype and satype: Type of geometry element (vertex,line,face,volume) of master (ma) and slave(sl)\n" <<
					"matnum and sltnum: Number of the geometric element for master(ma) and slave(sa)\n" <<
					"manodeset and slnode: The specific nodeset\n" <<
					"manode and slnode: The specific node\n" <<
					"madof and sldof: The specific degree of freedom to link\n" << std::endl;
				return ret;
			}

			template<typename prec, typename uint>
			void linkDofs<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				Userconstants<prec> *ucons = pointers.getUserConstants();
				GenericGeometryElement<prec, uint> *geoMaster, *geoSlave;
				uint geoMaNum = static_cast<uint>(ucons->process(this->maTnum));
				uint geoSlNum = static_cast<uint>(ucons->process(this->slTnum));

				if (this->maType == "vertex") {
					geoMaster = pointers.getGeometryData()->getVertex(geoMaNum);
				}

				if (this->slType == "vertex") {
					geoSlave = pointers.getGeometryData()->getVertex(geoSlNum);
				}

				uint maSetNum = static_cast<uint>(ucons->process(this->maNodeset));
				uint slSetNum = static_cast<uint>(ucons->process(this->slNodeset));
				uint maNN, slNN;
				maNN = static_cast<uint>(ucons->process(this->maNode));
				slNN = static_cast<uint>(ucons->process(this->slNode));

				std::vector<GenericNodes<prec, uint>*> maNodes, slNodes;

				NodeSet<prec, uint> *maSet = geoMaster->getSet(pointers, maSetNum);
				NodeSet<prec, uint> *slSet = geoSlave->getSet(pointers, slSetNum);

				pointers.getEquationHandler()->getNodes(maNodes, *maSet);
				pointers.getEquationHandler()->getNodes(slNodes, *slSet);

				GenericNodes<prec, uint> *maN, *slN;
				maN = maNodes[maNN];
				slN = slNodes[slNN];
				std::vector<DegreeOfFreedom<prec, uint>*> maDofs, slDofs;

				maN->getDegreesOfFreedom(pointers, maDofs);
				slN->getDegreesOfFreedom(pointers, slDofs);

				uint slDofN = static_cast<uint>(ucons->process(this->slDof));
				uint maDofN = static_cast<uint>(ucons->process(this->maDof));
				prec linkFact = ucons->process(this->fact);
				slDofs[slDofN]->setStatus(dofStatus::linked);
				uint masterId = maDofs[maDofN]->getId();
				slDofs[slDofN]->linkTo(masterId, linkFact);

				
			}
		}
	}
}

instantiate(Commands::Mesh::linkDofs)