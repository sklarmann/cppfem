#include <preprocessDefine.h>

#include <control/stringCommandHandler.h>

#include <elementFormulations/GenericElementFormulation.h>
#include <elementFormulations/FiniteRotation2DTimoshenko.h>

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

namespace FEMProject {

	template<typename prec, typename uint>
	FiniteRotation2DTimoshenko<prec, uint>::FiniteRotation2DTimoshenko(PointerCollection<prec, uint>* ptrCol) :
		GenericElementFormulation<prec, uint>(ptrCol)
	{
	}
	template<typename prec, typename uint>
	FiniteRotation2DTimoshenko<prec, uint>::~FiniteRotation2DTimoshenko()
	{
	}
	template<typename prec, typename uint>
	void FiniteRotation2DTimoshenko<prec, uint>::readData(stringCommandHandler & Command, Userconstants<prec>* ucons)
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
	}
	template<typename prec, typename uint>
	void FiniteRotation2DTimoshenko<prec, uint>::setDegreesOfFreedom(GenericFiniteElement<prec, uint>* elem)
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
	void FiniteRotation2DTimoshenko<prec, uint>::setTangentResidual(GenericFiniteElement<prec, uint>* elem, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
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

		
		GenericSolutionState<prec, uint> *sol = this->ptrCol->getSolutionState();
		Eigen::Matrix<prec, Eigen::Dynamic, 1> disp;
		disp = sol->getSolution(Dofs);
		

		std::vector<prec> gp, weight;

		gp.push_back((prec)0.0);
		weight.push_back((prec)2.0);


		Eigen::Matrix<prec, 2, 1> svec;
		svec(0) = coor2[0] - coor1[0];
		svec(1) = coor2[1] - coor1[1];

		svec = svec / length;

		prec css = svec.transpose()*svec;
		prec sss = sqrt(1 - css * css);

		svec(0) >= 0 ? css = css : css = -absWarp(css);
		svec(1) >= 0 ? sss = sss : sss = -absWarp(sss);


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

		Eigen::Matrix<prec, Eigen::Dynamic, 1> localDisp;
		localDisp = T * disp;


		Eigen::Matrix<prec, 3, Eigen::Dynamic> Bmat;
		Eigen::Matrix<prec, 3, 1> strains, stress;
		Eigen::Matrix<prec, 3, 3> mat;
		mat.setZero();
		mat(0, 0) = this->EA;
		mat(1, 1) = this->GA;
		mat(2, 2) = this->EI;
 		Bmat.resize(3, 6);
		Bmat.setZero();
		stiffness.resize(6, 6);
		stiffness.setZero();
		residual.resize(6);
		residual.setZero();
		for (auto i = 0; i < gp.size(); ++i) {
			Eigen::Matrix<prec, Eigen::Dynamic,1> shapeDeriv, shape;
			shapeDeriv.resize(2);
			shape.resize(2);
			shape(0) = ((prec)1.0 - gp[i]) / (prec)2.0;
			shape(1) = ((prec)1.0 + gp[i]) / (prec)2.0;
			shapeDeriv(0) = -(prec)1.0 / length;
			shapeDeriv(1) = (prec)1.0 / length;

			prec ucx = shapeDeriv(0)*localDisp(0) + shapeDeriv(1)*localDisp(3);
			prec wcx = shapeDeriv(0)*localDisp(1) + shapeDeriv(1)*localDisp(4);
			prec bcx = shapeDeriv(0)*localDisp(2) + shapeDeriv(1)*localDisp(5);
			prec beta = shape(0)*localDisp(2) + shape(1)*localDisp(5);

			strains(0) = ucx + (prec)0.5*ucx*ucx + (prec)0.5*wcx*wcx;     // epsilon
			strains(1) = ((prec)1.0 + ucx)*sin(beta) + wcx * cos(beta);   // gamma
			strains(2) = (((prec)1.0 + ucx)*cos(beta)-wcx*sin(beta))*bcx; // kappa

			stress = mat * strains;
			prec alpha1 = (-((prec)1.0+ucx)*sin(beta)-wcx*cos(beta));
			prec alpha2 = (((prec)1.0+ucx)*cos(beta)-wcx*sin(beta));
			for (auto j = 0; j < 2; ++j) {
				Bmat(0,j * 3) = ((prec)1.0 + ucx)*shapeDeriv(j);
				Bmat(0,j * 3+1) = wcx * shapeDeriv(j);

				Bmat(1,j * 3) = sin(beta)* shapeDeriv(j);
				Bmat(1,j * 3 + 1) = cos(beta)* shapeDeriv(j);
				Bmat(1,j * 3 + 2) = alpha2 * shape(j);

				Bmat(2,j * 3) = cos(beta)*bcx* shapeDeriv(j);
				Bmat(2,j * 3 + 1) = -bcx * sin(beta)* shapeDeriv(j);
				Bmat(2,j * 3 + 2) = alpha1*bcx * shape(i)+alpha2*shapeDeriv(j);
			}
			Eigen::Matrix<prec, 6, 6> GN, GQ, GM;
			GN.setZero(); GQ.setZero(); GM.setZero();
			for (auto j = 0; j < 2; ++j) {
				for (auto k = 0; k < 2; ++k) {
					GN(j * 3, k * 3) = shapeDeriv(j)*shapeDeriv(k);
					GN(j * 3+1, k * 3+1) = shapeDeriv(j)*shapeDeriv(k);


					GQ(j * 3, k * 3 + 2) = shapeDeriv(j)*cos(beta)*shape(k);
					GQ(j * 3 + 1, k * 3 + 2) = -shapeDeriv(j)*sin(beta)*shape(k);
					GQ(j * 3 + 2, k * 3) = shape(j)*cos(beta)*shapeDeriv(k);
					GQ(j * 3 + 2, k * 3 + 1) = -shape(j)*sin(beta)*shapeDeriv(k);
					GQ(j * 3 + 2, k * 3 + 2) = shape(j)*alpha1*shape(k);

					prec a = -shape(j)*sin(beta)*bcx*shapeDeriv(k) + shapeDeriv(j)*cos(beta)*shapeDeriv(k);
					prec b = -shape(j)*cos(beta)*bcx*shapeDeriv(k) - shapeDeriv(j)*sin(beta)*shapeDeriv(k);
					prec c = -shapeDeriv(j)*sin(beta)*bcx*shape(k) + shapeDeriv(j)*cos(beta)*shapeDeriv(k);
					prec d = -shapeDeriv(j)*cos(beta)*bcx*shape(k) - shapeDeriv(j)*sin(beta)*shapeDeriv(k);
					prec e = -shape(j)*alpha2*bcx*shape(k) + shape(j)*alpha1*shapeDeriv(k) + shapeDeriv(j)*alpha1*shape(k);
					GM(j * 3, k * 3 + 2) = c;
					GM(j * 3 + 1, k * 3 + 2) = d;
					GM(j * 3 + 2, k * 3 + 2) = e;
					GM(j * 3 + 2, k * 3) = a;
					GM(j * 3 + 2, k * 3 + 1) = b;
				}
			}

			GN *= stress(0);
			GQ *= stress(1);
			GM *= stress(2);

			residual += Bmat.transpose() * stress*length / (prec)2.0 * weight[i];
			stiffness += (Bmat.transpose() * mat*Bmat+GN+GQ+GM) * length / (prec)2.0 * weight[i];
			
		}
		stiffness = T.transpose()*stiffness*T;
		residual = T.transpose()*residual;



		//stiffness.resize(6, 6);
		//residual.resize(6);
		//residual.setZero();
		//
		//stiffness.setZero();
		//
		//stiffness(0, 0) = this->EA / length;
		//stiffness(0, 3) = -this->EA / length;
		//
		//
		//stiffness(1, 1) = this->EI / length / length / length * (prec)12;
		//stiffness(1, 2) = this->EI / length / length * (prec)6;
		//stiffness(1, 4) = -this->EI / length / length / length * (prec)12;
		//stiffness(1, 5) = this->EI / length / length * (prec)6;
		//
		//stiffness(2, 1) = this->EI / length / length * (prec)6;
		//stiffness(2, 2) = this->EI / length * (prec)4;
		//stiffness(2, 4) = -this->EI / length / length * (prec)6;
		//stiffness(2, 5) = this->EI / length * (prec)2;
		//
		//stiffness(3, 0) = -this->EA / length;
		//stiffness(3, 3) = this->EA / length;
		//
		//
		//stiffness(4, 1) = -this->EI / length / length / length * (prec)12;
		//stiffness(4, 2) = -this->EI / length / length * (prec)6;
		//stiffness(4, 4) = this->EI / length / length / length * (prec)12;
		//stiffness(4, 5) = -this->EI / length / length * (prec)6;
		//
		//stiffness(5, 1) = this->EI / length / length * (prec)6;
		//stiffness(5, 2) = this->EI / length * (prec)2;
		//stiffness(5, 4) = -this->EI / length / length * (prec)6;
		//stiffness(5, 5) = this->EI / length * (prec)4;
		//
		//
		//
		//
		//
		

	}
	template<typename prec, typename uint>
	void FiniteRotation2DTimoshenko<prec, uint>::setMass(GenericFiniteElement<prec, uint>* elem, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
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
} // End Namespace

instantiate(FiniteRotation2DTimoshenko)
