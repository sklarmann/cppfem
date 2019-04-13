/*
 * LinearTriangleElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>
#include <preprocessDefine.h>

#include <finiteElements/GenericFiniteElement.h>

#include <Eigen/Dense>

template <class bla>
class vtkSmartPointer;

template<typename prec, typename uint>
class PointerCollection;

class vtkCell;

namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;


	template <typename prec, typename uint>
	class GenericGeometryElement;

	template <typename prec, typename uint>
	class GenericFiniteElement;

	

	template<typename prec, typename uint>
	class LinearTriangleElement : public GenericFiniteElement<prec,uint> {
		typedef PointerCollection<prec,uint> ptrCol;
	public:
		LinearTriangleElement(PointerCollection<prec,uint> *pointers);
		~LinearTriangleElement();
		void setVerts(std::vector<uint> &vertsIn);
		void setEdges(std::vector<uint> &edgesIn);
		void setFace(const uint &face);
		Elementtypes getType(){return Elementtypes::LinearTriangle;};
		std::vector<uint> getVertexIds();
		GenericGeometryElement<prec, uint> *getVertex(ptrCol &pointers, const uint &num);
		GenericGeometryElement<prec, uint> *getEdge(ptrCol &pointers, const uint &num);
		GenericGeometryElement<prec, uint> *getFace(ptrCol &pointers);
		void getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, const prec &xsi, const prec &eta);
	
	
		void getNodesMeshId(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &Nodes, uint &meshId);
	
		void getH1Shapes(ptrCol &pointers
			, Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, Eigen::Matrix<prec,1,Eigen::Dynamic> &shape
			, Eigen::Matrix<prec,2,Eigen::Dynamic> &shapeDerivative
			, const uint &numEdge1, const uint &numEdge2, const uint &numEdge3, const uint &numFace);
		void getJacobian(ptrCol &pointers, Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDeriv);
		void getNumberOfNodes(ptrCol &pointers, uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId);
		void setUpSparseMatrix(ptrCol &pointers);


		void getVtkCell(PointerCollection<prec, uint> &ptrCol, vtkSmartPointer<vtkCell> &cell);
	private:
		uint verts[3];
		uint edges[3];
		uint face;
	};
	
	



} /* namespace FEMProject */

