#include <preprocessDefine.h>

#include <finiteElements/GenericFiniteElement.h>
#include <finiteElements/LinearLineElement.h>

#include <pointercollection/pointercollection.h>

#include <geometry/GenericGeometryElement.h>

#include <equations/GeometryData.h>

#include <control/OutputHandler.h>
#include <control/HandlingStructs.h>

#include <solver/GenericSolutionState.h>


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




} /* End Namespace */

instantiate(LinearLineElement)