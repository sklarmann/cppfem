
#pragma once

#include <forwarddeclaration.h>

#include <geometry/GenericGeometryElement.h>

namespace FEMProject {

	template<typename prec, typename uint>
	class LinearQuadrilateral : public GenericGeometryElement<prec, uint> {
	public:
		LinearQuadrilateral();
		~LinearQuadrilateral();
		void setVerts(const std::vector<uint> &vertsIn);
		void setEdges(const std::vector<uint> &edgesIn);
		GeometryTypes getType() { return GeometryTypes::LinearQuadrilateral; };
	private:
		uint verts[4], edges[4];
	};
}