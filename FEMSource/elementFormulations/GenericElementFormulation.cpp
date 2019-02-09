/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#include <preprocessDefine.h>

#include <elementFormulations/GenericElementFormulation.h>

#include <Eigen/Dense>

namespace FEMProject {


	template<typename prec,typename uint>
	GenericElementFormulation<prec, uint>::GenericElementFormulation(PointerCollection<prec, uint> *ptrCol) {
		this->ptrCol = ptrCol;
	}

	template<typename prec, typename uint>
	GenericElementFormulation<prec, uint>::~GenericElementFormulation() {
		this->ptrCol = 0;
	}

	template<typename prec, typename uint>
	void GenericElementFormulation<prec, uint>::setDegreesOfFreedom(GenericFiniteElement<prec, uint> *elem) {
		
	}

	template<typename prec, typename uint>
	void GenericElementFormulation<prec, uint>::readData(stringCommandHandler &Command, Userconstants<prec> *ucons) {

	}
}

instantiate(GenericElementFormulation)