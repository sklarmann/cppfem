/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#include <preprocessDefine.h>

#include <materials/MaterialFormulation1.h>

#include <control/stringCommandHandler.h>

#include <math/Userconstants.h>

#include <string>

namespace FEMProject {

	template<typename prec, typename uint>
	MaterialFormulation1<prec, uint>::MaterialFormulation1() {

	}

	template<typename prec, typename uint>
	MaterialFormulation1<prec, uint>::~MaterialFormulation1() {

	}

	template<typename prec, typename uint>
	void MaterialFormulation1<prec, uint>::readData(stringCommandHandler &Command, Userconstants<prec> *ucons) {
		
		std::string temp = Command.getRhs("emodul");
		this->emodul = ucons->process(temp);
		
		temp = Command.getRhs("nu");
		this->nu = ucons->process(temp);


	}

}

instantiate(MaterialFormulation1)