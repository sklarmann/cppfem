/*
 * Timer.h
 *
 *  Created on: 23.07.2016
 *      Author: Klarmann
 */

#include <preprocessDefine.h>

#include <control/Timer.h>


namespace FEMProject {
	template class Timer<sec>;
	template class Timer<ms>;

} /* namespace FEMProject */

