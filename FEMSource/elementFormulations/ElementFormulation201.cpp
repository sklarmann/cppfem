/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#include <preprocessDefine.h>

#include <elementFormulations/ElementFormulation201.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>
#include <control/OutputHandler.h>
#include <control/HandlingStructs.h>

#include <equations/Nodetypes.h>
#include <equations/GenericNodes.h>
#include <equations/NodeSet.h>

#include <finiteElements/GenericFiniteElement.h>

#include <geometry/GenericGeometryElement.h>

#include <math/Userconstants.h>

#include <shapefunctions/GaussPoints.h>

#include <elementFormulations/GenericElementFormulation.h>


namespace FEMProject {


	template<typename prec, typename uint>
	ElementFormulation201<prec, uint>::ElementFormulation201(PointerCollection<prec, uint> *ptrCol) : GenericElementFormulation<prec,uint>(ptrCol) {

	}


	template<typename prec, typename uint>
	ElementFormulation201<prec, uint>::~ElementFormulation201() {

	}



	template<typename prec, typename uint>
	void ElementFormulation201<prec, uint>::readData(stringCommandHandler &Command, Userconstants<prec> *ucons) {
		std::string temp;
		temp = Command.getRhs("meshiddisp");
		this->meshIdDisp = static_cast<uint>(ucons->process(temp));

		temp = Command.getRhs("disporder");
		this->intOrderDisp = static_cast<uint>(ucons->process(temp));



		OutputHandler *Log;
		Log=&this->ptrCol->getInfoData()->Log;
		(*Log)(LogLevel::BasicLog, LogLevel::BasicLog) << "Element 201, specified Options" << std::endl
			<< "Mesh id for displacement nodes: " << this->meshIdDisp << std::endl
			<< "Shape function order for displacements: " << this->intOrderDisp << std::endl;
	}

	template<typename prec, typename uint>
	void ElementFormulation201<prec, uint>::setDegreesOfFreedom(GenericFiniteElement<prec, uint> *elem) {
		GenericGeometryElement<prec, uint> *geotemp;
		NodeSet<prec, uint>* nodeSetTemp;

		for (auto i = 0; i < 3; ++i) {
			geotemp = elem->getVertex(*this->ptrCol,i);
			uint setnum = 1;
			geotemp->setNumberOfNodeSets(*this->ptrCol, setnum);
			setnum = 0;
			nodeSetTemp = geotemp->getSet(*this->ptrCol, setnum);
			nodeSetTemp->setNumberOfNodes(1);
			nodeSetTemp->setType(NodeTypes::displacement);
			nodeSetTemp->setMeshId(this->meshIdDisp);


		}

		//for (auto i = 0; i < 3; ++i) {
		//	geotemp = elem->getEdge(*this->ptrCol, i);
		//	uint setnum = 1;
		//	geotemp->setNumberOfNodeSets(*this->ptrCol, setnum);
		//	setnum = 0;
		//	nodeSetTemp = geotemp->getSet(*this->ptrCol, setnum);
		//	nodeSetTemp->setNumberOfNodes(1);
		//	nodeSetTemp->setType(NodeTypes::displacement);
		//	nodeSetTemp->setMeshId(this->meshIdDisp);
		//}
		//
		//geotemp = elem->getFace(*this->ptrCol);
		//uint setnum = 1;
		//geotemp->setNumberOfNodeSets(*this->ptrCol, setnum);
		//setnum = 0;
		//nodeSetTemp = geotemp->getSet(*this->ptrCol, setnum);
		//nodeSetTemp->setNumberOfNodes(1);
		//nodeSetTemp->setType(NodeTypes::displacement);
		//nodeSetTemp->setMeshId(this->meshIdDisp);
	}


	template<typename prec, typename uint>
	void ElementFormulation201<prec, uint>::setTangentResidual(GenericFiniteElement<prec, uint> *elem
		, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
		, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {
		

		std::vector<prec> xsi, eta, weight;
		triangleGP(xsi, eta, weight, 2);
		
		Eigen::Matrix<prec, 2, Eigen::Dynamic> shapeDeriv;
		Eigen::Matrix<prec, 1, Eigen::Dynamic> shape;
		Eigen::Matrix<prec, 2, Eigen::Dynamic> coorDeriv;
		Eigen::Matrix<prec, 1, Eigen::Dynamic> coor;
		Eigen::Matrix<prec, 3, Eigen::Dynamic> Bmat;
		Eigen::Matrix<prec, 2, 2> jacobi;
		Eigen::Matrix<prec, 3, 3> material;
		std::vector<DegreeOfFreedom<prec, uint>*> dispDofs, tempDofs;
		std::vector<GenericNodes<prec, uint>*> dispNodes;
		
		
		elem->getNodesMeshId(*this->ptrCol,dispNodes, this->meshIdDisp);
		
		dispDofs.clear();
		for (auto i = 0; i < dispNodes.size(); ++i) {
			tempDofs.clear();
			dispNodes[i]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
			for (auto j = 0; j < tempDofs.size(); ++j) {
				dispDofs.push_back(tempDofs[j]);
			}
		}
		
		uint numDofs = static_cast<uint>(dispDofs.size());
		Dofs = dispDofs;
		
		stiffness.resize(numDofs, numDofs);
		stiffness.setZero();
		
		residual.resize(numDofs);
		residual.setZero();
		
		
		
		material.setZero();
		material(0, 0) = 1.0*10000;
		material(1, 1) = 1.0*10000;
		material(1, 0) = 0.0*10000;
		material(0, 1) = 0.0*10000;
		material(2, 2) = 0.5*10000;


		
		//std::cout << " test" << std::endl;
		
		uint nodesEdge1, nodesEdge2, nodesEdge3, nodesFace;
		
		elem->getNumberOfNodes(*this->ptrCol,nodesEdge1, nodesEdge2, nodesEdge3, nodesFace, this->meshIdDisp);
		prec da;
		da = 0;
		
		Bmat.resize(3, numDofs);
		Bmat.setZero();
		for (auto i = 0; i < xsi.size(); ++i) {
			elem->getAffineCoordinates(coor, coorDeriv, xsi[i], eta[i]);
			elem->getH1Shapes(*this->ptrCol, coor, coorDeriv, shape, shapeDeriv, nodesEdge1, nodesEdge2, nodesEdge3, nodesFace);
			elem->getJacobian(*this->ptrCol,jacobi, shapeDeriv);
			shapeDeriv = (jacobi.inverse()).transpose()*shapeDeriv;
			
			for (auto j = 0; j < numDofs/3; ++j) {
				Bmat(0, j * 3)     = shapeDeriv(0, j);
				Bmat(1, j * 3 + 1) = shapeDeriv(1, j);
				Bmat(2, j * 3)     = shapeDeriv(1, j)*0.5;
				Bmat(2, j * 3 + 1) = shapeDeriv(0, j)*0.5;
			}
		
			//
			//			shapeDeriv.transpose()*material*shapeDeriv;
		
			da = (jacobi.determinant())*weight[i];
			stiffness += Bmat.transpose()*material*Bmat*da;
		}

		//std::cout << "elmat \n";
		//std::cout << stiffness << std::endl;
		
		//Eigen::EigenSolver< Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> > eigs;
		//eigs.compute(stiffness);
		//
		//std::cout <<"Eigenvalues: \n" 
		//	<< eigs.eigenvalues() << std::endl;
		
		//std::cout << da << std::endl;
	}

}

instantiate(ElementFormulation201)
