
#include <preprocessDefine.h>

#include <geometry/LinearBrick.h>


namespace FEMProject {


	template<typename prec, typename uint>
	LinearBrick<prec,uint>::LinearBrick() : GenericGeometryElement<prec, uint>() {

	}

	template <typename prec, typename uint>
	LinearBrick<prec, uint>::~LinearBrick() {

	}

	template<typename prec, typename uint>
	void LinearBrick<prec, uint>::setVerts(const std::vector<uint> &vertsIn) {
		if (vertsIn.size() == 8) {
			for (auto i = 0; i < 8; ++i) {
				this->verts[i] = vertsIn[i];
			}
		}
		else {
			// TODO throw exception
		}
	}

	template<typename prec, typename uint>
	void LinearBrick<prec, uint>::setEdges(const std::vector<uint> &edgesIn) {
		if (edgesIn.size() == 12) {
			for (auto i = 0; i < 12; ++i) {
				this->edges[i] = edgesIn[i];
			}
		}
		else {
			// TODO throw exception
		}
	}

	template<typename prec, typename uint>
	void LinearBrick<prec, uint>::setFaces(const std::vector<uint> &facesIn) {
		if (facesIn.size() == 6) {
			for (auto i = 0; i < 6; ++i) {
				this->faces[i] = facesIn[i];
			}
		}
		else {
			//TODO throw exception
		}
	}


}

instantiate(LinearBrick)