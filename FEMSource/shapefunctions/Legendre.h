/*
 * Legendre.h
 *
 *  Created on: 12.08.2016
 *      Author: klari
 */

#ifndef LEGENDRE_HPP_
#define LEGENDRE_HPP_


#include <vector>
#include <cmath>

template<class prec> void LegrendreShape(prec &shape, prec &shapeDerivative, const prec &coor, const uint &number){


	switch(number) {

	case 0:
		shape = dynamic_cast<prec> (1);
		shapeDerivative = dynamic_cast<prec> (0);
		break;
	case 1:
		shape = coor;
		shapeDerivative = dynamic_cast<prec> (1);
		break;
	case 2:
		shape = dynamic_cast<prec> (3)/dynamic_cast<prec> (2) *std::pow(coor,2)-dynamic_cast<prec> (1)/dynamic_cast<prec> (2);
		shapeDerivative = dynamic_cast<prec> (3) * coor;
		break;
	case 3:
		shape = dynamic_cast<prec> (5)/dynamic_cast<prec> (2)*std::pow(coor, 3)-dynamic_cast<prec> (3)/dynamic_cast<prec> (2)*coor;
		shapeDerivative = dynamic_cast<prec> (15)/dynamic_cast<prec> (2)*std::pow(coor, 2)-dynamic_cast<prec> (3)/dynamic_cast<prec> (2);
		break;

	}

}



#endif /* LEGENDRE_HPP_ */
