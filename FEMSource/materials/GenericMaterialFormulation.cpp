/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#include <preprocessDefine.h>

#include <materials/GenericMaterialFormulation.h>

namespace FEMProject {


	template<typename prec, typename uint>
	GenericMaterialFormulation<prec, uint>::GenericMaterialFormulation() {

	}

	template<typename prec, typename uint>
	GenericMaterialFormulation<prec, uint>::~GenericMaterialFormulation() {

	}

	template<typename prec, typename uint>
	void GenericMaterialFormulation<prec, uint>::readData(stringCommandHandler &Command, Userconstants<prec> *ucons) {

	}

}

instantiate(GenericMaterialFormulation)