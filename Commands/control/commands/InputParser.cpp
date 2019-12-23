
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
      this->macroCommands["quit"] = &macroQuit<prec, uint>::NewCommand;
      this->macroCommands["end"] = &macroQuit<prec, uint>::NewCommand;
      this->macroCommands["exit"] = &macroQuit<prec, uint>::NewCommand;
      ////-----#Transfer-------------------------------------------------
      this->macroCommands["mesh"] = &meshInteract<prec, uint>::NewCommand;
      this->macroCommands["plot"] = &plotInteract<prec, uint>::NewCommand;
      this->macroCommands["math"] = &mathInteract<prec, uint>::NewCommand;
      
      ////-----#Main Control---------------------------------------------
      this->macroCommands["open"] = &Macro::OpenFiles<prec, uint>::NewCommand;
      this->macroCommands["output"] = &Macro::Output<prec, uint>::NewCommand;
      this->macroCommands["processfiles"] = &Macro::Processfiles<prec, uint>::NewCommand;
      this->macroCommands["rinp"] = &Macro::ReInput<prec, uint>::NewCommand;
      this->macroCommands["threads"] = &Macro::Threads<prec, uint>::NewCommand;
      this->macroCommands["printinfo"] = &Macro::printInfo<prec, uint>::NewCommand;
      this->macroCommands["history"] = &Macro::PrintHistory<prec, uint>::NewCommand;
      this->macroCommands["printsolution"] = &Macro::PrintSolution<prec, uint>::NewCommand;
      this->macroCommands["printspmat"] = &Macro::PrintSpMat<prec, uint>::NewCommand;
      this->macroCommands["do"] = &Macro::Do<prec, uint>::NewCommand;
      this->macroCommands["digits"] = &Macro::OutputPrecision<prec, uint>::NewCommand;
      this->macroCommands["getval"] = &Macro::ValueToUserVar<prec, uint>::NewCommand;
      this->macroCommands["vartofile"] = &Macro::UserVarToFile<prec, uint>::NewCommand;
      this->macroCommands["runfile"] = &Macro::RunFile<prec, uint>::NewCommand;
      this->macroCommands["input"] = &Macro::includeFile<prec, uint>::NewCommand;
      //
      //
      this->macroCommands["solution"] = &Macro::Solution<prec, uint>::NewCommand;
      this->macroCommands["solver"] = &Macro::Solver<prec, uint>::NewCommand;
      this->macroCommands["sparsesetup"] = &Macro::SetUpSparseMatrix<prec, uint>::NewCommand;
      //
      this->macroCommands["condition"] = &Macro::ComputeConditionNumber<prec, uint>::NewCommand;
      this->macroCommands["eigenval"] = &Macro::eigenValues<prec, uint>::NewCommand;
      this->macroCommands["newton"] = &Macro::Newton<prec, uint>::NewCommand;
      this->macroCommands["tangent"] = &Macro::Tangent<prec, uint>::NewCommand;
      this->macroCommands["resetsolution"] = &Macro::ResetSolution<prec, uint>::NewCommand;
      //
      this->macroCommands["propnames"] = &Macro::PropNames<prec, uint>::NewCommand;
      this->macroCommands["propfunction"] = &Macro::PropFunction<prec, uint>::NewCommand;
      this->macroCommands["printpropfunction"] = &Macro::PrintPropFunctions<prec, uint>::NewCommand;
      this->macroCommands["dt"] = &Macro::SetDt<prec, uint>::NewCommand;
      this->macroCommands["timeincr"] = &Macro::TimeIncr<prec,uint>::NewCommand;
      //
      //----------//--------MESH----------------------------------------------------
      ////-----#Exit----------------------------------------------------
      this->meshCommands["quit"] = &meshQuit<prec, uint>::NewCommand;
      this->meshCommands["exit"] = &meshQuit<prec, uint>::NewCommand;
      this->meshCommands["end"] = &meshQuit<prec, uint>::NewCommand;
      //
      this->meshCommands["addvertex"] = &Mesh::AddVertex<prec, uint>::NewCommand;
      this->meshCommands["addgeoelement"] = &Mesh::AddGeometryElement<prec, uint>::NewCommand;
      this->meshCommands["addfiniteelement"] = &Mesh::AddFiniteElement<prec, uint>::NewCommand;
      this->meshCommands["block"] = &Mesh::Block<prec, uint>::NewCommand;
      this->meshCommands["setbc"] = &Mesh::SetBoundaryConditions<prec, uint>::NewCommand;
      this->meshCommands["setmaterials"] = &Mesh::SetMaterial<prec, uint>::NewCommand;
      this->meshCommands["setdofs"] = &Mesh::SetDegreesOfFreedom<prec, uint>::NewCommand;
      this->meshCommands["linkdofs"] = &Mesh::linkDofs<prec, uint>::NewCommand;
      //
      this->meshCommands["inplanebc"] = &Mesh::InplaneBC<prec, uint>::NewCommand;
	  this->meshCommands["inplaneload"] = &Mesh::InplaneLoad<prec, uint>::NewCommand;
	  this->meshCommands["singlebc"] = &Mesh::SingleBC<prec, uint>::NewCommand;
	  this->meshCommands["singleload"] = &Mesh::SingleLoad<prec, uint>::NewCommand;
      //
      //----------//--------PLOT----------------------------------------------------
      ////-----#Exit----------------------------------------------------
      this->plotCommands["quit"] = &plotQuit<prec, uint>::NewCommand;
      this->plotCommands["exit"] = &plotQuit<prec, uint>::NewCommand;
      this->plotCommands["end"] = &plotQuit<prec, uint>::NewCommand;
      //
      this->plotCommands["interact"] = &Plot::Interact<prec, uint>::NewCommand;
      //
      this->plotCommands["mesh"] = &Plot::Mesh<prec, uint>::NewCommand;
      this->plotCommands["solution"] = &Plot::Solution<prec, uint>::NewCommand;
      //
      this->plotCommands["paraview"] = &Plot::Paraview<prec, uint>::NewCommand;
      //----------//--------MATH----------------------------------------------------
      ////-----#Exit----------------------------------------------------
      this->mathCommands["quit"] = &mathQuit<prec, uint>::NewCommand;
      this->mathCommands["end"] = &mathQuit<prec, uint>::NewCommand;
      this->mathCommands["exit"] = &mathQuit<prec, uint>::NewCommand;
      //
      this->mathCommands["list"] = &Math::List<prec, uint>::NewCommand;
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
