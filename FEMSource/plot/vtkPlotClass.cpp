#ifdef USE_VTK



#include <preprocessDefine.h>

#include <algorithm>
#include <sstream>

#include <plot/vtkplotClass.h>

#include <control/HandlingStructs.h>

#include <equations/GeometryData.h>
#include <equations/GenericNodes.h>
#include <equations/DegreeOfFreedom.h>
#include <equations/NodeSet.h>

#include <finiteElements/ElementList.h>

#include <geometry/GenericGeometryElement.h>

#include <pointercollection/pointercollection.h>
#include <loads/PropfunctionHandler.h>

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
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkXMLMultiBlockDataWriter.h>


#include <regex>

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
		this->step = 0;
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
			this->points->InsertNextPoint(static_cast<double>(coor[0]), static_cast<double>(coor[1]), static_cast<double>(coor[2]));
		
		}
		this->unstructuredGrid->SetPoints(points);
		
		ElementList<prec, uint> *elemList = pointers.getElementList();
		uint numberOfElements = elemList->getNumberOfElements();
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
		vtkSmartPointer<vtkDoubleArray> solutionArray =
			vtkSmartPointer<vtkDoubleArray>::New();
	
	
		GeometryData<prec, uint> *geoData = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *temp;
		uint numVerts = geoData->getNumberOfVertices();
	
		solutionArray->SetNumberOfValues(numVerts);
		solutionArray->SetNumberOfComponents(1);
		solutionArray->SetName("test");
	
		std::vector<GenericNodes<prec, uint>*> nodes;
		std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
	
	
		prec sol;
	
		for (auto i = 0; i < numVerts; ++i) {
			temp = geoData->getGeometryElement(GeometryTypes::Vertex, i);
			temp->getNodesOfSet(pointers, nodes, meshId);
			nodes[0]->getDegreesOfFreedom(pointers, Dofs);
			sol = pointers.getSolutionState()->getSolution(Dofs[comp]->getId());
			solutionArray->SetValue(i, static_cast<double>(sol));
	
		}
		this->unstructuredGrid->GetPointData()->AddArray(solutionArray);
		this->unstructuredGrid->GetPointData()->SetActiveScalars("test");
		double range[2];
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

	template<typename prec, typename uint>
	void vtkPlotInterface<prec, uint>::toFile(PointerCollection<prec, uint>& pointers)
	{
		InfoData *infos = pointers.getInfoData();

		vtkSmartPointer<vtkMultiBlockDataSet> block =
			vtkSmartPointer<vtkMultiBlockDataSet>::New();
		

		std::string outputFile,pvdFile,tempFileName;
		outputFile = infos->fileNames[FileHandling::directory];
		pvdFile = outputFile + "parvout/";
		outputFile += "parvout/model/";
		tempFileName = infos->fileNames[FileHandling::infile];
		std::size_t pos = tempFileName.find(".txt");
		if (pos != std::string::npos) {
			tempFileName = tempFileName.substr(0, pos);
		}
		outputFile += tempFileName;
		pvdFile += tempFileName;
		std::stringstream tempStr;
		tempStr << this->step;
		++this->step;
		outputFile += tempStr.str() + ".vtm";
		pvdFile += ".pvd";

		
		vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
			vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();

		std::replace(outputFile.begin(), outputFile.end(), '\\', '/');

		writer->SetFileName(outputFile.c_str());
		writer->SetDataModeToBinary();

		vtkSmartPointer<vtkUnstructuredGrid> mesh =
			vtkSmartPointer<vtkUnstructuredGrid>::New();
		vtkSmartPointer<vtkPoints> lpoints =
			vtkSmartPointer<vtkPoints>::New();

		block->SetBlock(0, mesh);

		// Adding vertices
		GeometryData<prec, uint> *geoData = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *temp;
		uint numVerts = geoData->getNumberOfVertices();

		this->points->Initialize();

		for (auto i = 0; i < numVerts; ++i) {
			temp = geoData->getGeometryElement(GeometryTypes::Vertex, i);
			std::vector<prec> coor = temp->getCoordinates();
			lpoints->InsertNextPoint(static_cast<double>(coor[0]), static_cast<double>(coor[1]), static_cast<double>(coor[2]));
		}
		mesh->SetPoints(lpoints);


		// Adding Solution fields
		std::map<std::string, vtkSmartPointer<vtkDoubleArray>> sols;
		std::map<std::string, vtkSmartPointer<vtkDoubleArray>> eigenVectors;
		std::string basename = "Solution";
		std::string evBasename = "Eigenvector";
		NodeSet<prec, uint> *tempSet;
		for (auto i = 0; i < numVerts; ++i) {
			temp = geoData->getGeometryElement(GeometryTypes::Vertex, i);
			std::vector<NodeSet<prec, uint>*> sets;
			temp->getSets(pointers, sets);
			// Solution Field
			for (auto j = sets.begin(); j != sets.end(); ++j) {
				tempSet = *j;
				uint id = tempSet->getMeshId();
				uint nnodes = tempSet->getNumberOfNodes();
				for (auto k = 0; k < nnodes; ++k) {
					std::stringstream ArrName;
					ArrName << basename << "M" << id << "N" << k;
					if (sols.find(ArrName.str()) == sols.end()) {
						
						sols.insert(std::make_pair(ArrName.str(), vtkSmartPointer<vtkDoubleArray>::New()));
						vtkSmartPointer<vtkDoubleArray> ArrTemp = sols.find(ArrName.str())->second;
						
						ArrTemp->SetNumberOfComponents(3);
						ArrTemp->SetNumberOfTuples(numVerts);
						ArrTemp->SetName(ArrName.str().c_str());
						ArrTemp->Fill(0);

						mesh->GetPointData()->AddArray(ArrTemp);
					}
					vtkSmartPointer<vtkDoubleArray> ArrTemp = sols.find(ArrName.str())->second;
					std::vector<GenericNodes<prec, uint>*> nodes;
					std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
					temp->getNodesOfSet(pointers, nodes, id);
					nodes[k]->getDegreesOfFreedom(pointers, Dofs);
					for (auto l = 0; l <= 2; ++l) {
						prec sol = pointers.getSolutionState()->getSolution(Dofs[l]->getId());
						ArrTemp->SetComponent(i, l, static_cast<double>(sol));
					}
				}
			}

			//Eigenvectors
 			uint nVecs = pointers.getSolutionState()->numberOfEigenValues();
			for (auto j = 0; j < nVecs; ++j) {
				std::stringstream ArrName;
				ArrName << evBasename << j + 1;
				std::vector<NodeSet<prec, uint>*> sets;
				temp->getSets(pointers, sets);
				for (auto k = sets.begin(); k != sets.end(); ++k) {
					tempSet = *k;
					uint id = tempSet->getMeshId();
					uint nnodes = tempSet->getNumberOfNodes();
					for (auto l = 0; l < nnodes; ++l) {
						ArrName << "M" << id << "N" << l;
						if (eigenVectors.find(ArrName.str()) == eigenVectors.end()) {

							eigenVectors.insert(std::make_pair(ArrName.str(), vtkSmartPointer<vtkDoubleArray>::New()));
							vtkSmartPointer<vtkDoubleArray> ArrTemp = eigenVectors.find(ArrName.str())->second;

							ArrTemp->SetNumberOfComponents(3);
							ArrTemp->SetNumberOfTuples(numVerts);
							ArrTemp->SetName(ArrName.str().c_str());
							ArrTemp->Fill(0);

							mesh->GetPointData()->AddArray(ArrTemp);
						}
						vtkSmartPointer<vtkDoubleArray> ArrTemp = eigenVectors.find(ArrName.str())->second;
						std::vector<GenericNodes<prec, uint>*> nodes;
						std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
						temp->getNodesOfSet(pointers, nodes, id);
						nodes[l]->getDegreesOfFreedom(pointers, Dofs);
						for (auto l = 0; l <= 2; ++l) {
							prec sol;
							if (Dofs[l]->getStatus() != dofStatus::inactive) {
								sol = pointers.getSolutionState()->getEigenVectorComp(Dofs[l]->getEqId(), j);
							}
							else {
								sol = static_cast<prec>(0);
							}
							ArrTemp->SetComponent(i, l, static_cast<double>(sol));
						}
					}
				}
			}
		}

		// Adding elements
		ElementList<prec, uint> *elemList = pointers.getElementList();
		uint numberOfElements = elemList->getNumberOfElements();
		vtkSmartPointer<vtkCell> cellToAdd;
		for (auto i = 0; i < numberOfElements; ++i) {
			elemList->getElement(i)->getVtkCell(pointers, cellToAdd);
			mesh->InsertNextCell(cellToAdd->GetCellType(), cellToAdd->GetPointIds());
		}

		// Adding local nodal reactions
		std::string name = "LocalReactions";
		vtkSmartPointer<vtkDoubleArray> localReac = vtkSmartPointer<vtkDoubleArray>::New();
		localReac->SetName(name.c_str());
		localReac->SetNumberOfComponents(6);
		localReac->SetNumberOfTuples(numVerts);
		localReac->Fill(0);
		for (auto i = 0; i < numberOfElements; ++i) {
			std::map<uint, std::vector<prec>> vReacs;
			elemList->getElement(i)->getElementsLocalNodalReactions(pointers, vReacs);
			for (auto j = vReacs.begin(); j != vReacs.end(); ++j) {
				uint num = j->first;
				std::vector<prec> tempReacVec = j->second;
				for (auto k = 0; k < 6; ++k) {
					localReac->SetComponent(num, k, static_cast<double>(tempReacVec[k]));
				}
			}
		}
		mesh->GetPointData()->AddArray(localReac);
		vtkSmartPointer<vtkXMLMultiBlockDataWriter> pwriter =
			vtkSmartPointer<vtkXMLMultiBlockDataWriter>::New();
		pwriter->SetFileName(outputFile.c_str());
		pwriter->SetInputData(block);

		pwriter->SetEncodeAppendedData(1);
		pwriter->SetDataModeToAppended();

		pwriter->Write();

		std::vector<std::string> Files;
		std::vector<prec> times;
		this->pvdFileReader(pvdFile, Files, times);
        auto posi = outputFile.find("parvout");
        outputFile= outputFile.substr(posi+8,outputFile.length());
		Files.push_back(outputFile);
		times.push_back(pointers.getPropLoads()->getTime(pointers));
		this->pvdFileWriter(pvdFile, Files, times);

	}

	template<typename prec, typename uint>
	void vtkPlotInterface<prec, uint>::pvdFileReader(std::string &pvdFile,std::vector<std::string> &FNames, std::vector<prec> &timesteps)
	{
		FNames.clear(); timesteps.clear();

		std::ifstream file(pvdFile);
		if (file.good()) {
			//file.open(fileName.str());

			std::vector<std::string> fcon;
			std::string line;

			while (std::getline(file, line)) {
				fcon.push_back(line);
			}

			int start = 3;
			int end = static_cast<int>(fcon.size()) - 3;

			std::regex time("timestep=\"([^\"]*)\"");
			std::regex fname("file=\"([^\"]*)\"");
			std::smatch st, sf;
			while (start < end)
			{
				line = fcon[start];
				if (std::regex_search(line, st, time)) {
					double time = std::stod(st[1]);
					line = fcon[start + 1];
					std::regex_search(line, sf, fname);
					timesteps.push_back(time);
					FNames.push_back(sf[1]);
				}

				start += 2;
			}



		}
		file.close();
        
        FNames.erase(FNames.begin()+this->step-1,FNames.end());
        timesteps.erase(timesteps.begin()+this->step-1,timesteps.end());

	}

	template<typename prec, typename uint>
	void vtkPlotInterface<prec, uint>::pvdFileWriter(std::string &pvdFile,std::vector<std::string> &FNames, std::vector<prec> &timesteps)
	{
		std::ofstream file;
		file.open(pvdFile);

		std::string space;
		space = "  ";

		file << "<?xml version =\"1.0\"?>\n"
			<< "<VTKFile type=\"Collection\" version=\"0.1\">\n";

		file << space << "<Collection>\n";
		space = "    ";

		for (auto i = 0; i < this->step;++i) {
			file << space << "<DataSet timestep=\"" << timesteps[i] << "\" group=\"\" part=\"\"\n"
				<< space << "file=\"" << FNames[i] << "\"/>\n"; //.substr(pos+1,FNames[i].length())
		}


		space = "  ";
		file << space << "</Collection>\n</VTKFile>" << std::endl;

		file.close();
	}


	
}

instantiate(vtkPlotInterface)

#endif // USE_VTK
