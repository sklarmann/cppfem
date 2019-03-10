
#include <preprocessDefine.h>

#include <control/commands/InputParser.h>

#include <pointercollection/pointercollection.h>

#include <control/stringCommandHandler.h>
#include <control/commands/macroCMD/macroCommandInclude.h>
#include <control/commands/meshCMD/meshCommandInclude.h>
#include <control/commands/mathCMD/mathCommandInclude.h>
#include <control/commands/plotCMD/plotCommandInclude.h>
#include <control/commands/GenericCommand.h>
#include <control/commands/quitCommands.h>
#include <control/FEMProgram.h>


#include <queue>
#include <string>
#include <map>

namespace FEMProject {
	namespace Commands {

		template<typename prec, typename uint>
		InputParser<prec, uint>::InputParser() {
//------------------MACRO---------------------------------------------------
			////-----#Exit----------------------------------------------------
			this->macroCommands["quit"] = &macroQuit<prec, uint>::New;
			this->macroCommands["end"] = &macroQuit<prec, uint>::New;
			this->macroCommands["exit"] = &macroQuit<prec, uint>::New;
			////-----#Transfer-------------------------------------------------
			this->macroCommands["mesh"] = &meshInteract<prec, uint>::New;
			this->macroCommands["plot"] = &plotInteract<prec, uint>::New;
			this->macroCommands["math"] = &mathInteract<prec, uint>::New;
			
			////-----#Main Control---------------------------------------------
			this->macroCommands["open"] = &Macro::OpenFiles<prec, uint>::New;
			this->macroCommands["output"] = &Macro::Output<prec, uint>::New;
			this->macroCommands["processfiles"] = &Macro::Processfiles<prec, uint>::New;
			this->macroCommands["rinp"] = &Macro::ReInput<prec, uint>::New;
			this->macroCommands["threads"] = &Macro::Threads<prec, uint>::New;
			this->macroCommands["printinfo"] = &Macro::printInfo<prec, uint>::New;
			this->macroCommands["history"] = &Macro::PrintHistory<prec, uint>::New;
			this->macroCommands["printsolution"] = &Macro::PrintSolution<prec, uint>::New;
			this->macroCommands["do"] = &Macro::Do<prec, uint>::New;
			//
			//
			this->macroCommands["solver"] = &Macro::Solver<prec, uint>::New;
			this->macroCommands["solution"] = &Macro::Solution<prec, uint>::New;
			this->macroCommands["sparsesetup"] = &Macro::SetUpSparseMatrix<prec, uint>::New;
			//
			this->macroCommands["tangent"] = &Macro::Tangent<prec, uint>::New;
			this->macroCommands["eigenval"] = &Macro::eigenValues<prec, uint>::New;
			//
			this->macroCommands["propnames"] = &Macro::PropNames<prec, uint>::New;
			this->macroCommands["propfunction"] = &Macro::PropFunction<prec, uint>::New;
			this->macroCommands["printpropfunction"] = &Macro::PrintPropFunctions<prec, uint>::New;
			this->macroCommands["dt"] = &Macro::SetDt<prec, uint>::New;
			this->macroCommands["timeincr"] = &Macro::TimeIncr<prec,uint>::New;
			//
//----------//--------MESH----------------------------------------------------
			////-----#Exit----------------------------------------------------
			this->meshCommands["quit"] = &meshQuit<prec, uint>::New;
			this->meshCommands["exit"] = &meshQuit<prec, uint>::New;
			this->meshCommands["end"] = &meshQuit<prec, uint>::New;
			//
			this->meshCommands["addvertex"] = &Mesh::AddVertex<prec, uint>::New;
			this->meshCommands["block"] = &Mesh::Block<prec, uint>::New;
			this->meshCommands["setmaterials"] = &Mesh::SetMaterial<prec, uint>::New;
			this->meshCommands["setdofs"] = &Mesh::SetDegreesOfFreedom<prec, uint>::New;
			//
			this->meshCommands["inplanebc"] = &Mesh::InplaneBC<prec, uint>::New;
			this->meshCommands["inplaneload"] = &Mesh::InplaneLoad<prec, uint>::New;
			//
//----------//--------PLOT----------------------------------------------------
			////-----#Exit----------------------------------------------------
			this->plotCommands["quit"] = &plotQuit<prec, uint>::New;
			this->plotCommands["exit"] = &plotQuit<prec, uint>::New;
			this->plotCommands["end"] = &plotQuit<prec, uint>::New;
			//
			this->plotCommands["interact"] = &Plot::Interact<prec, uint>::New;
			//
			this->plotCommands["mesh"] = &Plot::Mesh<prec, uint>::New;
			this->plotCommands["solution"] = &Plot::Solution<prec, uint>::New;
//----------//--------MATH----------------------------------------------------
			////-----#Exit----------------------------------------------------
			this->mathCommands["quit"] = &mathQuit<prec, uint>::New;
			this->mathCommands["end"] = &mathQuit<prec, uint>::New;
			this->mathCommands["exit"] = &mathQuit<prec, uint>::New;
			//
			this->mathCommands["list"] = &Math::List<prec, uint>::New;
		}

