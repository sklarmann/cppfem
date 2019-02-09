/*
 * KernelShape.h
 *
 *  Created on: 22.08.2016
 *      Author: Klarmann
 */

#ifndef KERNELSHAPE_HPP_
#define KERNELSHAPE_HPP_

#include <cmath>
#include <iostream>

template<typename prec, typename uint>
void KernelShapes(prec &shape, prec &derivative, const prec &coor, const uint &number) {
	switch (number) {
	case 0:
		shape = -2.0*std::sqrt(3.0 / 2.0);
		derivative = 0.0;
		break;
	case 1:
		shape = -2.0*std::sqrt(5.0 / 2.0)*coor;
		derivative = -2.0*std::sqrt(5.0 / 2.0);
		break;
	case 2:
		shape = -1.0 / 2.0*std::sqrt(7.0 / 2.0)*(5.0*coor*coor - 1.0);
		derivative = -1.0 / 2.0*std::sqrt(7.0 / 2.0)*10.0*coor;
		break;
	case 3:
		shape = -1.0 / 2.0*std::sqrt(9.0 / 2.0)*(7.0*coor*coor - 3.0)*coor;
		derivative = -1.0 / 2.0*std::sqrt(9.0 / 2.0)*(21.0*coor*coor - 3.0);
		break;
	default:
		std::cout << "Not implemented!" << std::endl;
	}
}



#endif /* KERNELSHAPE_HPP_ */
