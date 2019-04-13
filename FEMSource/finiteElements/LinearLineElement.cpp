#include <preprocessDefine.h>

#include <finiteElements/GenericFiniteElement.h>
#include <finiteElements/LinearLineElement.h>

#include <pointercollection/pointercollection.h>

#include <geometry/GenericGeometryElement.h>

#include <equations/GeometryData.h>

#include <control/OutputHandler.h>
#include <control/HandlingStructs.h>

#include <solver/GenericSolutionState.h>

#ifdef USE_VTK
#include <vtkSmartPointer.h>
#include <vtkCell.h>
#include <vtkPolyLine.h>
#endif // USE_VTK



namespace FEMProject {

	template<typename prec, typename uint>
	LinearLineElement<prec, uint>::LinearLineElement(PointerCollection<prec, uint> *pointers) :
		GenericFiniteElement<prec, uint>() {

	}

	template<typename prec, typename uint>
	LinearLineElement<prec, uint>::~LinearLineElement() {

	}

	template<typename prec, typename uint>
	void LinearLineElement<prec, uint>::setVerts(std::vector<uint>& vertsIn)
	{
		if (vertsIn.size() == 2) {
			this->verts[0] = vertsIn[0];
			this->verts[1] = vertsIn[1];
		}
		else {
		}
	}

	template<typename prec, typename uint>
	void LinearLineElement<prec, uint>::setEdges(std::vector<uint>& edgesIn)
	{
		if (edgesIn.size() == 1) {
			this->edge = edgesIn[0];
		}
	}

	template<typename prec, typename uint>
	GenericGeometryElement<prec, uint>* LinearLineElement<prec, uint>::getVertex(ptrCol & pointers, const uint & num)
	{
		GeometryData<prec, uint> *geodata = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *geotemp;
		geotemp = geodata->getEdge(this->edge);
		std::vector<uint> verts;
		geotemp->getVerts(verts);
		if (num>=verts.size()) return nullptr;
		return geodata->getVertex(verts[num]);
	}

	template<typename prec, typename uint>
	void LinearLineElement<prec, uint>::setUpSparseMatrix(ptrCol & pointers)
	{
		GeometryData<prec, uint> *geodata = pointers.getGeometryData();

		GenericGeometryElement<prec, uint> *tempGeo, *thisedge;

		std::vector<DegreeOfFreedom<prec, uint>*> tempDofs, Dofs;

		thisedge = geodata->getEdge(this->edge);
		std::vector<uint> vertNums;
		thisedge->getVerts(vertNums);
		for (auto i = vertNums.begin(); i != vertNums.end(); ++i) {
			tempGeo = geodata->getVertex(*i);
			tempGeo->getAllEquationsIds(pointers, tempDofs);
			for (auto j = tempDofs.begin(); j != tempDofs.end(); ++j) {
				Dofs.push_back(*j);
			}
		}

		GenericSolutionState<prec, uint> *tsol =
			pointers.getSolutionState();
		tsol->setTripletList(Dofs);
		
	}

	template<typename prec, typename uint>
	void LinearLineElement<prec, uint>::getVtkCell(PointerCollection<prec, uint> &ptrCol, vtkSmartPointer<vtkCell> &cell)
	{
#ifdef USE_VTK
		vtkSmartPointer<vtkCell> line =
			vtkSmartPointer<vtkPolyLine>::New();
		GenericGeometryElement<prec, uint> *geoEdge;
		GeometryData<prec, uint> *geoData;
		std::vector<uint> vertNums;
		geoData = ptrCol.getGeometryData();
		geoEdge = geoData->getEdge(this->edge);
		geoEdge->getVerts(vertNums);
		line->GetPointIds()->SetNumberOfIds(2);
		line->GetPointIds()->SetId(0, vertNums[0]);
		line->GetPointIds()->SetId(1, vertNums[1]);
		
		cell = line;
#endif // USE_VTK

	}


} /* End Namespace */

instantiate(LinearLineElement)