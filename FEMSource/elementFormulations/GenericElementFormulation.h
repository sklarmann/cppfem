/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#pragma once

#include <forwarddeclaration.h>

#include <vector>
#include <Eigen/Dense>

namespace FEMProject {
	template <typename prec, typename uint>
	class GenericFiniteElement;

	template<typename prec, typename uint>
	class PointerCollection;


	template<typename prec, typename uint>
	class GenericElementFormulation {
	public:
		GenericElementFormulation(PointerCollection<prec, uint> *ptrCol);
		virtual ~GenericElementFormulation();

		virtual void readData(stringCommandHandler &Command, Userconstants<prec> *ucons);
		virtual void setDegreesOfFreedom(GenericFiniteElement<prec, uint> *elem);
		virtual void setTangentResidual(GenericFiniteElement<prec, uint> *elem
			, Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
			, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
			, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {};
	protected:
		PointerCollection<prec, uint> *ptrCol;
	};
}
