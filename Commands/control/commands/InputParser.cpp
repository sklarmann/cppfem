
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
			//-----#Exit----------------------------------------------------
			this->macroCommands["quit"] = macroCmd::exit;
			this->macroCommands["end"] = macroCmd::exit;
			this->macroCommands["exit"] = macroCmd::exit;
			//-----#Transfer-------------------------------------------------
			this->macroCommands["mesh"] = macroCmd::mesh;
			this->macroCommands["plot"] = macroCmd::plot;
			this->macroCommands["math"] = macroCmd::math;
			//-----#Main Control---------------------------------------------
			this->macroCommands["output"] = macroCmd::output;
			this->macroCommands["open"] = macroCmd::openFiles;
			this->macroCommands["processfiles"] = macroCmd::processfiles;
			this->macroCommands["rinp"] = macroCmd::reinput;
			this->macroCommands["threads"] = macroCmd::threads;
			this->macroCommands["history"] = macroCmd::history;
			this->macroCommands["printinfo"] = macroCmd::prininfo;


			this->macroCommands["solver"] = macroCmd::solver;
			this->macroCommands["solution"] = macroCmd::solution;
			this->macroCommands["sparsesetup"] = macroCmd::setupsparsematrix;

			this->macroCommands["tangent"] = macroCmd::tangent;
			this->macroCommands["eigenval"] = macroCmd::eigenval;

			this->macroCommands["propnames"] = macroCmd::propnames;
			this->macroCommands["propfunction"] = macroCmd::propfunction;
			this->macroCommands["printpropfunction"] = macroCmd::printpropfunction;
			this->macroCommands["dt"] = macroCmd::setdt;
			this->macroCommands["timeincr"] = macroCmd::timeincr;

//------------------MESH----------------------------------------------------
			//-----#Exit----------------------------------------------------
			this->meshCommands["quit"] = meshCmd::exit;
			this->meshCommands["end"]  = meshCmd::exit;
			this->meshCommands["exit"] = meshCmd::exit;

			this->meshCommands["block"] = meshCmd::block;
			this->meshCommands["setmaterials"] = meshCmd::setmaterial;
			this->meshCommands["setdofs"] = meshCmd::setDegreesOfFreedom;

			this->meshCommands["inplanebc"] = meshCmd::inplanebc;
			this->meshCommands["inplaneload"] = meshCmd::inplaneload;

//------------------PLOT----------------------------------------------------
			//-----#Exit----------------------------------------------------
			this->plotCommands["quit"] = plotCmd::exit;
			this->plotCommands["end"]  = plotCmd::exit;
			this->plotCommands["exit"] = plotCmd::exit;

			this->plotCommands["interact"] = plotCmd::interact;

			this->plotCommands["mesh"] = plotCmd::mesh;
			this->plotCommands["solution"] = plotCmd::solution;
