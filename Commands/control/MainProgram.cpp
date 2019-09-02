/*
 * MainProgram.h
 *
 *  Created on: 25.07.2016
 *      Author: Klarmann
 */

#ifndef MAINPROGRAM_H_
#define MAINPROGRAM_H_


#define MAINTEMP template<typename prec, typename uint>
#define MAINPARAM_ <prec,uint>

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <filehandling/filehandling.h>
#include <control/stringCommandHandler.h>
#include <set>
#include <equations/GeometryData.h>
#include <control/ControlProgram.h>
#include <control/HandlingStructs.hpp>
#include <math/Userconstants.h>
#include <vector>
#include <pointercollection/pointercollection.hpp>
#include <solver/SolverTypes.hpp>
#include <solver/SolutionTypes.hpp>

#include <control/commands/InputParser.hpp>

std::string commentSymbols = "!%";

namespace FEMProject {



	/**
	 * @brief The Main Program Class handles the user interaction.
	 */
	template<typename prec, typename uint>
	class MainProgram {
	public:
		MainProgram(InfoData *info);
		~MainProgram();
		void run();
	
		// Macro Commands
		

	

	
		// Mesh Commands
		void MeshAddVert(stringCommandHandler &passCommand);
	
		// Plot Commands
		void plotMesh(stringCommandHandler &command);
		void plotInteract(stringCommandHandler &command);
	
	
	private:
		typedef void (MainProgram<prec,uint>::*FuncPtr)(stringCommandHandler&);
	
		std::map<std::string,FuncPtr> MacroCMDs, MeshCMDs, PlotCMDs;
		std::set<std::string> ExitCMDs, HelpCMD;

		std::map<std::string, SolverTypes> Solvers;
	
		ControlProgram<prec,uint> *controlProgram;
		
		PointerCollection<prec, uint> *pointers;
	
		InfoData *info; 
		
		Commands::InputParser<prec,uint> CommandParser;

	};
	
	
	/**
	 * @brief The constructor sets up the functions pointer for userinteraction
	 */
	template<typename prec, typename uint>
	MainProgram <prec, uint>::MainProgram(InfoData *info) {
		// TODO Auto-generated constructor stub
	//
	
		this->info = info;
		this->info->runProg = true;
		this->pointers = new PointerCollection<prec, uint>;
		this->pointers->setInfoData(this->info);
		this->pointers->newUserconstants();
	
		this->controlProgram = new ControlProgram<prec,uint>(this->pointers);
	
	
		this->MeshCMDs["vertex"] = &MainProgram<prec,uint>::MeshAddVert;

		this->PlotCMDs["mesh"] = &MainProgram<prec, uint>::plotMesh;
		this->PlotCMDs["interact"] = &MainProgram<prec, uint>::plotInteract;
	
	
		this->ExitCMDs.insert("exit");
		this->ExitCMDs.insert("quit");
		this->ExitCMDs.insert("q");
		this->ExitCMDs.insert("end");
	
		this->HelpCMD.insert("help");

		this->Solvers["eigenpardisoldlt"] = SolverTypes::EigenPardisoLDLT;
		this->Solvers["eigenpardisollt"] = SolverTypes::EigenPardisoLLT;
		this->Solvers["eigenpardisolu"] = SolverTypes::EigenPardisoLU;
		this->Solvers["eigensimplicialldlt"] = SolverTypes::EigenSimplicialLDLT;
		this->Solvers["eigensimplicialllt"] = SolverTypes::EigenSimplicialLLT;
		this->Solvers["eigensparselu"] = SolverTypes::EigenSparseLU;
		this->Solvers["eigensparseqr"] = SolverTypes::EigenSparseQR;


	}
	
	
	/**
	 * @brief Destructor of the main program 
	 */
	template<typename prec, typename uint>
	MainProgram <prec, uint>::~MainProgram() {
		// TODO Auto-generated destructor stub
		delete this->controlProgram;
		delete this->pointers;
	}
	
	/**
	 *@brief starts the main program
	*/
	template<typename prec, typename uint>
	void MainProgram <prec, uint>::run() {
		// TODO main routine to run the program
		stringCommandHandler first;
		while(this->info->runProg){
//			MacroInteraction(first);
		}
	}
		
	
	template<typename prec, typename uint>
	void MainProgram <prec, uint>::MeshAddVert(stringCommandHandler &passCommand){
	
		passCommand.errorReport(this->info->Log, "AddVert");
	}
	


	
	
	template<typename prec, typename uint>
	void MainProgram<prec, uint>::plotMesh(stringCommandHandler &command) {
		this->controlProgram->displayMesh();
	}

	template<typename prec, typename uint>
	void MainProgram<prec, uint>::plotInteract(stringCommandHandler &command) {
		this->controlProgram->plotInteract();
	}



} /* namespace FEMProject */

#undef MAINTEMP
#endif /* MAINPROGRAM_H_ */
