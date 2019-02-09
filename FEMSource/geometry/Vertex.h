/*
 * Vertex.h
 *
 *  Created on: 28.07.2016
 *      Author: Klarmann
 */

#pragma once

#include <forwarddeclaration.h>

#include <geometry/GenericGeometryElement.h>

namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	template <typename prec, typename uint>
	class Vertex : public GenericGeometryElement<prec,uint> {
	public:
		Vertex(PointerCollection<prec, uint> *ptrCollection);
		~Vertex();
		void setCoordinates(const prec &x=0, const prec &y=0, const prec &z=0);
		void print(PointerCollection<prec, uint> &pointers);
		GeometryTypes getType(){return GeometryTypes::Vertex;};
		std::vector<prec> getCoordinates();
	
	protected:
		prec x, y, z;
	};

} /* namespace FEMProject */

