/*
 * Plane.h
 *
 *  Created on: 23.08.2016
 *      Author: Klarmann
 */

#pragma once

#include <forwarddeclaration.h>

#include <vector>

namespace FEMProject {

	template<typename prec, typename uint>
	class Plane {
	public:
		Plane() {};
		~Plane() {};
		void set(const std::vector<prec> &normal, const std::vector<prec> &point);
		bool inPlane(const std::vector<prec> &point);
		bool inPlane(const prec &x, const prec &y, const prec &z);
	private:
		std::vector<prec> normal;
		prec value;
	};


}/*End of namespace*/
