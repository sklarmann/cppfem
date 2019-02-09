/*
 * Vertex.h
 *
 *  Created on: 28.07.2016
 *      Author: Klarmann
 */

#include <preprocessDefine.h>

#include <geometry/Vertex.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>


#include <iomanip>

namespace FEMProject {

	template<typename prec, typename uint>
	Vertex<prec,uint>::Vertex(PointerCollection<prec,uint> *ptrCollection) : GenericGeometryElement<prec,uint>(){
		this->x=0;
		this->y=0;
		this->z=0;
	}
	
	template<typename prec, typename uint>
	Vertex<prec,uint>::~Vertex(){
	
	}
	
	/**
	 * @brief Routine to set the coordinates of the vertex.
	 * @param x x Coordinate
	 * @param y y Coordinate
	 * @param z z Coordinate
	 */
	template<typename prec, typename uint>
	void Vertex<prec,uint>::setCoordinates(const prec &x, const prec &y, const prec &z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	template<typename prec, typename uint>
	inline void Vertex<prec, uint>::print(PointerCollection<prec, uint> &pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			"Vertex id:" << std::setw(10) << this->id
			<< std::setw(10) << "xcoor:" << std::setw(10) << this->x
			<< std::setw(10) << "ycoor:" << std::setw(10) << this->y
			<< std::setw(10) << "zcoor:" << std::setw(10) << this->z << "\n";
		this->printEqInfo(pointers);
	}
	
	//template<typename prec, typename uint>
	//void Vertex<prec,uint>::print(){
	//	std::cout << "Vertex id: " << this->id  <<  " x: " << std::setw(8) << this->x
	//			<< " y: " << std::setw(8) << this->y << " z: " << std::setw(8)<< this->z << std::endl;
	//}
	
	
	template<typename prec, typename uint>
	std::vector<prec> Vertex<prec,uint>::getCoordinates(){
		std::vector<prec> u;
		u.resize(3);
		u[0] = this->x;
		u[1] = this->y;
		u[2] = this->z;
		return u;
	}

} /* namespace FEMProject */

instantiate(Vertex)