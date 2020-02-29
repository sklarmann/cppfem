/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#pragma once

#include <forwarddeclaration.h>

#include <elementFormulations/GenericElementFormulation.h>
#include <Eigen/Dense>

namespace FEMProject {


	template<typename prec, typename uint>
	class LSFEMBernoulli : public GenericElementFormulation<prec, uint> {
	public:
		LSFEMBernoulli(PointerCollection<prec, uint> *ptrCol);
		~LSFEMBernoulli();
		void readData(stringCommandHandler &Command, Userconstants<prec> *ucons);
		void setDegreesOfFreedom(GenericFiniteElement<prec, uint> *elem);
		void setTangentResidual(GenericFiniteElement<prec, uint> *elem
			, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		void setMass(GenericFiniteElement<prec, uint> *elem
			, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		void getElementsLocalNodalReactions(PointerCollection<prec, uint>& ptrCol
			, GenericFiniteElement<prec, uint>* elem
			, std::map<uint, std::vector<prec>>&vReacs);
	private:
		uint meshIdDisp, intOrderDisp, propnum, localLoad;
		prec EA, EI, GA, rhoA;
		prec qx, qy, mz;


	};


}