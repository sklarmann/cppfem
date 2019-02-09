/*
 * LinearTriangle.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <geometry/GenericGeometryElement.h>


namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;

	template<typename prec, typename uint>
	class LinearTriangle : public GenericGeometryElement<prec,uint> {
		typedef PointerCollection<prec, uint> ptrCol;
	public:
		LinearTriangle(PointerCollection<prec,uint> *ptrCol);
		~LinearTriangle();
		void setEdges(std::vector<uint> &edgesIn);
		void setVerts(std::vector<uint> &vertsIn);
		void print(PointerCollection<prec, uint> &pointers);
	private:
		uint edges[3];
		uint verts[3];
	};
	


} /* namespace FEMProject */
