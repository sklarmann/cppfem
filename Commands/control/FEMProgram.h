
#pragma once

#include <preprocessDefine.h>
#include <forwarddeclaration.h>

#include <control/HandlingStructs.h>
#include <control/commands/InputParser.h>

#include <vector>
#include <queue>

instantiateHeader(FEMProgram)

namespace FEMProject {

	template<typename prec, typename uint>
	class FEMProgram {
	public:
		FEMProgram(PointerCollection<prec,uint> *pointers);
		~FEMProgram();
		void run(PointerCollection<prec, uint> *pointers);
		void processCommands(PointerCollection<prec, uint> *pointers,std::queue<Commands::GenericCommand<prec, uint>*> &cmdQueue);
		void processExternalCommand(PointerCollection<prec, uint> *pointers, Commands::GenericCommand<prec, uint> *cmd);
		void enableUserPlot() { this->plotRun = true; };
		void enableUserMesh() { this->meshRun = true; };
		void enableUserMath() { this->mathRun = true; };
		void disableUserPlot() { this->plotRun = false; };
		void disableUserMesh() { this->meshRun = false; };
		void disableUserMath() { this->mathRun = false; };
		void disableUserMacro() { this->macroRun = false; };
		void parseExternalMacro(PointerCollection<prec, uint> *pointers, std::string &cmd);
		void parseExternalMesh(PointerCollection<prec, uint> *pointers, std::string &cmd);
		void parseExternalMath(PointerCollection<prec, uint> *pointers, std::string &cmd);
		void parseExternalPlot(PointerCollection<prec, uint> *pointers, std::string &cmd);
		//InfoData *getInfoData() { return &this->infodata; };
		void ReInput(PointerCollection<prec,uint> &pointers);

		void printHist();

	private:
		bool macroRun, plotRun, meshRun, mathRun;
		std::vector<Commands::GenericCommand<prec, uint>*> CommandHistory;
		Commands::InputParser<prec, uint> parser;

		PointerCollection<prec, uint> *pointers;
		InfoData infodata;

	};

}

