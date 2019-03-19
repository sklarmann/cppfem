/*
 * Edge2.h
 *
 *  Created on: 03.08.2016
 *      Author: Klarmann
 */

#pragma once

#include <forwarddeclaration.h>
#include <geometry/GenericGeometryElement.h>

#include <geometry/GeometryTypes.h>

#include <vector>

namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	template<typename prec, typename uint>
	class LinearEdge : public GenericGeometryElement<prec,uint> {
	public:
		LinearEdge(PointerCollection<prec,uint> *pointers);
		~LinearEdge();
		GeometryTypes getType(){return GeometryTypes::LinearEdge;};
		uint getNumberOfVerts() { return 2; };
		void getVerts(std::vector<uint> &vertsOut);
		void setVerts(std::vector<uint> &vertsIn);
		void print(PointerCollection<prec, uint> &pointers);

	private:
		uint verts[2];
	
	
	};
	

} /* namespace FEMProject */
