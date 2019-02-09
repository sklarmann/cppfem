#include <include/MainProgram.h>
#include <plot/vtkplotClassBase.h>


#include <control/FEMProgram.h>
#include <control/HandlingStructs.h>
#include <pointercollection/pointercollection.h>


namespace FEMProject 
{
	template<typename prec,typename uint>
	MainProgram<prec,uint>::MainProgram() {
		this->infos = new InfoData;
		this->pointers = new PointerCollection<prec, uint>;
		this->pointers->setInfoData(this->infos);
		this->program = new FEMProgram<prec, uint>(this->pointers);
	}

	template<typename prec, typename uint>
	MainProgram<prec,uint>::~MainProgram() {
		delete this->pointers;
		delete this->pointers;
		delete this->infos;
	}

	template<typename prec, typename uint>
	void MainProgram<prec, uint>::test() {

	}


	template<typename prec, typename uint>
	void MainProgram<prec, uint>::run() {
		this->program->run(this->pointers);
	}

	template<typename prec, typename uint>
	InfoData * MainProgram<prec, uint>::getInfoData()
	{
		return this->pointers->getInfoData();
	}

	template<typename prec, typename uint>
	void MainProgram<prec, uint>::processExternalMacroCmd(std::string &cmd)
	{
		this->program->parseExternalMacro(this->pointers, cmd);
	}

	template<typename prec, typename uint>
	void MainProgram<prec, uint>::processExternalMeshCmd(std::string &cmd)
	{
		this->program->parseExternalMesh(this->pointers,cmd);
	}

	template<typename prec, typename uint>
	void MainProgram<prec, uint>::processExternalPlotCmd(std::string &cmd)
	{
		this->program->parseExternalPlot(this->pointers,cmd);
	}

	//template<typename prec, typename uint>
	//vtkRenderer *MainProgram<prec, uint>::getRenderer()
	//{
	//
	//	//vtkSmartPointer<vtkRenderer renderer = this->pointers->getVtkPlotInterface()->getRenderer();
	//	return this->pointers->getVtkPlotInterface()->getRenderer();
	//	
	//}

	template<typename prec, typename uint>
	vtkUnstructuredGrid * MainProgram<prec, uint>::getGrid()
	{
		return this->pointers->getVtkPlotInterface()->getGrid();
	}


}

instantiate(MainProgram)