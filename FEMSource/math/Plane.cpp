/*
 * Plane.h
 *
 *  Created on: 23.08.2016
 *      Author: Klarmann
 */

#include <preprocessDefine.h>

#include <math/Plane.h>

namespace FEMProject {

	template<typename prec, typename uint>
	void Plane<prec, uint>::set(const std::vector<prec> &normal, const std::vector<prec> &point) {
		if (normal.size() != 3) {
			//TODO throw exception
		}
		if (point.size() != 3) {
			//TODO throw exception
		}
		this->normal = normal;
		this->value = 0.0;
		for (auto i = 0; i < 3; ++i) {
			this->value += normal[i] * point[i];
		}
	}

	template<typename prec, typename uint>
	bool Plane<prec, uint>::inPlane(const std::vector<prec> &point) {
		bool ret = false;
		if (point.size() != 3) {
			//TODO throw exception
		}

		prec val2;
		val2 = 0;
		for (auto i = 0; i < 3; ++i) {
			val2 += this->normal[i] * point[i];
		}


		prec diff;
		diff = this->value - val2;
		prec comp;
		comp = this->value;
		if (diff < 0.0) diff = -diff;
		if (comp < 0.0) comp = -comp;
		if (diff <= comp*1.0e-14) ret = true;
		return ret;
	}

	template <typename prec, typename uint>
	bool Plane<prec, uint>::inPlane(const prec &x, const prec &y, const prec &z) {

		return false;
	}

}/*End of namespace*/


instantiate(Plane)
