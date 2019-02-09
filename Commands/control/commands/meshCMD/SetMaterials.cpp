
#include <preprocessDefine.h>

#include <control/commands/meshCMD/SetMaterials.h>

#include <pointercollection/pointercollection.h>

#include <elementFormulations/GenericElementFormulation.h>

#include <materials/Material.h>
#include <materials/MaterialList.h>
#include <materials/GenericMaterialFormulation.h>

#include <math/Userconstants.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {

			template<typename prec, typename uint>
			SetMaterial<prec, uint>::SetMaterial(stringCommandHandler &cmd) {
				this->number = cmd.getRhs("number");
				this->elform = cmd.getRhs("elementformulation");
				this->matform = cmd.getRhs("materialformulation");
				while (!cmd.empty())
				{
					std::string scmd;
					stringCommandHandler passCommand;
					cmd.processCommand(scmd, passCommand);
					if (scmd == "element") {
						this->elpara=passCommand;
					}
					else if (scmd == "material") {
						this->matpara = passCommand;
					}
				}
			}

			template<typename prec, typename uint>
			std::string SetMaterial<prec, uint>::printCommand() {
				std::string ret;

			//	setmaterials(
			//		number = 1;
			//	elementformulation = 201;
			//	materialformulation = 1;
			//	element(meshiddisp = 1; disporder = 1;)
			//		material(emodul = 100; nu = 0.3;)
			//		)
				
				

				ret = "setmaterials(\n\tnumber=" + this->number +
					";\n\telementformulation=" + this->elform +
					";\n\tmaterialformulation=" + this->matform +
					";\n\telement" + this->elpara.remainingCommands() + ")";

				

				ret += "\n\tmaterial(" + this->matpara.remainingCommands() + ")\n)";

				return ret;
			}

			template<typename prec, typename uint>
			void SetMaterial<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				uint num, matnum, elnum;
				
				num = static_cast<uint>(pointers.getUserConstants()->process(this->number));
				matnum = static_cast<uint>(pointers.getUserConstants()->process(this->matform));
				elnum = static_cast<uint>(pointers.getUserConstants()->process(this->elform));
				Material<prec, uint> *mat;
				mat = pointers.getMaterialList()->getMaterial(num);
				mat->setElementForumaltion(elnum);
				mat->setMaterialFormulation(matnum);
				stringCommandHandler temp = this->elpara;
				mat->getElementFormulation()->readData(temp, pointers.getUserConstants());
				temp = this->matpara;
				mat->getMaterialFormulation()->readData(temp, pointers.getUserConstants());
			}
		}
	}
}

instantiate(Commands::Mesh::SetMaterial)