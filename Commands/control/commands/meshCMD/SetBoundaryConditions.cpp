#include <preprocessDefine.h>

#include <control/commands/meshCMD/SetBoundaryConditions.h>

#include <control/stringCommandHandler.h>

#include <pointercollection/pointercollection.h>

#include <math/Userconstants.h>

namespace FEMProject {
	namespace Commands {
		namespace Mesh {
			template<typename prec, typename uint>
			SetBoundaryConditions<prec, uint>::SetBoundaryConditions(stringCommandHandler & cmd)
			{
				this->geotype = cmd.getRhs("type");
				this->meshid = cmd.getRhs("meshid");
				this->elemList = cmd.getRhsArray("list");
				this->bcList = cmd.getRhsArray("bc");
			}

			template<typename prec, typename uint>
			void SetBoundaryConditions<prec, uint>::run(PointerCollection<prec, uint>& ptrCol, FEMProgram<prec, uint>* program)
			{
				Userconstants<prec> *ucons = ptrCol.getUserConstants();

				if (this->geotype == "vertex") {
					std::vector<uint> bcs;
					for (auto i = 0; i < 3; ++i) bcs.push_back(static_cast<uint>(ucons->process(this->bcList[i])));
				}

			}

			template<typename prec, typename uint>
			std::string SetBoundaryConditions<prec, uint>::printCommand()
			{
				return std::string();
			}
		}
	}
}

instantiate(Commands::Mesh::SetBoundaryConditions)