/*
 * Lobatto.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#ifndef LOBATTO_HPP_
#define LOBATTO_HPP_

#include <cmath>


template<typename prec, typename uint>
void LobattoShape(prec &shape, prec &shapeDerivative, const prec &coor, const uint number){
	switch (number){
	case 0:
		shape 			= (static_cast<prec>(1)-coor)/static_cast<prec>(2);
		shapeDerivative = -static_cast<prec>(1)/static_cast<prec>(2);
		break;
	case 1:
		shape 			= (static_cast<prec>(1)+coor)/static_cast<prec>(2);
		shapeDerivative = static_cast<prec>(1)/static_cast<prec>(2);
		break;
	case 2:
		prec fac1 = static_cast<prec>(1)/static_cast<prec>(2);
		prec fac2 = static_cast<prec>(3)/static_cast<prec>(2);
		shape 			= fac1*sqrt(fac2)*(coor*coor-static_cast<prec>(1));
		shapeDerivative = fac1*sqrt(fac2)*static_cast<prec>(2)*coor;
	}
}



#endif /* LOBATTO_HPP_ */
