/*
 * ControlProgram.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#ifndef CONTROLPROGRAM_H_
#define CONTROLPROGRAM_H_

#include <solver/GenericSolutionState.hpp>
#include <solver/SolutionTypes.hpp>
#include <geometry/GenericGeometryElement.h>
#include <equations/EquationHandler.h>
#include <equations/GeometryData.h>
#include <finiteElements/ElementList.h>
#include <vector>
#include <shapefunctions/Lobatto.hpp>
#include <materials/MaterialList.hpp>
#include <stack>
#include <pointercollection/pointercollection.hpp>
#include <math/Userconstants.h>
#include <elementFormulations/GenericElementFormulation.hpp>
#include <finiteElements/GenericFiniteElement.h>
#include <control/stringCommandHandler.h>
#include <omp.h>

#include<control/Timer.hpp>

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
#include <thread>

namespace FEMProject {
	enum blockTypes{quadlinear};
	
	
	void fnPointerTest()
	{
		std::cout << "Done" << std::endl;
	}
	
	
	
	template<typename prec, typename uint>
	class ControlProgram {
	public:
		ControlProgram(PointerCollection<prec,uint> *pointers);
		~ControlProgram();
		GeometryData<prec, uint> *getGeometry() { return this->geometryData; };
			
	
		void checkData();

		void displayMesh();
		void plotInteract();

	
	private:
		PointerCollection<prec,uint> *pointers;
		Userconstants<prec> *ucons;
	
		vtkSmartPointer<vtkPoints> points;
		vtkSmartPointer<vtkCellArray> cells;
		vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid;
		vtkSmartPointer<vtkDataSetMapper> mapper;
		vtkSmartPointer<vtkActor> actor;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
	
		//Solutionstate<prec, uint> *activeSolutionState;
		//EquationHandler<prec,uint> *eqHandler;
		//GeometryData<prec,uint> *geometryData;
		//ElementList<prec,uint>  *elementList;
		//MaterialList<prec,uint> *materialList;
	};
	
	/**
	 * @brief Constructor to allocate the necessary classes.
	 */
	template<typename prec, typename uint>
	ControlProgram<prec,uint>::ControlProgram(PointerCollection<prec, uint> *pointers){
		
		this->pointers = pointers;
		this->pointers->newGeometry();
		this->pointers->newEqHandler();
		this->pointers->newElementList();
		this->pointers->newMaterialList();
		this->pointers->newPropLoads();
		this->pointers->newLoadList();
	
		this->points = vtkSmartPointer<vtkPoints>::New();
		this->cells  = vtkSmartPointer<vtkCellArray>::New();
		this->unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
		this->mapper = vtkSmartPointer<vtkDataSetMapper>::New();
		this->actor = vtkSmartPointer<vtkActor>::New();
		this->renderer = vtkSmartPointer<vtkRenderer>::New();
		this->renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	}
	
	/**
	 * @brief Destructor to free the space again.
	 */
	template<typename prec, typename uint>
	ControlProgram<prec,uint>::~ControlProgram(){
		
	}
	
	
	
	
	template<typename prec, typename uint>
	void ControlProgram<prec,uint>::displayMesh(){
		
		
	
		GeometryData<prec, uint> *geoData = this->pointers->getGeometryData();
	
		uint numberOfVerts = geoData->getNumberOfVertices();
		ElementList<prec, uint> *elemList = this->pointers->getElementList();
		vtkSmartPointer<vtkIntArray> weights =
					  vtkSmartPointer<vtkIntArray>::New();
	
		weights->SetNumberOfValues(numberOfVerts);
		weights->SetNumberOfComponents(1);
		weights->SetName("test");
	
		GenericGeometryElement<prec,uint> *temp;

		this->points->Initialize();

		for(uint i=0;i<numberOfVerts;++i){
			temp = geoData->getGeometryElement(GeometryTypes::Vertex,i);
			std::vector<prec> coor = temp->getCoordinates();
			this->points->InsertNextPoint(static_cast<float>(coor[0]), static_cast<float>(coor[1]), static_cast<float>(coor[2]));
	//		weights->InsertValue(i);
			weights->SetValue(i,i);
	
		}
	
	
		vtkSmartPointer<vtkTriangle> triangle =
				vtkSmartPointer<vtkTriangle>::New();

		uint numberOfElements = elemList->getNumberOfElements();
		std::vector<uint> verts;
	
		GenericFiniteElement<prec,uint> *temp2;

		this->unstructuredGrid->SetPoints(points);
		for(uint i=0;i<numberOfElements;++i){
			temp2 = elemList->getElement(i);
			verts = temp2->getVertexIds();
			triangle->GetPointIds()->SetId(0,verts[0]);
			triangle->GetPointIds()->SetId(1,verts[1]);
			triangle->GetPointIds()->SetId(2,verts[2]);
			//this->cells->InsertNextCell(triangle);
			this->unstructuredGrid->InsertNextCell(triangle->GetCellType(), triangle->GetPointIds());
	//
	//		line->GetPointIds()->SetId(0,verts[0]);
	//		line->GetPointIds()->SetId(1,verts[1]);
	//		cellArray->InsertNextCell(line);
		}
		//this->unstructuredGrid->SetCells(VTK_TRIANGLE, this->cells);
		
		this->unstructuredGrid->GetPointData()->AddArray(weights);
	
		this->unstructuredGrid->GetPointData()->SetActiveScalars("test");
	
	//	vtkSmartPointer<vtkSphereSource> sphereSource =
	//	    vtkSmartPointer<vtkSphereSource>::New();
	//	  sphereSource->Update();
	//
	
	
	
	
	
		this->mapper->SetInputData(this->unstructuredGrid);
	
	//	mapper->SetScalarRange(0,numberOfVerts);
		this->mapper->Update();
	
	//	vtkSmartPointer<vtkUnstructuredGridGeometryFilter> geofilter =
	//			vtkSmartPointer<vtkUnstructuredGridGeometryFilter>::New();
	
	//	geofilter->SetInputData(unstructuredGrid);
	//	geofilter->Update();
	
	
	//	vtkSmartPointer<vtkExtractEdges> extractEdges =
	//			vtkSmartPointer<vtkExtractEdges>::New();
	//	extractEdges->SetInputDataObject(geofilter->GetOutput());
	//			  extractEdges->Update();
	//	vtkCellArray* lines= extractEdges->GetOutput()->GetLines();
	//
	//	std::cout << "number of edges " << lines->GetNumberOfCells() << std::endl;
	
	
	
	//	unstructuredGrid->Delete();
	//	unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
	//	unstructuredGrid->SetPoints(points);
	//	unstructuredGrid->SetCells(VTK_LINE,lines);
	
		this->mapper->SetInputData(this->unstructuredGrid);

		this->mapper->InterpolateScalarsBeforeMappingOn();
		this->mapper->Update();
	
	//	std::cout << *lines;
	
		this->actor->SetMapper(this->mapper);
	
		
		this->renderWindow->AddRenderer(this->renderer);
	
		this->renderer->AddActor(this->actor);
		this->renderer->SetBackground(.3, .6, .3);
		
	
		this->renderWindow->Render();

		
		//
		//
		this->mapper->SetScalarRange(0, numberOfVerts);
		this->renderWindow->Modified();
		this->renderWindow->Render();
		//
		
	}

	template<typename prec, typename uint>
	void ControlProgram<prec, uint>::plotInteract() {
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(this->renderWindow);
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Start();
	}
	
	

	
	template<typename prec, typename uint>
	void ControlProgram<prec, uint>::checkData() {
		ElementList<prec, uint> *elemList = this->pointers.getElementList();
		uint numberOfElements;
		numberOfElements = elemList->getNumberOfElements();
	
		for (uint i = 0; i < numberOfElements; ++i) {
			GenericFiniteElement<prec, uint> *elem;
			elem = elemList->getElement(i);
			elementLibrary(*elem, ControlOptions::CheckData);
		}
	
		
	}

} /* namespace FEMProject */

#endif /* CONTROLPROGRAM_H_ */
