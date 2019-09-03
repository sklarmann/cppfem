/*
 * GenericFiniteElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <equations/GeometryData.h>
#include <materials/Material.h>
#include <finiteElements/ElementTypes.h>
#include <equations/DofStatus.h>

#include <Eigen/Dense>

template <class bla>
class vtkSmartPointer;

template<typename prec,typename uint>
class PointerCollection;


class vtkCell;

namespace FEMProject {


	template <typename prec, typename uint>
	class PointerCollection;
	template <typename prec, typename uint>
	class Material;

	template<typename prec, typename uint>
	class GenericFiniteElement {
		typedef PointerCollection<prec, uint> ptrCol;
	public:
		GenericFiniteElement();
		virtual ~GenericFiniteElement();
		void setId(const uint &id){this->id = id;};
		void setMatrial(Material<prec,uint> *in){this->material=in;};
		//Material<prec,uint> *getMaterial() { return this->material; };
		
		void insertStiffnessResidual(Eigen::Matrix<prec,Eigen::Dynamic,Eigen::Dynamic> &stiffness
									,Eigen::Matrix<prec,1,Eigen::Dynamic> &residual
									,std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus);
	
		void GenericSetDegreesOfFreedom();
		void GenericSetTangentResidual(
			Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		void GenericSetMass(
			Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
	
		//TODO throw exception
		virtual void setVerts(std::vector<uint> &vertsIn){};
		virtual void setEdges(std::vector<uint> &edgesIn){};
		virtual void setFace(const uint &face) {};
		virtual Elementtypes getType() { return Elementtypes::Generic; };
		virtual GenericGeometryElement<prec, uint> *getVertex(ptrCol &pointers, const uint &num) { return 0; };
		virtual GenericGeometryElement<prec, uint> *getEdge(ptrCol &pointers, const uint &num) { return 0; };
		virtual GenericGeometryElement<prec, uint> *getFace(ptrCol &pointers) { return 0; };
		virtual void setStiffnessMatrix() {};
		virtual std::vector<uint> getVertexIds(){std::vector<uint> u;u.resize(0);return u;};
		virtual void getNumberOfNodes(ptrCol &pointers, uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId) {};
		virtual void getVertexFunctions(Eigen::Matrix<prec, 1, Eigen::Dynamic> &shape
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &shapeDerivative
			, const prec &xsi, const prec &eta) {};
	
		virtual void getNodesMeshId(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &Nodes, uint &meshId) {};
	
		virtual void getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, const prec &xsi, const prec &eta) {};
	
		virtual void getH1Shapes(ptrCol &pointers
			, Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
			, Eigen::Matrix<prec, 1, Eigen::Dynamic> &shape
			, Eigen::Matrix<prec, 2, Eigen::Dynamic> &shapeDerivative
			, const uint &numEdge1, const uint &numEdge2, const uint &numEdge3, const uint &numFace) {};
	
		virtual void getJacobian(ptrCol &pointers, Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDeriv) {};
		
		virtual void setUpSparseMatrix(ptrCol &pointers) {};
	
		virtual void getVtkCell(PointerCollection<prec,uint> &ptrCol, vtkSmartPointer<vtkCell> &cell) {  };
	
	protected:
		uint id;
		Material<prec,uint> *material;
	};

	

} /* namespace FEMProject */
