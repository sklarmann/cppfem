/*
 * Element201.hpp
 *
 *  Created on: 17.08.2016
 *      Author: Klarmann
 */

#ifndef ELEMENT201_HPP_
#define ELEMENT201_HPP_

#include <ElementControl.hpp>
#include <GenericGeometryElement.h>
#include <GenericFiniteElement.h>
#include <NodeTypes.h>
#include <DofStatus.hpp>
#include <GaussPoints.hpp>
#include <Eigen/Dense>
#include <iomanip>



namespace FEMProject {




	template <typename prec, typename uint>
	void element201(GenericFiniteElement<prec, uint> &element, const ControlOptions &Control) {

		switch (Control) {
		case ControlOptions::SetDegreesOfFreedom:
		{
			GenericGeometryElement<prec, uint> *geotemp;
			NodeSet<prec, uint>* nodeSetTemp;

			for (auto i = 0; i < 3; ++i) {
				geotemp = element.getVertex(i);
				geotemp->setNumberOfNodeSets(1);
				nodeSetTemp = geotemp->getSet(0);
				nodeSetTemp->setNumberOfNodes(1);
				nodeSetTemp->setType(NodeTypes::displacement);
				nodeSetTemp->setMeshId(0);
				nodeSetTemp->setDofsPerNode(2);


			}

			//for (auto i = 0; i < 3; ++i) {
			//	geotemp = element.getEdge(i);
			//	geotemp->setNumberOfNodeSets(1);
			//	nodeSetTemp = geotemp->getSet(0);
			//	nodeSetTemp->setNumberOfNodes(1);
			//	nodeSetTemp->setType(NodeTypes::displacement);
			//	nodeSetTemp->setMeshId(0);
			//
			//
			//}
			//
			//geotemp = element.getFace();
			//geotemp->setNumberOfNodeSets(1);
			//nodeSetTemp = geotemp->getSet(0);
			//nodeSetTemp->setNumberOfNodes(4);
			//nodeSetTemp->setType(NodeTypes::displacement);
			//nodeSetTemp->setMeshId(0);

		}
		break;
		case ControlOptions::CheckData:
			GenericGeometryElement<prec, uint> *verttemp;
			NodeSet<prec, uint>* nodeSetTemp;

			for (auto i = 0; i < 3; ++i) {
				verttemp = element.getVertex(i);
				nodeSetTemp = verttemp->getSet(0);

				if (nodeSetTemp->getMeshId() != 0) {
					//TODO throw exception
					std::cout << "mesh id does not match" << std::endl;
				}
				if (nodeSetTemp->getNodeSetType() != NodeTypes::displacement) {
					//TODO throw exception
					std::cout << "Nodetype does not match" << std::endl;
				}
				if (nodeSetTemp->getNumberOfNodes() != 1) {
					//TODO throw exception
					std::cout << "Number of nodes does not match" << std::endl;
				}
			}


			//for (auto i = 0; i < 3; ++i) {
			//	verttemp = element.getVertex(i);
			//	std::vector<uint> eqIds;
			//	std::vector<dofStatus> eqStatus;
			//	verttemp->getEquationsIds(eqIds, eqStatus, 0);
			//
			//	std::cout << "Vertex: " << verttemp->getId() << "Equation ids: ";
			//
			//	for (auto i = 0; i < eqIds.size(); ++i) {
			//		std::cout << eqIds[i] << " ";
			//	}
			//	std::cout << std::endl;
			//}
			//
			//for (auto i = 0; i < 3; ++i) {
			//	verttemp = element.getEdge(i);
			//	std::vector<uint> eqIds;
			//	std::vector<dofStatus> eqStatus;
			//	verttemp->getEquationsIds(eqIds, eqStatus, 0);
			//
			//	std::cout << "Edge: " << verttemp->getId() << "Equation ids: ";
			//
			//	for (auto i = 0; i < eqIds.size(); ++i) {
			//		std::cout << eqIds[i] << " ";
			//	}
			//	std::cout << std::endl;
			//}
			//{
			//	verttemp = element.getFace();
			//	std::vector<uint> eqIds;
			//	std::vector<dofStatus> eqStatus;
			//	verttemp->getEquationsIds(eqIds, eqStatus, 0);
			//
			//	std::cout << "Face: " << verttemp->getId() << " Equation ids: ";
			//	for (auto i = 0; i < eqIds.size(); ++i) {
			//		std::cout << eqIds[i] << " ";
			//	}
			//	std::cout << std::endl;
			//}




			break;

		case ControlOptions::BuildStiffnessResidual:

			setStiffRes201<prec, uint>(element);

			break;
		}
	}



	template<typename prec, typename uint>
	void setStiffRes201(GenericFiniteElement<prec,uint> &element) {
		std::vector<prec> xsi, eta, weight;
		triangleGP(xsi, eta, weight, 2);

		Eigen::Matrix<prec, 2, Eigen::Dynamic> shapeDeriv;
		Eigen::Matrix<prec, 1, Eigen::Dynamic> shape;
		Eigen::Matrix<prec, 2, Eigen::Dynamic> coorDeriv;
		Eigen::Matrix<prec, 1, Eigen::Dynamic> coor;
		Eigen::Matrix<prec, 2, 2> jacobi;
		Eigen::Matrix<prec, 3, 3> material;

		material.setZero();
		material(0, 0) = 1.0;
		material(1, 1) = 1.0;
		material(1, 0) = 0.0;
		material(0, 1) = 0.0;
		material(2, 2) = 0.5;

		//std::cout << " test" << std::endl;

		uint nodesEdge1, nodesEdge2, nodesEdge3, nodesFace;

		element.getNumberOfNodes(nodesEdge1, nodesEdge2, nodesEdge3, nodesFace, 0);
		prec da;
		da = 0;

		for (auto i = 0; i < xsi.size(); ++i) {
			element.getAffineCoordinates(coor, coorDeriv, xsi[i], eta[i]);
			element.getH1Shapes(coor, coorDeriv, shape, shapeDeriv, nodesEdge1, nodesEdge2, nodesEdge3, nodesFace);
			element.getJacobian(jacobi, coorDeriv);
//			shapeDeriv = (jacobi.inverse()).transpose()*shapeDeriv;
//
//			shapeDeriv.transpose()*material*shapeDeriv;

			da += (jacobi.determinant())*weight[i];
		}
		std::cout << std::setprecision(16) << "Area: " << da << std::endl;
	}
	

}
	


#endif /* ELEMENT201_HPP_ */
