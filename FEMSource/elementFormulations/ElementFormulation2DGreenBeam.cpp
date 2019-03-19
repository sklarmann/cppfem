#include <preprocessDefine.h>

#include <control/stringCommandHandler.h>

#include <elementFormulations/GenericElementFormulation.h>
#include <elementFormulations/ElementFormulation2DGreenBeam.h>

#include <finiteElements/GenericFiniteElement.h>

#include <geometry/GenericGeometryElement.h>

#include <equations/NodeSet.h>
#include <equations/Nodetypes.h>
#include <equations/GenericNodes.h>
#include <equations/EquationHandler.h>

#include <math/Userconstants.h>

#include <pointercollection/pointercollection.h>

namespace FEMProject {

	template<typename prec, typename uint>
	ElementFormulation2DGreenBeam<prec, uint>::ElementFormulation2DGreenBeam(PointerCollection<prec, uint>* ptrCol) :
		GenericElementFormulation<prec, uint>(ptrCol)
	{
	}
	template<typename prec, typename uint>
	ElementFormulation2DGreenBeam<prec, uint>::~ElementFormulation2DGreenBeam()
	{
	}
	template<typename prec, typename uint>
	void ElementFormulation2DGreenBeam<prec, uint>::readData(stringCommandHandler & Command, Userconstants<prec>* ucons)
	{
		std::string temp;
		temp = Command.getRhs("meshiddisp");
		this->meshIdDisp = static_cast<uint>(ucons->process(temp));
		temp = Command.getRhs("ea");
		this->EA = static_cast<uint>(ucons->process(temp));
		temp = Command.getRhs("ei");
		this->EI = static_cast<uint>(ucons->process(temp));
	}
	template<typename prec, typename uint>
	void ElementFormulation2DGreenBeam<prec, uint>::setDegreesOfFreedom(GenericFiniteElement<prec, uint>* elem)
	{
		GenericGeometryElement<prec, uint> *geoTemp;
		NodeSet<prec, uint> *tempSet;
		for (auto i = 0; i < 2; ++i) {
			geoTemp = elem->getVertex(*this->ptrCol, i);
			uint nsets = 1;
			geoTemp->setNumberOfNodeSets(*this->ptrCol, nsets);
			nsets = 0;
			tempSet = geoTemp->getSet(*this->ptrCol, nsets);
			tempSet->setNumberOfNodes(1);
			tempSet->setType(NodeTypes::displacement);
			tempSet->setMeshId(this->meshIdDisp);

		}
	}
	template<typename prec, typename uint>
	void ElementFormulation2DGreenBeam<prec, uint>::setTangentResidual(GenericFiniteElement<prec, uint>* elem, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
	{
		GenericGeometryElement<prec, uint> *edge, *vert1, *vert2;
		GeometryData<prec, uint> *geodata;
		EquationHandler<prec, uint> *eqHandler;
		eqHandler = this->ptrCol->getEquationHandler();
		NodeSet<prec, uint> *set1, *set2;
		uint dummy = 0;
		vert1 = elem->getVertex(*this->ptrCol, 0);
		vert2 = elem->getVertex(*this->ptrCol, 1);
		set1 = vert1->getSetMeshId(*this->ptrCol, this->meshIdDisp);
		set2 = vert2->getSetMeshId(*this->ptrCol, this->meshIdDisp);
		GenericNodes<prec, uint> *node1, *node2;
		std::vector<GenericNodes<prec, uint>*> temp, Nodes;
		eqHandler->getNodes(temp, *set1);
		Nodes.push_back(temp[0]);
		temp.clear();
		eqHandler->getNodes(temp, *set2);
		set2->getNodes(temp);
		Nodes.push_back(temp[0]);

		std::vector<DegreeOfFreedom<prec, uint>*> tempDofs;
		Nodes[0]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
		for (auto i = 0; i < 3; ++i) {
			Dofs.push_back(tempDofs[i]);
		}
		Nodes[1]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
		for (auto i = 0; i < 3; ++i) {
			Dofs.push_back(tempDofs[i]);
		}

		std::vector<prec> coor1, coor2;
		coor1 = vert1->getCoordinates();
		coor2 = vert2->getCoordinates();
		prec length = (prec)0, tempDiff;
		for (auto i = 0; i < 3; ++i) {
			tempDiff = (coor1[i] - coor2[i]);
			length += tempDiff * tempDiff;
		}
		length = sqrt(length);

		prec xi, w;
		std::vector<prec> gp, weight;

		Eigen::Matrix<prec, 2, Eigen::Dynamic> shapeDeriv;

		Eigen::Matrix<prec, 2, Eigen::Dynamic> Bmat;

		stiffness.resize(6, 6);
		residual.resize(6);
		residual.setZero();

		stiffness.setZero();

		stiffness(0, 0) = this->EA / length;
		stiffness(0, 3) = -this->EA / length;
		

		stiffness(1, 1) = this->EI / length / length / length * (prec)12;
		stiffness(1, 2) = this->EI / length / length * (prec)6;
		stiffness(1, 4) = -this->EI / length / length / length * (prec)12;
		stiffness(1, 5) = this->EI / length / length * (prec)6;

		stiffness(2, 1) = this->EI / length / length * (prec)6;
		stiffness(2, 2) = this->EI / length * (prec)4;
		stiffness(2, 4) = -this->EI / length / length * (prec)6;
		stiffness(2, 5) = this->EI / length * (prec)2;

		stiffness(3, 0) = -this->EA / length;
		stiffness(3, 3) = this->EA / length;


		stiffness(4, 1) = -this->EI / length / length / length * (prec)12;
		stiffness(4, 2) = -this->EI / length / length * (prec)6;
		stiffness(4, 4) = this->EI / length / length / length * (prec)12;
		stiffness(4, 5) = -this->EI / length / length * (prec)6;

		stiffness(5, 1) = this->EI / length / length * (prec)6;
		stiffness(5, 2) = this->EI / length * (prec)2;
		stiffness(5, 4) = -this->EI / length / length * (prec)6;
		stiffness(5, 5) = this->EI / length * (prec)4;


	}
} // End Namespace

instantiate(ElementFormulation2DGreenBeam)