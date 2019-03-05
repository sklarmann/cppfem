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
	{
		prec val1 = 3.0 / 2.0, val2 = 2.0;
		shape = -val2*sqrt(val1);
		derivative = 0.0;
		break;
	}
	case 1:
	{
		prec val1 = 5.0 / 2.0, val2 = 2.0;
		shape = -val2*sqrt(val1)*coor;
		derivative = -val2*sqrt(val1);
		break;
	}
	case 2:
	{
		prec val1 = 7.0 / 2.0, val2 = 1.0 / 2.0, val3 = 1.0, val4 = 5.0, val5=10.0;
		shape = -val2*sqrt(val1)*(coor*coor*val4 - val3);
		derivative = -val2*sqrt(val1)*val5*coor;
		break;
	}
	case 3:
		shape = -(prec)1.0 / (prec)2.0*sqrt((prec)9.0 / (prec)2.0)*((prec)7.0*coor*coor - (prec)3.0)*coor;
		derivative = -(prec)1.0 / (prec)2.0*sqrt((prec)9.0 / (prec)2.0)*((prec)21.0*coor*coor - (prec)3.0);
		break;
	default:
		std::cout << "Not implemented!" << std::endl;
	}
}



#endif /* KERNELSHAPE_HPP_ */
