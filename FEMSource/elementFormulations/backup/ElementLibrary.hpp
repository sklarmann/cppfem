/*
 * ElementLibrary.hpp
 *
 *  Created on: 17.08.2016
 *      Author: klari
 */

#pragma once

#include <GenericFiniteElement.h>
#include <Element201.hpp>
#include <ElementControl.hpp>
#include <ElementTypes.hpp>

namespace FEMProject{

	
template<typename prec, typename uint>
struct ElementListControl {
public:
	ControlOptions whatToDo;
};


template<typename prec, typename uint>
void elementLibrary(GenericFiniteElement<prec,uint> &element,const ControlOptions &Control){


	Material<prec, uint> *mat;
	mat = element.getMaterial();

	uint num = mat->getElementFormulation();

	switch (num) {

	case 201:
		element201(element, Control);
		break;
	default:
		//TODO throw exception
		std::cout << "Element not in List!" << std::endl;
		break;
	}


}





}
