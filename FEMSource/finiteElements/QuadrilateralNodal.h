/*
 * LinearTriangleElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <finiteElements/GenericFiniteElement.h>

namespace FEMProject {


	template<typename prec, typename uint>
	class QuadrilateralNodal : public GenericFiniteElement<prec,uint> {
	public:
		QuadrilateralNodal();
		~QuadrilateralNodal();
		void setVerts(const uint &vert1,const uint &vert2, const uint &vert3);
		void setEdges(const uint &edge1,const uint &edge2, const uint &edge3);
		void setFace(const uint &face);
		Elementtypes getType(){return Elementtypes::LinearTriangle;};
		std::vector<uint> getVertexIds();
		GenericGeometryElement<prec, uint> *getVertex(const unsigned char &num);
		GenericGeometryElement<prec, uint> *getEdge(const unsigned char &num);
		GenericGeometryElement<prec, uint> *getFace();
		void getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, const prec &xsi, const prec &eta);
	
		void getH1Shapes(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, Eigen::Matrix<prec,1,Eigen::Dynamic> &shape
			, Eigen::Matrix<prec,2,Eigen::Dynamic> &shapeDerivative
			, const uint &numEdge1, const uint &numEdge2, const uint &numEdge3, const uint &numFace);
		void getJacobian(Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDeriv);
		void getNumberOfNodes(uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId);
		void setUpSparseMatrix();
	private:
		uint verts[4];
		uint edges[4];
		uint face;
	};

} /* namespace FEMProject */

