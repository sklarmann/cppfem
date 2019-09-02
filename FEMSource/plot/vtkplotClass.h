
#pragma once

#ifdef USE_VTK




#include <forwarddeclaration.h>

#include <plot/vtkplotClassBase.h>


#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <vtkDataSetMapper.h>

namespace FEMProject {

	

	template<typename prec, typename uint>
	class vtkPlotInterface : public vtkPlotInterfaceBase<prec,uint> {
	public:
		vtkPlotInterface();
		~vtkPlotInterface() {};

		void mesh(PointerCollection<prec, uint> &pointers);
		void solution(PointerCollection<prec, uint> &pointers, uint &meshId, uint &comp);
		//vtkRenderer *getRenderer();
		vtkUnstructuredGrid *getGrid();
		void interact();

		void toFile(PointerCollection<prec, uint> &pointers);

	private:
		void pvdFileReader(std::string &pvdFile,std::vector<std::string> &FNames, std::vector<prec> &timesteps);
		void pvdFileWriter(std::string &pvdFile,std::vector<std::string> &FNames, std::vector<prec> &timesteps);

		vtkSmartPointer<vtkPoints> points;
		vtkSmartPointer<vtkCellArray> cells;
		vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid;
		vtkSmartPointer<vtkDataSetMapper> mapper;
		vtkSmartPointer<vtkActor> actor;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
		vtkSmartPointer<vtkScalarBarActor> scalarBar;
		vtkSmartPointer<vtkLookupTable> hueLut;
		uint step;
		std::vector<prec> timesteps;
	};



}
#endif // USE_VTK