#ifdef USE_VTK



#include <preprocessDefine.h>

#include <plot/vtkplotClass.h>

#include <equations/GeometryData.h>
#include <equations/GenericNodes.h>
#include <equations/DegreeOfFreedom.h>

#include <finiteElements/ElementList.h>

#include <geometry/GenericGeometryElement.h>

#include <pointercollection/pointercollection.h>

#include <solver/GenericSolutionState.h>


#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDoubleArray.h>
#include <vtkLine.h>
#include <vtkTriangle.h>
#include <vtkExtractEdges.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGridGeometryFilter.h>
#include <vtkFloatArray.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <vtkCell.h>



namespace FEMProject {

	template<typename prec, typename uint>
	inline vtkPlotInterface<prec, uint>::vtkPlotInterface()
	{
		this->points = vtkSmartPointer<vtkPoints>::New();
		this->cells = vtkSmartPointer<vtkCellArray>::New();
		this->unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		this->mapper = vtkSmartPointer<vtkDataSetMapper>::New();
		this->actor = vtkSmartPointer<vtkActor>::New();
		this->renderer = vtkSmartPointer<vtkRenderer>::New();
		this->renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		this->scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
		this->hueLut = vtkSmartPointer<vtkLookupTable>::New();
	}

	template<typename prec, typename uint>
	inline void vtkPlotInterface<prec, uint>::mesh(PointerCollection<prec, uint>& pointers)
	{
		GeometryData<prec, uint> *geoData = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *temp;
		uint numVerts = geoData->getNumberOfVertices();
		
		this->points->Initialize();
		
		for (auto i = 0; i < numVerts; ++i) {
			temp = geoData->getGeometryElement(GeometryTypes::Vertex, i);
			std::vector<prec> coor = temp->getCoordinates();
			this->points->InsertNextPoint(static_cast<float>(coor[0]), static_cast<float>(coor[1]), static_cast<float>(coor[2]));
		
		}
		this->unstructuredGrid->SetPoints(points);
		
		ElementList<prec, uint> *elemList = pointers.getElementList();
		uint numberOfElements = elemList->getNumberOfElements();
		GenericFiniteElement<prec, uint> *elem;
		vtkSmartPointer<vtkCell> cellToAdd;
		for (auto i = 0; i < numberOfElements; ++i) {
			elemList->getElement(i)->getVtkCell(pointers, cellToAdd);
			this->unstructuredGrid->InsertNextCell(cellToAdd->GetCellType(), cellToAdd->GetPointIds());
		}
		
		this->mapper->SetInputData(this->unstructuredGrid);
		this->mapper->Update();
		this->actor->SetMapper(this->mapper);
		this->renderWindow->AddRenderer(this->renderer);
		this->renderer->AddActor(this->actor);
		this->renderer->SetBackground(.3, .6, .3);
		this->renderWindow->Render();


	}

	template<typename prec, typename uint>
	inline void vtkPlotInterface<prec, uint>::solution(PointerCollection<prec, uint>& pointers, uint & meshId, uint & comp)
	{
		vtkSmartPointer<vtkFloatArray> solutionArray =
			vtkSmartPointer<vtkFloatArray>::New();
	
	
		GeometryData<prec, uint> *geoData = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *temp;
		uint numVerts = geoData->getNumberOfVertices();
	
		solutionArray->SetNumberOfValues(numVerts);
		solutionArray->SetNumberOfComponents(1);
		solutionArray->SetName("test");
	
		std::vector<GenericNodes<prec, uint>*> nodes;
		std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
		DegreeOfFreedom<prec, uint>* test;
	
	
		prec sol;
	
		for (auto i = 0; i < numVerts; ++i) {
			temp = geoData->getGeometryElement(GeometryTypes::Vertex, i);
			temp->getNodesOfSet(pointers, nodes, meshId);
			nodes[0]->getDegreesOfFreedom(pointers, Dofs);
			sol = pointers.getSolutionState()->getSolution(Dofs[comp]->getId());
			solutionArray->SetValue(i, static_cast<float>(sol));
	
		}
		this->unstructuredGrid->GetPointData()->AddArray(solutionArray);
		this->unstructuredGrid->GetPointData()->SetActiveScalars("test");
		float range[2];
		solutionArray->GetValueRange(range);
		this->mapper->InterpolateScalarsBeforeMappingOn();
		this->mapper->SetScalarRange(range[0], range[1]);
	
		this->scalarBar->SetLookupTable(mapper->GetLookupTable());
		this->scalarBar->SetTitle("Title");
		this->scalarBar->SetNumberOfLabels(4);
		this->hueLut->SetRange(0, 1);
		this->hueLut->SetTableRange(0, 1);
		//this->hueLut->SetHueRange(0, 1);
		this->hueLut->SetSaturationRange(1, 1);
		this->hueLut->SetValueRange(1, 1);
		this->hueLut->Build();
	
		this->mapper->SetLookupTable(hueLut);
		this->scalarBar->SetLookupTable(hueLut);
	
		this->mapper->Update();
		this->renderer->AddActor2D(this->scalarBar);
	
		this->renderWindow->Render();
	
	}

	//template<typename prec, typename uint>
	//vtkSmartPointer<vtkRenderer>& vtkPlotInterface<prec, uint>::getRenderer()
	//{
	//	return this->renderer;
	//}

	template<typename prec, typename uint>
	vtkUnstructuredGrid *vtkPlotInterface<prec, uint>::getGrid()
	{
		return this->unstructuredGrid.GetPointer();
	}

	template<typename prec, typename uint>
	inline void vtkPlotInterface<prec, uint>::interact()
	{
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(this->renderWindow);
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Start();
	}


	
}

instantiate(vtkPlotInterface)

#endif // USE_VTK