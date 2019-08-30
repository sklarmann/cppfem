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
	class FiniteRotation2DTimoshenko : public GenericElementFormulation<prec, uint> {
	public:
		FiniteRotation2DTimoshenko(PointerCollection<prec, uint> *ptrCol);
		~FiniteRotation2DTimoshenko();
		void readData(stringCommandHandler &Command, Userconstants<prec> *ucons);
		void setDegreesOfFreedom(GenericFiniteElement<prec, uint> *elem);
		void setTangentResidual(GenericFiniteElement<prec, uint> *elem
			, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
	private:
		uint meshIdDisp, intOrderDisp;
		prec EA, EI, GA;


	};


}