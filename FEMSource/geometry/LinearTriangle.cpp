/*
 * LinearTriangle.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <geometry/LinearTriangle.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <iomanip>

namespace FEMProject {

	
	template<typename prec, typename uint>
	LinearTriangle<prec,uint>::LinearTriangle(PointerCollection<prec, uint> *ptrCol) : GenericGeometryElement<prec,uint> (){
	
	}
	
	template<typename prec, typename uint>
	LinearTriangle<prec,uint>::~LinearTriangle(){
	
	}

	template<typename prec, typename uint>
	void LinearTriangle<prec, uint>::setVerts(std::vector<uint> &vertsIn) {
		if (vertsIn.size() == 3) {
			for (auto i = 0; i < 3; ++i) {
				this->verts[i] = vertsIn[i];
			}
		}
	}

	template<typename prec, typename uint>
	inline void LinearTriangle<prec, uint>::print(PointerCollection<prec, uint>& pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			std::left << std::setw(20) << "Linear Triangle id:" <<
			std::right << std::setw(10) << this->id << "\n" <<
			std::left << std::setw(10) << "Vertex 1:" <<
			std::right << std::setw(10) << this->verts[0] <<
			std::left << std::setw(10) << "Vertex 2:" <<
			std::right << std::setw(10) << this->verts[1] <<
			std::left << std::setw(10) << "Vertex 3:" <<
			std::right << std::setw(10) << this->verts[2] << "\n" <<
			std::left << std::setw(10) << "Edge 1:" <<
			std::right << std::setw(10) << this->edges[0] <<
			std::left << std::setw(10) << "Edge 2:" <<
			std::right << std::setw(10) << this->edges[1] <<
			std::left << std::setw(10) << "Edge 3:" <<
			std::right << std::setw(10) << this->edges[2] << "\n";
		this->printEqInfo(pointers);
	}

	
	
	

	
	
	template<typename prec, typename uint>
	void LinearTriangle<prec,uint>::setEdges(std::vector<uint> &edgesIn){
		if (edgesIn.size() == 3) {
			for (auto i = 0; i < 3; ++i) {
				this->edges[i] = edgesIn[i];
			}
		}
	}


} /* namespace FEMProject */


instantiate(LinearTriangle)