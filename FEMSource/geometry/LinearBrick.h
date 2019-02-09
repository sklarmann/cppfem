
#pragma once

#include <forwarddeclaration.h>

#include <geometry/GenericGeometryElement.h>

#include <vector>

namespace FEMProject {
	
	template<typename prec,typename uint>
	class LinearBrick : public GenericGeometryElement<prec, uint> {
	public:
		LinearBrick();
		~LinearBrick();
		void setVerts(const std::vector<uint> &vertsIn);
		void setEdges(const std::vector<uint> &edgesIn);
		void setFaces(const std::vector<uint> &facesIn);
	private:
		uint verts[8], edges[12], faces[6];

	};
	

}