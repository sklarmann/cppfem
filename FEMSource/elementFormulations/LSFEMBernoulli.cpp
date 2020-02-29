#include <preprocessDefine.h>

#include <control/stringCommandHandler.h>

#include <elementFormulations/GenericElementFormulation.h>
#include <elementFormulations/LSFEMBernoulli.h>

#include <finiteElements/GenericFiniteElement.h>

#include <geometry/GenericGeometryElement.h>


#include <equations/NodeSet.h>
#include <equations/Nodetypes.h>
#include <equations/GenericNodes.h>
#include <equations/EquationHandler.h>

#include <math/Userconstants.h>

#include <pointercollection/pointercollection.h>
#include <solver/GenericSolutionState.h>

#include <Eigen/Dense>

#include <loads/PropfunctionHandler.h>

namespace FEMProject {

	template<typename prec, typename uint>
	LSFEMBernoulli<prec, uint>::LSFEMBernoulli(PointerCollection<prec, uint>* ptrCol) :
		GenericElementFormulation<prec, uint>(ptrCol)
	{
	}
	template<typename prec, typename uint>
	LSFEMBernoulli<prec, uint>::~LSFEMBernoulli()
	{
	}
	template<typename prec, typename uint>
	void LSFEMBernoulli<prec, uint>::readData(stringCommandHandler & Command, Userconstants<prec>* ucons)
	{
		std::string temp;
		temp = Command.getRhs("meshiddisp");
		this->meshIdDisp = static_cast<uint>(ucons->process(temp));
		temp = Command.getRhs("ea");
		this->EA = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("ei");
		this->EI = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("ga");
		this->GA = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("rhoa");
		this->rhoA = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("propnum");
		this->propnum = static_cast<uint>(ucons->process(temp));
		temp = Command.getRhs("local");
		this->localLoad = static_cast<uint>(ucons->process(temp));
		temp = Command.getRhs("qx");
		this->qx = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("qy");
		this->qy = static_cast<prec>(ucons->process(temp));
		temp = Command.getRhs("mz");
		this->mz = static_cast<prec>(ucons->process(temp));
	}
	template<typename prec, typename uint>
	void LSFEMBernoulli<prec, uint>::setDegreesOfFreedom(GenericFiniteElement<prec, uint>* elem)
	{
		GenericGeometryElement<prec, uint> *geoTemp;
		NodeSet<prec, uint> *tempSet;
		for (auto i = 0; i < 2; ++i) {
			geoTemp = elem->getVertex(*this->ptrCol, i);
			uint nsets = 1;
			geoTemp->setNumberOfNodeSets(*this->ptrCol, nsets);
			nsets = 0;
			tempSet = geoTemp->getSet(*this->ptrCol, nsets);
			tempSet->setNumberOfNodes(2);
			tempSet->setType(NodeTypes::displacement);
			tempSet->setMeshId(this->meshIdDisp);

		}
	}
	template<typename prec, typename uint>
	void LSFEMBernoulli<prec, uint>::setTangentResidual(GenericFiniteElement<prec, uint>* elem, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
	{
		GenericGeometryElement<prec, uint> *vert1, *vert2;
		EquationHandler<prec, uint> *eqHandler;
		eqHandler = this->ptrCol->getEquationHandler();
		NodeSet<prec, uint> *set1, *set2;
		vert1 = elem->getVertex(*this->ptrCol, 0);
		vert2 = elem->getVertex(*this->ptrCol, 1);
		set1 = vert1->getSetMeshId(*this->ptrCol, this->meshIdDisp);
		set2 = vert2->getSetMeshId(*this->ptrCol, this->meshIdDisp);
		std::vector<GenericNodes<prec, uint>*> temp, Nodes;
		eqHandler->getNodes(temp, *set1);
		Nodes.push_back(temp[0]);
		Nodes.push_back(temp[1]);
		temp.clear();
		eqHandler->getNodes(temp, *set2);
		set2->getNodes(temp);
		Nodes.push_back(temp[0]);
		Nodes.push_back(temp[1]);

		std::vector<DegreeOfFreedom<prec, uint>*> tempDofs;
		Nodes[0]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
		for (auto i = 0; i < 3; ++i) {
			Dofs.push_back(tempDofs[i]);
		}
		Nodes[1]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
		for (auto i = 0; i < 3; ++i) {
			Dofs.push_back(tempDofs[i]);
		}
		Nodes[2]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
		for (auto i = 0; i < 3; ++i) {
			Dofs.push_back(tempDofs[i]);
		}
		Nodes[3]->getDegreesOfFreedom(*this->ptrCol, tempDofs);
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

		
		GenericSolutionState<prec, uint> *sol = this->ptrCol->getSolutionState();
		Eigen::Matrix<prec, Eigen::Dynamic, 1> disp;
		disp = sol->getSolution(Dofs);
		

		std::vector<prec> gp, weight;

		gp.push_back((prec)-0.5);
		gp.push_back((prec)0.5);
		weight.push_back((prec)1 / sqrt((prec)3));
		weight.push_back((prec)1 / sqrt((prec)3));


		Eigen::Matrix<prec, 2, 1> svec;
		svec(0) = coor2[0] - coor1[0];
		svec(1) = coor2[1] - coor1[1];

		svec = svec / length;


		Eigen::Matrix<prec, 4, Eigen::Dynamic> Bmat;
		Eigen::Matrix<prec, 1, Eigen::Dynamic> NN;
		Bmat.resize(4, 12);
		Bmat.setZero();
		NN.resize(1, 12);
		NN.setZero();
		
		stiffness.resize(12, 12);
		stiffness.setZero();
		residual.resize(12);
		residual.setZero();
		for (auto i = 0; i < gp.size(); ++i) {
			Eigen::Matrix<prec, Eigen::Dynamic,1> shapeDeriv, shape;
			shapeDeriv.resize(2);
			shape.resize(2);
			shape(0) = ((prec)1.0 - gp[i]) / (prec)2.0;
			shape(1) = ((prec)1.0 + gp[i]) / (prec)2.0;
			shapeDeriv(0) = -(prec)1.0 / length;
			shapeDeriv(1) = (prec)1.0 / length;

			for (auto j = 0; j < 2; ++j) {
				Bmat(0, j * 6) = shapeDeriv(j);
				Bmat(0, j * 6 + 1) = -shape(j);

				Bmat(1, j * 6 + 1) = this->EI*shapeDeriv(j);
				Bmat(1, j * 6 + 2) = -shape(j);


				Bmat(2, j * 6 + 2) = shapeDeriv(j);
				Bmat(2, j * 6 + 3) = -shape(j);


				Bmat(3, j * 6 + 3) = shapeDeriv(j);

				NN(0, j * 6 + 3) = (prec)1.0 / (prec)2.0;;
			}

			residual += NN.transpose() * this->qy;// *length / (prec)2.0 * weight[i];
			stiffness += (Bmat.transpose() * Bmat) * length / (prec)2.0 * weight[i];
			
		}



		

	}
	template<typename prec, typename uint>
	void LSFEMBernoulli<prec, uint>::setMass(GenericFiniteElement<prec, uint>* elem, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
	{
		GenericGeometryElement<prec, uint> *vert1, *vert2;
		EquationHandler<prec, uint> *eqHandler;
		eqHandler = this->ptrCol->getEquationHandler();
		NodeSet<prec, uint> *set1, *set2;
		vert1 = elem->getVertex(*this->ptrCol, 0);
		vert2 = elem->getVertex(*this->ptrCol, 1);
		set1 = vert1->getSetMeshId(*this->ptrCol, this->meshIdDisp);
		set2 = vert2->getSetMeshId(*this->ptrCol, this->meshIdDisp);
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

		stiffness.resize(6, 6);
		for (auto i = 0; i < 2; ++i) {
			stiffness(i, i) = this->rhoA*length / (prec)2;
			stiffness(i+3, i+3) = this->rhoA*length / (prec)2;
		}
			//stiffness(2, 2) = this->rhoA*length / (prec)2*(prec)1e-12;
			//stiffness(5, 5) = this->rhoA*length / (prec)2*(prec)1e-12;
	}

	template<typename prec, typename uint>
	void LSFEMBernoulli<prec, uint>::getElementsLocalNodalReactions(PointerCollection<prec, uint>& ptrCol, GenericFiniteElement<prec, uint>* elem, std::map<uint, std::vector<prec>>& vReacs)
	{
		uint vert1 = elem->getVertexId(ptrCol, 0);
		uint vert2 = elem->getVertexId(ptrCol, 1);
 
		Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> stiffness;
		Eigen::Matrix<prec, Eigen::Dynamic, 1> residual;
		std::vector<DegreeOfFreedom<prec, uint>*> Dofs;

		this->setTangentResidual(elem, stiffness, residual, Dofs);

		GenericGeometryElement<prec, uint>* gvert1, * gvert2;
		gvert1 = elem->getVertex(*this->ptrCol, 0);
		gvert2 = elem->getVertex(*this->ptrCol, 1);

		std::vector<prec> coor1, coor2;
		coor1 = gvert1->getCoordinates();
		coor2 = gvert2->getCoordinates();
		prec length = (prec)0, tempDiff;
		for (auto i = 0; i < 3; ++i) {
			tempDiff = (coor1[i] - coor2[i]);
			length += tempDiff * tempDiff;
		}
		length = sqrt(length);

		Eigen::Matrix<prec, 2, 1> svec;
		svec(0) = coor2[0] - coor1[0];
		svec(1) = coor2[1] - coor1[1];

		svec = svec / length;

		prec css = svec.transpose() * svec;
		prec sst = (prec)1 - css * css;
		sst < 0 ? sst = 0 : sst = sst;
		prec sss = sqrt(sst);

		svec(0) >= 0 ? css = css : css = -absWarp(css);
		svec(1) >= 0 ? sss = sss : sss = -absWarp(sss);

		css = svec(0);
		sss = svec(1);

		Eigen::Matrix<prec, 6, 6> T;
		T.setZero();
		T(0, 0) = css;
		T(0, 1) = sss;
		T(1, 0) = -sss;
		T(1, 1) = css;
		T(2, 2) = (prec)1.0;

		T(3, 3) = css;
		T(3, 4) = sss;
		T(4, 3) = -sss;
		T(4, 4) = css;
		T(5, 5) = (prec)1.0;

		residual = T * residual;

		std::vector<prec> temp1(6), temp2(6);
		for (auto i = 0; i < 3; ++i) {
			temp1[i] = residual(i);
			temp2[i] = residual(i + 3);
		}
		temp1[0] = -temp1[0];
		temp1[1] = -temp1[1];
		temp1[2] = -temp1[2];
		vReacs[vert1] = temp1;
		vReacs[vert2] = temp2;
	}

} // End Namespace

instantiate(LSFEMBernoulli)
