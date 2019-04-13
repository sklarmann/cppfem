/*
 * LinearTriangleElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */
#include <preprocessDefine.h>

#include <finiteElements/LinearTriangleElement.h>

#include <pointercollection/pointercollection.h>

#include <equations/GeometryData.h>
#include <equations/NodeSet.h>
#include <equations/EquationHandler.h>
#include <equations/DegreeOfFreedom.h>

#include <geometry/GenericGeometryElement.h>

#include <solver/GenericSolutionState.h>

#include <shapefunctions/KernelShape.h>

#include <Eigen/Dense>

#ifdef USE_VTK
	#include <vtkSmartPointer.h>
	#include <vtkCell.h>
	#include <vtkTriangle.h>
#endif // USE_VTK





namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	
	
	
	template<typename prec, typename uint>
	LinearTriangleElement<prec,uint>::LinearTriangleElement(PointerCollection<prec, uint> *pointers) : 
		GenericFiniteElement<prec,uint>(){
	
	}
	
	template<typename prec, typename uint>
	LinearTriangleElement<prec,uint>::~LinearTriangleElement(){
	
	}
	
	template<typename prec, typename uint>
	void LinearTriangleElement<prec,uint>::setVerts(std::vector<uint> &vertsIn) {
		this->verts[0] = vertsIn[0];
		this->verts[1] = vertsIn[1];
		this->verts[2] = vertsIn[2];
	}
	
	template<typename prec, typename uint>
	void LinearTriangleElement<prec,uint>::setEdges(std::vector<uint> &edgesIn){
		this->edges[0] = edgesIn[0];
		this->edges[1] = edgesIn[1];
		this->edges[2] = edgesIn[2];
	}
	
	template<typename prec,typename uint>
	void LinearTriangleElement<prec, uint>::setFace(const uint &face) {
		this->face = face;
	}
	
	template<typename prec, typename uint>
	std::vector<uint> LinearTriangleElement<prec,uint>::getVertexIds(){
		std::vector<uint> u;
		u.resize(3);
		u[0] = this->verts[0];
		u[1] = this->verts[1];
		u[2] = this->verts[2];
		return u;
	}
	
	
	template<typename prec,typename uint>
	GenericGeometryElement<prec, uint> *LinearTriangleElement<prec, uint>::getVertex(ptrCol &pointers, const uint &num) {
		if (num > 2) {
			//TODO throw exception
		}
		
		GeometryData<prec, uint> *temp;
		temp = pointers.getGeometryData();
		return temp->getVertex(this->verts[num]);
	}
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec, uint> *LinearTriangleElement<prec, uint>::getEdge(ptrCol &pointers, const uint &num) {
		if (num > 2) {
			//TODO throw exception
		}
	
		GeometryData<prec, uint> *temp = pointers.getGeometryData();
		return temp->getEdge(this->edges[num]);
	}
	
	template <typename prec, typename uint>
	GenericGeometryElement<prec, uint> *LinearTriangleElement<prec, uint>::getFace(ptrCol &pointers) {
	
		GeometryData<prec, uint> *temp = pointers.getGeometryData();
		return temp->getFace(this->face);
	
	}
	
	
	template<typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getNumberOfNodes(ptrCol &pointers, uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId) {
		numEdge1 = 0;
		numEdge2 = 0;
		numEdge3 = 0;
		numFace  = 0;
		
		GeometryData<prec, uint> *geoData = pointers.getGeometryData();
	
		GenericGeometryElement<prec, uint> *geoElem;
	
		NodeSet<prec, uint> *tempSet;
		geoElem = geoData->getEdge(this->edges[0]);
		if (geoElem->checkSetWithMeshId(pointers,meshId)) {
			tempSet = geoElem->getSetMeshId(pointers,meshId);
			numEdge1 = tempSet->getNumberOfNodes();
		}
	
	
		geoElem = geoData->getEdge(this->edges[1]);
		if (geoElem->checkSetWithMeshId(pointers,meshId)) {
			tempSet = geoElem->getSetMeshId(pointers, meshId);
			numEdge2 = tempSet->getNumberOfNodes();
		}
	
		geoElem = geoData->getEdge(this->edges[2]);
		if (geoElem->checkSetWithMeshId(pointers,meshId)) {
			tempSet = geoElem->getSetMeshId(pointers, meshId);
			numEdge3 = tempSet->getNumberOfNodes();
		}
	
		geoElem = geoData->getFace(this->face);
		if (geoElem->checkSetWithMeshId(pointers,meshId)) {
			tempSet = geoElem->getSetMeshId(pointers, meshId);
			numFace = tempSet->getNumberOfNodes();
		}
	
	}
	
	template <typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
		, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
		, const prec &xsi, const prec &eta) {
	
		coor.resize(3);
	
		coor(0) = (eta + (prec)1.0) / (prec)2.0;
		coor(1) = -(xsi + eta) / (prec)2.0;
		coor(2) = (xsi + (prec)1.0) / (prec)2.0;
	
		coorDerivative.resize(2, 3);
	
		coorDerivative(0, 0) = 0.0;
		coorDerivative(0, 1) = -1.0 / 2.0;
		coorDerivative(0, 2) = 1.0 / 2.0;
	
		coorDerivative(1, 0) = 1.0 / 2.0;
		coorDerivative(1, 1) = -1.0 / 2.0;
		coorDerivative(1, 2) = 0.0;
	}
	
	template<typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getH1Shapes(ptrCol &pointers
		, Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
		, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
		, Eigen::Matrix<prec, 1, Eigen::Dynamic> &shape
		, Eigen::Matrix<prec, 2, Eigen::Dynamic> &shapeDerivative
		, const uint &numEdge1, const uint &numEdge2, const uint &numEdge3, const uint &numFace) {
	
		uint sum = 3 + numEdge1 + numEdge2 + numEdge3 + numFace;
	
		shape.resize(sum);
		shapeDerivative.resize(2, sum);
	
		// Vertex shapes
		shape(0) = coor(1);
		shape(1) = coor(2);
		shape(2) = coor(0);
	
		shapeDerivative(0, 0) = coorDerivative(0, 1);
		shapeDerivative(0, 1) = coorDerivative(0, 2);
		shapeDerivative(0, 2) = coorDerivative(0, 0);
	
		shapeDerivative(1, 0) = coorDerivative(1, 1);
		shapeDerivative(1, 1) = coorDerivative(1, 2);
		shapeDerivative(1, 2) = coorDerivative(1, 0);
	
	
		uint shapePos = 3;
		prec tshp, tdshp;
	
		GeometryData<prec, uint> *tempGeoData = pointers.getGeometryData();
	
		GenericGeometryElement<prec, uint> *tempGeo;
	
		tempGeo = tempGeoData->getEdge(this->edges[0]);
		std::vector<uint> edgeVerts;
		tempGeo->getVerts(edgeVerts);
	
		prec flag;
		if (this->verts[0] == edgeVerts[0]) {
			flag = 1.0;
		}
		else {
			flag = -1.0;
		}
	
		//Edge1
		uint l1, l2;
		l1 = 1;
		l2 = 2;
		for (uint i = 0; i < numEdge1; ++i) {
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag,i);
			shape(shapePos) = coor(l1)*coor(l2)*tshp;
		
			uint deriv = 0;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			deriv = 1;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			++shapePos;
		}
	
		//Edge2
		tempGeo = tempGeoData->getEdge(this->edges[1]);
		tempGeo->getVerts(edgeVerts);
	
		if (this->verts[1] == edgeVerts[0]) {
			flag = 1.0;
		}
		else {
			flag = -1.0;
		}
	
	
	
		l1 = 2;
		l2 = 0;
		for (uint i = 0; i < numEdge2; ++i) {
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag, i);
			shape(shapePos) = coor(l1)*coor(l2)*tshp;
		
			uint deriv = 0;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			deriv = 1;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			++shapePos;
		}
	
		//Edge3
		tempGeo = tempGeoData->getEdge(this->edges[2]);
		tempGeo->getVerts(edgeVerts);
	
		if (this->verts[2] == edgeVerts[0]) {
			flag = 1.0;
		}
		else {
			flag = -1.0;
		}
	
		l1 = 0;
		l2 = 1;
		for (uint i = 0; i < numEdge3; ++i) {
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag, i);
			shape(shapePos) = coor(l1)*coor(l2)*tshp;
		
			uint deriv = 0;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			deriv = 1;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, l1)*coor(l2)*tshp
				+ coor(l1)*coorDerivative(deriv, l2)*tshp
				+ coor(l1)*coor(l2)*tdshp*(coorDerivative(deriv, l2) - coorDerivative(deriv, l1))*flag;
		
			++shapePos;
		}
	
		////Face
		//prec tshp2, tdshp2;
		//uint loop;
		//loop = static_cast<uint>(std::sqrt(numFace));
		//for (uint i = 0; i < loop; ++i) {
		//	for (uint j = 0; j < loop; ++j) {
		//		KernelShapes(tshp, tdshp, coor(2) - coor(1), i);
		//		KernelShapes(tshp2, tdshp2, coor(1) - coor(0), j);
		//
		//		shape(shapePos) = coor(0)*coor(1)*coor(2)*tshp*tshp2;
		//		uint deriv;
		//		deriv = 0;
		//		shapeDerivative(deriv, shapePos) = coorDerivative(deriv, 0)*coor(1)*coor(2)*tshp*tshp2
		//			+ coorDerivative(deriv, 1)*coor(0)*coor(2)*tshp*tshp2
		//			+ coorDerivative(deriv, 2)*coor(1)*coor(0)*tshp*tshp2
		//			+ coor(0)*coor(1)*coor(2)*tdshp*(coorDerivative(deriv, 2) - coorDerivative(deriv, 1))*tshp2
		//			+ coor(0)*coor(1)*coor(2)*tdshp2*(coorDerivative(deriv, 1) - coorDerivative(deriv, 0))*tshp;
		//
		//		deriv = 1;
		//		shapeDerivative(deriv, shapePos) = coorDerivative(deriv, 0)*coor(1)*coor(2)*tshp*tshp2
		//			+ coorDerivative(deriv, 1)*coor(0)*coor(2)*tshp*tshp2
		//			+ coorDerivative(deriv, 2)*coor(1)*coor(0)*tshp*tshp2
		//			+ coor(0)*coor(1)*coor(2)*tdshp*(coorDerivative(deriv, 2) - coorDerivative(deriv, 1))*tshp2
		//			+ coor(0)*coor(1)*coor(2)*tdshp2*(coorDerivative(deriv, 1) - coorDerivative(deriv, 0))*tshp;
		//
		//		++shapePos;
		//	}
		//}

		prec tshp2, tdshp2;
		uint n1=1, n2=1;
		uint order;
		if (numFace == 1) {
			order = 3;
		}
		else if(numFace == 3) {
			order = 4;
		}
		for (uint i = 0; i < numFace; ++i) {
			KernelShapes(tshp, tdshp, coor(2) - coor(1), n1-1);
			KernelShapes(tshp2, tdshp2, coor(1) - coor(0), n2-1);

			shape(shapePos) = coor(0)*coor(1)*coor(2)*tshp*tshp2;
			uint deriv;
			deriv = 0;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, 0)*coor(1)*coor(2)*tshp*tshp2
				+ coorDerivative(deriv, 1)*coor(0)*coor(2)*tshp*tshp2
				+ coorDerivative(deriv, 2)*coor(1)*coor(0)*tshp*tshp2
				+ coor(0)*coor(1)*coor(2)*tdshp*(coorDerivative(deriv, 2) - coorDerivative(deriv, 1))*tshp2
				+ coor(0)*coor(1)*coor(2)*tdshp2*(coorDerivative(deriv, 1) - coorDerivative(deriv, 0))*tshp;

			deriv = 1;
			shapeDerivative(deriv, shapePos) = coorDerivative(deriv, 0)*coor(1)*coor(2)*tshp*tshp2
				+ coorDerivative(deriv, 1)*coor(0)*coor(2)*tshp*tshp2
				+ coorDerivative(deriv, 2)*coor(1)*coor(0)*tshp*tshp2
				+ coor(0)*coor(1)*coor(2)*tdshp*(coorDerivative(deriv, 2) - coorDerivative(deriv, 1))*tshp2
				+ coor(0)*coor(1)*coor(2)*tdshp2*(coorDerivative(deriv, 1) - coorDerivative(deriv, 0))*tshp;

			++shapePos;
			++n1;
			if (n1 + n2 > order-1) {
				n1 = 1;
				++n2;
			}

		}
	
	}
	
	template<typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getJacobian(ptrCol &pointers, Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec,2,Eigen::Dynamic> &coorDeriv) {
		
		GeometryData<prec, uint> *tempGeoData = pointers.getGeometryData();
		
		GenericGeometryElement<prec, uint> *tempGeo;
	
	
		jacobi.setZero();
		for (auto k = 0; k < 3; ++k) {
			tempGeo = tempGeoData->getVertex(this->verts[k]);
	
			std::vector<prec> coords;
			coords = tempGeo->getCoordinates();
	
			jacobi(0, 0) += coorDeriv(0, k)*coords[0];
			jacobi(0, 1) += coorDeriv(1, k)*coords[0];
			jacobi(1, 0) += coorDeriv(0, k)*coords[1];
			jacobi(1, 1) += coorDeriv(1, k)*coords[1];
		}
	
	}
	
	
	template <typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::setUpSparseMatrix(ptrCol &pointers) {
		GeometryData<prec, uint> *tempGeoData = pointers.getGeometryData();
	
		GenericGeometryElement<prec, uint> *tempGeo;
	
		std::vector<DegreeOfFreedom<prec, uint>*> tempDofs, Dofs;
		
	
		for (auto k = 0; k < 3; ++k) {
			tempGeo = tempGeoData->getVertex(this->verts[k]);
			tempGeo->getAllEquationsIds(pointers, tempDofs);
			for (auto i = 0; i < tempDofs.size(); ++i) {
				Dofs.push_back(tempDofs[i]);
			}
		}
	
	
		for (auto k = 0; k < 3; ++k) {
			tempGeo = tempGeoData->getEdge(this->edges[k]);
			tempGeo->getAllEquationsIds(pointers, tempDofs);
			for (auto i = 0; i < tempDofs.size(); ++i) {
				Dofs.push_back(tempDofs[i]);
			}
		}
		
	
		tempGeo = tempGeoData->getFace(this->face);
		tempGeo->getAllEquationsIds(pointers, tempDofs);
		for (auto i = 0; i < tempDofs.size(); ++i) {
			Dofs.push_back(tempDofs[i]);
		}
	
	
		
		GenericSolutionState<prec, uint> *tsol;
		tsol = pointers.getSolutionState();
		tsol->setTripletList(Dofs);
	}

	template<typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getNodesMeshId(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &Nodes, uint &meshId) {
		Nodes.clear();
		GeometryData<prec, uint> *tempGeoData = pointers.getGeometryData();
		GenericGeometryElement<prec, uint> *tempGeo;
		NodeSet<prec, uint> *NodeSet;

		std::vector<GenericNodes<prec, uint>*> Nodestemp;
		
		for (auto i = 0; i < 3; ++i) {
			tempGeo=tempGeoData->getVertex(this->verts[i]);
			NodeSet = tempGeo->getSetMeshId(pointers,meshId);
			pointers.getEquationHandler()->getNodes(Nodestemp, *NodeSet);
			for (auto j = 0; j < Nodestemp.size(); ++j) {
				Nodes.push_back(Nodestemp[j]);
			}
		}

		for (auto i = 0; i < 3; ++i) {
			tempGeo = tempGeoData->getEdge(this->edges[i]);
			NodeSet = tempGeo->getSetMeshId(pointers, meshId);
			if (NodeSet != 0) {
				pointers.getEquationHandler()->getNodes(Nodestemp, *NodeSet);
				for (auto j = 0; j < Nodestemp.size(); ++j) {
					Nodes.push_back(Nodestemp[j]);
				}
			}
		}

		tempGeo = tempGeoData->getFace(this->face);
		NodeSet = tempGeo->getSetMeshId(pointers, meshId);
		if (NodeSet != 0) {
			pointers.getEquationHandler()->getNodes(Nodestemp, *NodeSet);
			for (auto j = 0; j < Nodestemp.size(); ++j) {
				Nodes.push_back(Nodestemp[j]);
			}
		}
	}


	template<typename prec, typename uint>
	void LinearTriangleElement<prec, uint>::getVtkCell(PointerCollection<prec, uint> &ptrCol, vtkSmartPointer<vtkCell> &cell)
	{
#ifdef USE_VTK
		vtkSmartPointer<vtkCell> triangle =
			vtkSmartPointer<vtkTriangle>::New();
		triangle->GetPointIds()->SetId(0, this->verts[0]);
		triangle->GetPointIds()->SetId(1, this->verts[1]);
		triangle->GetPointIds()->SetId(2, this->verts[2]);

		cell = triangle;
#endif // USE_VTK

	}




} /* namespace FEMProject */


instantiate(LinearTriangleElement)
