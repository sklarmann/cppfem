/*
 * LinearTriangleElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <finiteElements/QuadrilateralNodal.h>

#include <pointercollection/pointercollection.h>

#include <shapefunctions/KernelShape.h>


namespace FEMProject {
	
	template<typename prec, typename uint>
	QuadrilateralNodal<prec,uint>::QuadrilateralNodal() : GenericFiniteElement<prec,uint>(){
	
	}
	
	template<typename prec, typename uint>
	QuadrilateralNodal<prec,uint>::~QuadrilateralNodal(){
	
	}
	
	template<typename prec, typename uint>
	void QuadrilateralNodal<prec,uint>::setVerts(const uint &vert1,const uint &vert2, const uint &vert3){
		this->verts[0] = vert1;
		this->verts[1] = vert2;
		this->verts[2] = vert3;
	}
	
	template<typename prec, typename uint>
	void QuadrilateralNodal<prec,uint>::setEdges(const uint &edge1,const uint &edge2, const uint &edge3){
		this->edges[0] = edge1;
		this->edges[1] = edge2;
		this->edges[2] = edge3;
	}
	
	template<typename prec,typename uint>
	void QuadrilateralNodal<prec, uint>::setFace(const uint &face) {
		this->face = face;
	}
	
	template<typename prec, typename uint>
	std::vector<uint> QuadrilateralNodal<prec,uint>::getVertexIds(){
		std::vector<uint> u;
		u.resize(3);
		u[0] = this->verts[0];
		u[1] = this->verts[1];
		u[2] = this->verts[2];
		return u;
	}
	
	
	template<typename prec,typename uint>
	GenericGeometryElement<prec, uint> *QuadrilateralNodal<prec, uint>::getVertex(const unsigned char &num) {
		if (num > 2) {
			//TODO throw exception
		}
		
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *temp;
		temp = ptrCol->getGeometryData();
		return temp->getVertex(this->verts[num]);
	}
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec, uint> *QuadrilateralNodal<prec, uint>::getEdge(const unsigned char &num) {
		if (num > 2) {
			//TODO throw exception
		}
	
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *temp = ptrCol->getGeometryData();
		return temp->getEdge(this->edges[num]);
	}
	
	template <typename prec, typename uint>
	GenericGeometryElement<prec, uint> *QuadrilateralNodal<prec, uint>::getFace() {
	
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *temp = ptrCol->getGeometryData();
		return temp->getFace(this->face);
	
	}
	
	
	template<typename prec, typename uint>
	void QuadrilateralNodal<prec, uint>::getNumberOfNodes(uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId) {
		numEdge1 = 0;
		numEdge2 = 0;
		numEdge3 = 0;
		numFace  = 0;
		
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *geoData = ptrCol->getGeometryData();
	
		GenericGeometryElement<prec, uint> *geoElem;
	
		NodeSet<prec, uint> *tempSet;
		geoElem = geoData->getEdge(this->edges[0]);
		if (geoElem->checkSetWithMeshId(meshId)) {
			tempSet = geoElem->getSetMeshId(meshId);
			numEdge1 = tempSet->getNumberOfNodes();
		}
	
	
		geoElem = geoData->getEdge(this->edges[1]);
		if (geoElem->checkSetWithMeshId(meshId)) {
			tempSet = geoElem->getSetMeshId(meshId);
			numEdge2 = tempSet->getNumberOfNodes();
		}
	
		geoElem = geoData->getEdge(this->edges[2]);
		if (geoElem->checkSetWithMeshId(meshId)) {
			tempSet = geoElem->getSetMeshId(meshId);
			numEdge3 = tempSet->getNumberOfNodes();
		}
	
		geoElem = geoData->getFace(this->face);
		if (geoElem->checkSetWithMeshId(meshId)) {
			tempSet = geoElem->getSetMeshId(meshId);
			numFace = tempSet->getNumberOfNodes();
		}
	
	}
	
	template <typename prec, typename uint>
	void QuadrilateralNodal<prec, uint>::getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
		, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
		, const prec &xsi, const prec &eta) {
	
		coor.resize(3);
	
		coor(0) = (eta + 1.0) / 2.0;
		coor(1) = -(xsi + eta) / 2.0;
		coor(2) = (xsi + 1.0) / 2.0;
	
		coorDerivative.resize(2, 3);
	
		coorDerivative(0, 0) = 0.0;
		coorDerivative(0, 1) = -1.0 / 2.0;
		coorDerivative(0, 2) = 1.0 / 2.0;
	
		coorDerivative(1, 0) = 1.0 / 2.0;
		coorDerivative(1, 1) = -1.0 / 2.0;
		coorDerivative(1, 2) = 0.0;
	}
	
	template<typename prec, typename uint>
	void QuadrilateralNodal<prec, uint>::getH1Shapes(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
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
	
		shapeDerivative(0, 0) = coorDerivative(0, 0);
		shapeDerivative(0, 1) = coorDerivative(0, 1);
		shapeDerivative(0, 2) = coorDerivative(0, 2);
	
		shapeDerivative(1, 0) = coorDerivative(1, 0);
		shapeDerivative(1, 1) = coorDerivative(1, 1);
		shapeDerivative(1, 2) = coorDerivative(1, 2);
	
	
		uint shapePos = 3;
		prec tshp, tdshp;
	
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *tempGeoData = ptrCol->getGeometryData();
	
		GenericGeometryElement<prec, uint> *tempGeo;
	
		tempGeo = tempGeoData->getEdge(this->edges[0]);
		std::vector<uint> edgeVerts;
		edgeVerts = tempGeo->getEdgeVerts();
	
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
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag,i+2);
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
		edgeVerts = tempGeo->getEdgeVerts();
	
		if (this->verts[1] == edgeVerts[0]) {
			flag = 1.0;
		}
		else {
			flag = -1.0;
		}
	
	
	
		l1 = 2;
		l2 = 0;
		for (uint i = 0; i < numEdge2; ++i) {
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag, i + 2);
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
		edgeVerts = tempGeo->getEdgeVerts();
	
		if (this->verts[2] == edgeVerts[0]) {
			flag = 1.0;
		}
		else {
			flag = -1.0;
		}
	
		l1 = 0;
		l2 = 1;
		for (uint i = 0; i < numEdge3; ++i) {
			KernelShapes(tshp, tdshp, (coor(l2) - coor(l1))*flag, i + 2);
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
	
		//Face
		prec tshp2, tdshp2;
		uint loop;
		loop = static_cast<uint>(std::sqrt(numFace));
		for (uint i = 0; i < loop; ++i) {
			for (uint j = 0; j < loop; ++j) {
				KernelShapes(tshp, tdshp, coor(2) - coor(1), i);
				KernelShapes(tshp2, tdshp2, coor(1) - coor(0), j);
	
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
			}
		}
	
	}
	
	template<typename prec, typename uint>
	void QuadrilateralNodal<prec, uint>::getJacobian(Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec,2,Eigen::Dynamic> &coorDeriv) {
		
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *tempGeoData = ptrCol->getGeometryData();
		
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
	void QuadrilateralNodal<prec, uint>::setUpSparseMatrix() {
		PointerCollection<prec, uint> *ptrCol = static_cast<PointerCollection<prec, uint>*> (this->pointers);
		GeometryData<prec, uint> *tempGeoData = ptrCol->getGeometryData();
	
		PointerCollection<prec, uint> *temp = static_cast<PointerCollection<prec, uint>*>(this->pointers);
		GenericGeometryElement<prec, uint> *tempGeo;
	
		std::vector<uint> eqIds, tempIds;
		std::vector<dofStatus> eqStatus, tempStatus;
	
		for (auto k = 0; k < 3; ++k) {
			tempGeo = tempGeoData->getVertex(this->verts[k]);
			tempGeo->getAllEquationsIds(tempIds, tempStatus);
			for (auto i = 0; i < tempIds.size(); ++i) {
				eqIds.push_back(tempIds[i]);
				eqStatus.push_back(tempStatus[i]);
			}
		}
	
	
		for (auto k = 0; k < 3; ++k) {
			tempGeo = tempGeoData->getEdge(this->edges[k]);
			tempGeo->getAllEquationsIds(tempIds, tempStatus);
			for (auto i = 0; i < tempIds.size(); ++i) {
				eqIds.push_back(tempIds[i]);
				eqStatus.push_back(tempStatus[i]);
			}
		}
		
	
		tempGeo = tempGeoData->getFace(this->face);
		tempGeo->getAllEquationsIds(tempIds, tempStatus);
		for (auto i = 0; i < tempIds.size(); ++i) {
			eqIds.push_back(tempIds[i]);
			eqStatus.push_back(tempStatus[i]);
		}
	
		
		Solutionstate<prec, uint> *tsol;
		tsol = ptrCol->getSolutionState();
		tsol->setTripletList(eqIds, eqStatus);
	}

} /* namespace FEMProject */

instantiate(QuadrilateralNodal)