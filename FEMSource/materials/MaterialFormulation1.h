/*
* GenericMaterialFormulation.h
*
*  Created on: 05.08.2016
*      Author: simon
*/

#pragma once

#include <forwarddeclaration.h>

#include <materials/GenericMaterialFormulation.h>

namespace FEMProject {

	template<typename prec, typename uint>
	class MaterialFormulation1 : public GenericMaterialFormulation<prec,uint> {
	public:
		MaterialFormulation1();
		~MaterialFormulation1();

		void readData(stringCommandHandler &Command, Userconstants<prec> *ucons);
	private:
		prec emodul, nu;
	};


}