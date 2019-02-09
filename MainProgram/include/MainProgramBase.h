#pragma once

#include <string>

class vtkUnstructuredGrid;

namespace FEMProject {

	struct InfoData;

	class MainProgramBase
	{
	public:
		virtual void test() = 0;
		virtual void run() = 0;
		virtual InfoData *getInfoData() = 0;
		virtual void processExternalMacroCmd(std::string &cmd) = 0;
		virtual void processExternalMeshCmd(std::string &cmd) = 0;
		virtual void processExternalPlotCmd(std::string &cmd) = 0;
		//virtual vtkSmartPointer<vtkRenderer> &getRenderer() = 0;
		virtual vtkUnstructuredGrid *getGrid() = 0;
	};

}