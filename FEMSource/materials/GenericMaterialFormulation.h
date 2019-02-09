/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#pragma once

#include <forwarddeclaration.h>

namespace FEMProject {

	template<typename prec, typename uint>
	class GenericMaterialFormulation {
	public:
		GenericMaterialFormulation();
		virtual ~GenericMaterialFormulation();

		virtual void readData(stringCommandHandler &Command, Userconstants<prec> *ucons);
	private:
	};
	
}
