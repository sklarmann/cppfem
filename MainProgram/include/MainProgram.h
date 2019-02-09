
#pragma once

#include <MainProgramBase.h>

#include <preprocessDefine.h>


class vtkUnstructuredGrid;



namespace FEMProject {

	template<typename prec, typename uint>
	class FEMProgram;

	template<typename prec, typename uint>
	class PointerCollection;

	struct InfoData;

	template <typename prec, typename uint>
	class MainProgram : public MainProgramBase {
	public:
		MainProgram();
		~MainProgram();
		void test();
		void run();
		InfoData *getInfoData();
		void processExternalMacroCmd(std::string &cmd);
		void processExternalMeshCmd(std::string &cmd);
		void processExternalPlotCmd(std::string &cmd);
		//vtkSmartPointer<vtkRenderer> &getRenderer();
		vtkUnstructuredGrid *getGrid();

	private:
		FEMProject::FEMProgram<prec, uint> *program;
		FEMProject::PointerCollection<prec, uint> *pointers;
		FEMProject::InfoData *infos;
	};
}

instantiateHeader(MainProgram)