		/**
		* @brief parseMacro parses macro command input and returns the corresponding command.
		*/

		template<typename prec, typename uint>
		void InputParser<prec, uint>::parseMacro(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue) {
			while (!cmd.empty()) {
				stringCommandHandler pass;
				std::string procCmd;
				cmd.processCommand(procCmd, pass);
				auto it = this->macroCommands.find(procCmd);


				if (it != this->macroCommands.end()) {
					cmdQueue.push(it->second(pass));
				}
				if (procCmd == "help") {
					if (pass.empty()) {
						std::cout << "List of macro commands:" << std::endl;
						for (auto i = this->macroCommands.begin(); i != this->macroCommands.end(); ++i) {
							std::cout << i->first << std::endl;
						}
					}
					else {
						std::string name;
						stringCommandHandler tempcmd;
						pass.processCommand(name, tempcmd);
						auto it = this->macroCommands.find(name);
						if (it != this->macroCommands.end()) {
							GenericCommand<prec, uint> *temp = it->second(tempcmd);
							temp->help();
							delete temp;
						}
					}
				}
			}
		}

		/**
		* @brief parseMesh parses mesh command input and returns the corresponding command.
		*/

		template<typename prec, typename uint>
		void InputParser<prec, uint>::parseMesh(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue) {
			while (!cmd.empty()) {
				stringCommandHandler pass;
				std::string procCmd;
				cmd.processCommand(procCmd, pass);
				auto it = this->meshCommands.find(procCmd);
				//GenericCommand<prec, uint> *ptr = &Mesh::Block<prec, uint>;
				
				if (it != this->meshCommands.end()) {
					cmdQueue.push(it->second(pass));
				}

				if (procCmd == "help") {
					if (pass.empty()) {
						std::cout << "List of mesh commands:" << std::endl;
						for (auto i = this->meshCommands.begin(); i != this->meshCommands.end(); ++i) {
							std::cout << i->first << std::endl;
						}
					}
				}
			}
		}

		/**
		* @brief parsePlot parses plot command input and returns the corresponding command.
		*/

		template<typename prec, typename uint>
		void InputParser<prec, uint>::parsePlot(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue) {
			while (!cmd.empty()) {
				stringCommandHandler pass;
				std::string procCmd;
				cmd.processCommand(procCmd, pass);
				auto it = this->plotCommands.find(procCmd);
				if (it != this->plotCommands.end()) {
					cmdQueue.push(it->second(pass));
				}

				if (procCmd == "help") {
					if (pass.empty()) {
						std::cout << "List of plot commands:" << std::endl;
						for (auto i = this->plotCommands.begin(); i != this->plotCommands.end(); ++i) {
							std::cout << i->first << std::endl;
						}
					}
				}
			}
		}

		/**
		* @brief parsePlot parses plot command input and returns the corresponding command.
		*/

		template<typename prec, typename uint>
		void InputParser<prec, uint>::parseMath(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue) {
			while (!cmd.empty()) {
				stringCommandHandler pass, temp;
				temp = cmd;
				std::string procCmd;
				cmd.processCommand(procCmd, pass);
				auto it = this->mathCommands.find(procCmd);
				if (it != this->mathCommands.end()) {
					cmdQueue.push(it->second(pass));
				}
				else if (procCmd == "help") {
					if (pass.empty()) {
						std::cout << "List of math commands:" << std::endl;
						for (auto i = this->mathCommands.begin(); i != this->mathCommands.end(); ++i) {
							std::cout << i->first << std::endl;
						}
					}
				}
				else {
					cmd = "";
					cmdQueue.push(new Math::Process<prec, uint>(temp));
				}
			}
		}
	}
}

instantiate(Commands::InputParser)