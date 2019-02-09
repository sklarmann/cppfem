

#include <preprocessDefine.h>

#include <geometry/LinearQuadrilateral.h>



namespace FEMProject {


	template<typename prec, typename uint>
	LinearQuadrilateral<prec,uint>::LinearQuadrilateral() : GenericGeometryElement<prec, uint>()
	{

	}

	template<typename prec, typename uint>
	LinearQuadrilateral<prec, uint>::~LinearQuadrilateral(){

	}

	template<typename prec, typename uint>
	void LinearQuadrilateral<prec, uint>::setVerts(const std::vector<uint> &vertsIn) {
		if (vertsIn.size() == 4) {
			for (auto i = 0; i < 4; ++i) {
				this->verts[i] = vertsIn[i];
			}
		}
		else {
			//TDO throw exception
		}
	}

	template<typename prec, typename uint>
	void LinearQuadrilateral<prec, uint>::setEdges(const std::vector<uint> &edgesIn) {
		if (edgesIn.size() == 4) {
			for (auto i = 0; i < 4; ++i) {
				this->edges[i] = edgesIn[i];
			}
		}
		else {
			//TDO throw exception
		}
	}
}

instantiate(LinearQuadrilateral)