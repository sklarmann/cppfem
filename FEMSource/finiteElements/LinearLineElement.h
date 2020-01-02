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
	class LinearLineElement : public GenericFiniteElement<prec,uint> {
		typedef PointerCollection<prec,uint> ptrCol;
	public:
		LinearLineElement(PointerCollection<prec,uint> *pointers);
		~LinearLineElement();
		void setVerts(std::vector<uint> &vertsIn);
		void setEdges(std::vector<uint> &edgesIn);
		Elementtypes getType(){return Elementtypes::LinearLine;};
		uint getVertexId(ptrCol& pointers, uint num);
		//std::vector<uint> getVertexIds();
		GenericGeometryElement<prec, uint> *getVertex(ptrCol &pointers, const uint &num);
		//GenericGeometryElement<prec, uint> *getEdge(ptrCol &pointers, const uint &num);
		//GenericGeometryElement<prec, uint> *getFace(ptrCol &pointers);
		//void getAffineCoordinates(Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
		//	, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
		//	, const prec &xsi, const prec &eta);
	
	
		//void getNodesMeshId(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &Nodes, uint &meshId);
	
		//void getH1Shapes(ptrCol &pointers
		//	, Eigen::Matrix<prec, 1, Eigen::Dynamic> &coor
		//	, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDerivative
		//	, Eigen::Matrix<prec,1,Eigen::Dynamic> &shape
		//	, Eigen::Matrix<prec,2,Eigen::Dynamic> &shapeDerivative
		//	, const uint &numEdge1, const uint &numEdge2, const uint &numEdge3, const uint &numFace);
		//void getJacobian(ptrCol &pointers, Eigen::Matrix<prec, 2, 2> &jacobi, Eigen::Matrix<prec, 2, Eigen::Dynamic> &coorDeriv);
		//void getNumberOfNodes(ptrCol &pointers, uint &numEdge1, uint &numEdge2, uint &numEdge3, uint &numFace, const unsigned char &meshId);
		void setUpSparseMatrix(ptrCol &pointers);


		void getVtkCell(PointerCollection<prec, uint> &ptrCol, vtkSmartPointer<vtkCell> &cell);
		//void getElementsLocalNodalReactions(PointerCollection<prec, uint>& ptrCol, std::map<uint, std::vector<prec>>& vReacs);
	private:
		uint verts[2];
		uint edge;
	};

} /* namespace FEMProject */

