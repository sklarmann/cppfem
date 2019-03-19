/*
 * Edge2.h
 *
 *  Created on: 03.08.2016
 *      Author: Klarmann
 */

#include <preprocessDefine.h>

#include <geometry/LinearEdge.h>
#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <iomanip>

namespace FEMProject {

	
	template<typename prec, typename uint>
	LinearEdge<prec,uint>::LinearEdge(PointerCollection<prec, uint> *pointers) : GenericGeometryElement<prec,uint>(){
		for (auto i = 0; i < 2; ++i) {
			this->verts[i] = 0;
		}
	}
	

	
	template<typename prec, typename uint>
	LinearEdge<prec,uint>::~LinearEdge(){
		
	}
	
	

	template<typename prec, typename uint>
	void LinearEdge<prec, uint>::getVerts(std::vector<uint> &vertsOut) {
		vertsOut.resize(2);
		for (auto i = 0; i < 2; ++i) {
			vertsOut[i] = this->verts[i];
		}
		
	}

	template<typename prec, typename uint>
	void LinearEdge<prec, uint>::setVerts(std::vector<uint> &vertsIn) {
		if (vertsIn.size() == 2) {
			for (auto i = 0; i < 2; ++i) {
				this->verts[i] = vertsIn[i];
			}
		}
	}

	template<typename prec, typename uint>
	inline void LinearEdge<prec, uint>::print(PointerCollection<prec, uint> &pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			std::left << std::setw(20) << "Linear Edge id:" <<
			std::right << std::setw(10) << this->id <<
			std::left << std::setw(10) << "Vertex 1:" <<
			std::right << std::setw(10) << this->verts[0] <<
			std::left << std::setw(10) << "Vertex 2:" <<
			std::right << std::setw(10) << this->verts[1] << "\n";
		this->printEqInfo(pointers);
	}

} /* namespace FEMProject */

instantiate(LinearEdge)