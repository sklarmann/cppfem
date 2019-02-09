/*
 * Material.h
 *
 *  Created on: 17.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>



namespace FEMProject {
	template<typename prec,typename uint>
	class Material {
	public:
		Material(PointerCollection<prec,uint> *ptrCol);
		~Material();
		void setElementForumaltion(const uint &elementFormulation);
		void setMaterialFormulation(const uint &materialFormulation);
		GenericElementFormulation<prec, uint>* getElementFormulation();
		GenericMaterialFormulation<prec, uint>* getMaterialFormulation();
	private:
		GenericMaterialFormulation<prec, uint> *materialFormulation;
		GenericElementFormulation<prec, uint> *elementFormulation;
		PointerCollection<prec, uint> *ptrCol;
	};


} /* namespace FEMProject */

