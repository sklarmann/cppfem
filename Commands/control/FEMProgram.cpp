
#include <preprocessDefine.h>

#include <control/FEMProgram.h>

#include <control/commands/GenericCommand.h>
#include <control/stringCommandHandler.h>

#include <pointercollection/pointercollection.h>

#include <queue>


namespace FEMProject {

	template<typename prec, typename uint>
	FEMProgram<prec, uint>::FEMProgram(PointerCollection<prec, uint> *pointers) {
		this->macroRun = true;
		this->plotRun = false;
		this->meshRun = false;
		this->mathRun = false;

		pointers->newGeometry();
		pointers->newEqHandler();
		pointers->newElementList();
		pointers->newMaterialList();
		pointers->newLoadList();
		pointers->newUserconstants();
		pointers->newVtkPlot();
		
	}

	template<typename prec, typename uint>
	FEMProgram<prec, uint>::~FEMProgram() {
		for (auto i = 0; i < this->CommandHistory.size(); ++i) {
			delete this->CommandHistory[i];
		}
		CommandHistory.clear();
	}


	/** 
	* @brief User Text Interaction, Handles user commands and passes them to the right parser.
	*/
	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::run(PointerCollection<prec, uint> *pointers) {

		while (this->macroRun) {
			std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
			if (this->meshRun) {
				stringCommandHandler userCommand;
				userCommand.userInteraction("Mesh>");
				this->parser.parseMesh(userCommand, cmdQueue);
			}
			else if (this->plotRun) {
				stringCommandHandler userCommand;
				userCommand.userInteraction("Plot>");
				this->parser.parsePlot(userCommand, cmdQueue);
			}
			else if (this->mathRun) {
				stringCommandHandler userCommand;
				userCommand.userInteraction("Math>");
				this->parser.parseMath(userCommand, cmdQueue);
			}
			else {
				stringCommandHandler userCommand;
				userCommand.userInteraction("Macro>");
				this->parser.parseMacro(userCommand, cmdQueue);
			}
			this->processCommands(pointers,cmdQueue);
		}
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::processCommands(PointerCollection<prec, uint> *pointers, std::queue<Commands::GenericCommand<prec, uint>*> &cmdQueue) {

		while (!cmdQueue.empty()) {
			Commands::GenericCommand<prec, uint>* Command;
			Command = cmdQueue.front();
			cmdQueue.pop();
			this->CommandHistory.push_back(Command);
			Command->run(*pointers, this);
		}
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::processExternalCommand(PointerCollection<prec, uint>* pointers, Commands::GenericCommand<prec, uint> *Command)
	{
		std::cout << "test2" << std::endl;
		Command->run(*pointers, this);
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::printHist() {
		auto end = this->CommandHistory.size();
		for (auto i = 0; i < end; ++i) {
			std::cout << *this->CommandHistory[i] << std::endl;
		}
	}

	
	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::parseExternalMacro(PointerCollection<prec, uint>* pointers, std::string & cmd)
	{
		std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
		stringCommandHandler passCmd;
		passCmd = cmd;
		this->parser.parseMacro(passCmd, cmdQueue);
		this->processCommands(pointers, cmdQueue);
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::parseExternalMesh(PointerCollection<prec, uint>* pointers, std::string & cmd)
	{
		std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
		stringCommandHandler passCmd;
		passCmd = cmd;
		this->parser.parseMesh(passCmd, cmdQueue);
		this->processCommands(pointers, cmdQueue);
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::parseExternalMath(PointerCollection<prec, uint>* pointers, std::string & cmd)
	{
		std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
		stringCommandHandler passCmd;
		passCmd = cmd;
		this->parser.parseMath(passCmd, cmdQueue);
		this->processCommands(pointers, cmdQueue);
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::parseExternalPlot(PointerCollection<prec, uint>* pointers, std::string & cmd)
	{
		std::queue<Commands::GenericCommand<prec, uint>*> cmdQueue;
		stringCommandHandler passCmd;
		passCmd = cmd;
		this->parser.parsePlot(passCmd, cmdQueue);
		this->processCommands(pointers, cmdQueue);
	}

	template<typename prec, typename uint>
	void FEMProgram<prec, uint>::ReInput(PointerCollection<prec,uint> &pointers) {
		pointers.renew();
		//delete pointers;
		//pointers = new PointerCollection<prec, uint>;
		//pointers->setInfoData(&this->infodata);
		//pointers->newGeometry();
		//pointers->newEqHandler();
		//pointers->newElementList();
		//pointers->newMaterialList();
		//pointers->newLoadList();
		//pointers->newUserconstants();
		//pointers->newVtkPlot();
		for (auto i = 0; i < this->CommandHistory.size(); ++i) {
			delete this->CommandHistory[i];
		}
		CommandHistory.clear();
	}

}

instantiate(FEMProgram)