//------------------MATH----------------------------------------------------
			//-----#Exit----------------------------------------------------
			this->mathCommands["quit"] = mathCmd::exit;
			this->mathCommands["end"] = mathCmd::exit;
			this->mathCommands["exit"] = mathCmd::exit;

			this->mathCommands["list"] = mathCmd::list;
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
				std::map<std::string, macroCmd>::iterator it = this->macroCommands.find(procCmd);

				if (it != this->macroCommands.end()) {
					switch (it->second)
					{
					case macroCmd::exit:
						cmdQueue.push(new macroQuit<prec, uint>(pass));
						break;
					case macroCmd::mesh:
						if (pass.empty()) {
							cmdQueue.push(new meshInteract<prec, uint>(pass));
						}
						else {
							this->parseMesh(pass, cmdQueue);
						}
						break;
					case macroCmd::plot:
						if (pass.empty()) {
							cmdQueue.push(new plotInteract<prec, uint>(pass));
						}
						else {
							this->parsePlot(pass, cmdQueue);
						}
						break;
					case macroCmd::math:
						if (pass.empty()) {
							cmdQueue.push(new mathInteract<prec, uint>(pass));
						}
						else {
							this->parseMath(pass, cmdQueue);
						}
						break;
					case macroCmd::output:
						cmdQueue.push(new Macro::Output<prec, uint>(pass));
						break;
					case macroCmd::openFiles:
						cmdQueue.push(new Macro::OpenFiles<prec, uint>(pass));
						break;
					case macroCmd::processfiles:
						cmdQueue.push(new Macro::Processfiles<prec, uint>(pass));
						break;
					case macroCmd::reinput:
						cmdQueue.push(new Macro::ReInput<prec, uint>(pass));
						break;
					case macroCmd::solution:
						cmdQueue.push(new Macro::Solution<prec, uint>(pass));
						break;
					case macroCmd::solver:
						cmdQueue.push(new Macro::Solver<prec, uint>(pass));
						break;
					case macroCmd::threads:
						cmdQueue.push(new Macro::Threads<prec, uint>(pass));
						break;
					case macroCmd::history:
						cmdQueue.push(new Macro::PrintHistory<prec, uint>(pass));
						break;
					case macroCmd::propnames:
						cmdQueue.push(new Macro::PropNames<prec, uint>(pass));
						break;
					case macroCmd::propfunction:
						cmdQueue.push(new Macro::PropFunction<prec, uint>(pass));
						break;
					case macroCmd::printpropfunction:
						cmdQueue.push(new Macro::PrintPropFunctions<prec, uint>(pass));
						break;
					case macroCmd::setdt:
						cmdQueue.push(new Macro::SetDt<prec, uint>(pass));
						break;
					case macroCmd::timeincr:
						cmdQueue.push(new Macro::TimeIncr<prec, uint>(pass));
						break;
					case macroCmd::setupsparsematrix:
						cmdQueue.push(new Macro::SetUpSparseMatrix<prec, uint>(pass));
						break;
					case macroCmd::tangent:
						cmdQueue.push(new Macro::Tangent<prec, uint>(pass));
						break;
					case macroCmd::eigenval:
						cmdQueue.push(new Macro::eigenValues<prec, uint>(pass));
						break;
					case macroCmd::prininfo:
						cmdQueue.push(new Macro::printInfo<prec, uint>(pass));
						break;
					default:
						break;
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
				std::map<std::string, meshCmd>::iterator it = this->meshCommands.find(procCmd);
				if (it != this->meshCommands.end()) {
					switch (it->second)
					{
					case meshCmd::exit:
						cmdQueue.push(new meshQuit<prec, uint>(pass));
						break;
					case meshCmd::setmaterial:
						cmdQueue.push(new Mesh::SetMaterial<prec, uint>(pass));
						break;
					case meshCmd::block:
						cmdQueue.push(new Mesh::Block<prec, uint>(pass));
						break;
					case meshCmd::inplanebc:
						cmdQueue.push(new Mesh::InplaneBC<prec, uint>(pass));
						break;
					case meshCmd::inplaneload:
						cmdQueue.push(new Mesh::InplaneLoad<prec, uint>(pass));
						break;
					case meshCmd::setDegreesOfFreedom:
						cmdQueue.push(new Mesh::SetDegreesOfFreedom<prec, uint>(pass));
						break;
					default:
						break;
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
				std::map<std::string, plotCmd>::iterator it = this->plotCommands.find(procCmd);
				if (it != this->plotCommands.end()) {
					switch (it->second)
					{
					case plotCmd::exit:
						cmdQueue.push(new plotQuit<prec, uint>(pass));
						break;
					case plotCmd::mesh:
						cmdQueue.push(new Plot::Mesh<prec, uint>(pass));
						break;
					case plotCmd::interact:
						cmdQueue.push(new Plot::Interact<prec, uint>(pass));
						break;
					case plotCmd::solution:
						cmdQueue.push(new Plot::Solution<prec, uint>(pass));
						break;
					default:
						break;
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
				std::map<std::string, mathCmd>::iterator it = this->mathCommands.find(procCmd);
				if (it != this->mathCommands.end()) {
					switch (it->second)
					{
					case mathCmd::exit:
						cmdQueue.push(new mathQuit<prec, uint>(pass));
						break;
					case mathCmd::list:
						cmdQueue.push(new Math::List<prec, uint>(pass));
						break;
					default:
						break;
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