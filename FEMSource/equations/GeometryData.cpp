/*
 * Model.h
 *
 *  Created on: 01.08.2016
 *      Author: simon
 */


#include <preprocessDefine.h>

#include <equations/GeometryData.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <geometry/Vertex.h>
#include <geometry/Edge.h>
#include <geometry/LinearTriangle.h>

#include <math/Plane.h>


#include <vector>
#include <iomanip>
#include <iterator>
#include <algorithm>

namespace FEMProject {
	
	
	
	template<typename prec, typename uint>
	GeometryData<prec,uint>::GeometryData(PointerCollection<prec, uint> *pointers){
		this->pointers = pointers;
		this->numberOfVerts = 0;
	}
	
	
	template<typename prec, typename uint>
	GeometryData<prec,uint>::~GeometryData(){
		this->pointers = 0;
		for (auto i = 0; i < this->vertListIntern.size(); ++i) {
			delete this->vertListIntern[i];
		}
		for (auto i = 0; i < this->edgeList.size(); ++i) {
			delete this->edgeList[i];
		}
		for (auto i = 0; i < this->faceList.size(); ++i) {
			delete this->faceList[i];
		}
	}
	
	template<typename prec, typename uint>
	uint GeometryData<prec,uint>::requestNewVert(){
		uint num = static_cast<uint>(this->vertListOut.size());
		this->vertListOut.push_back(num);
		
		this->vertListIntern.emplace_back(new Vertex<prec, uint>(this->pointers));
			
		GenericGeometryElement<prec,uint> *temp;
		temp = this->vertListIntern.back();
		temp ->setId(num);
	
		return (this->vertListOut.back());
	
	}
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec,uint> *GeometryData<prec,uint>::getVertex(const uint &num){
		GenericGeometryElement<prec,uint> *ret = 0;
		if(static_cast<std::size_t>(num) < this->vertListOut.size()){
			ret = this->vertListIntern[this->vertListOut[num]];
		}else{
			//TODO throw exception
		}
		return ret;
	}
	
	template<typename prec, typename uint>
	uint GeometryData<prec,uint>::requestNewGeometryObject(const GeometryTypes &type){
		uint ret = 0;
		GenericGeometryElement<prec,uint> *temp;
		switch(type){
		case GeometryTypes::Vertex:
			ret = static_cast<uint>(this->vertListOut.size());
			this->vertListOut.push_back(ret);
			this->vertListIntern.emplace_back(new Vertex<prec,uint>(this->pointers));
			this->vertListIntern.back()->setId(this->numberOfVerts);
			++this->numberOfVerts;
			break;
		case GeometryTypes::LinearEdge:
			ret = static_cast<uint>(this->edgeListOut.size());
			this->edgeListOut.push_back(static_cast<uint>(this->edgeList.size()));
			this->edgeList.emplace_back(new LinearEdge<prec,uint>(this->pointers));
			temp = this->edgeList.back();
			temp ->setId(ret);
			//delete temp;
			break;
		//case GeometryTypes::QuadraticEdge:
		//	ret = static_cast<uint>(this->edgeListOut.size());
		//	this->edgeListOut.push_back(static_cast<uint>(this->edgeList.size()));
		//	this->edgeList.emplace_back(new LinearEdge<prec, uint, GeometryTypes::QuadraticEdge>(this->pointers));
		//	temp = this->edgeList.back();
		//	temp->setId(ret);
		//	//delete temp;
		//	break;
		case GeometryTypes::LinearTriangle:
			ret = static_cast<uint>(this->faceListOut.size());
			this->faceListOut.push_back(static_cast<uint>(this->faceList.size()));
			this->faceList.emplace_back(new LinearTriangle<prec,uint>(this->pointers));
			temp = this->faceList.back();
			temp->setId(ret);
			break;
		default:
			//TODO throw exception
			std::cout << "ERROR: GeometryType not defined" << std::endl;
			break;
		}
		return ret;
	}
	
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec,uint> *GeometryData<prec,uint>::getGeometryElement(const GeometryTypes &type, uint num){
	
		switch (type){
		case GeometryTypes::Vertex:
			if(static_cast<std::size_t>(num)>=this->vertListOut.size()){
				//TODO throw exception
				std::cout << "ERROR: Vertex: " << num << " not in List!" << std::endl;
			}
			return this->vertListIntern[this->vertListOut[num]];
			break;
		case GeometryTypes::LinearEdge:
			if(static_cast<std::size_t>(num)>=this->edgeListOut.size()){
				//TODO throw exception
				std::cout << "ERROR edge not in List!" << std::endl;
			}
			
			return this->edgeList[this->edgeListOut[num]];
			break;
		case GeometryTypes::LinearTriangle:
			if (static_cast<std::size_t>(num) >= this->faceListOut.size()) {
				//TODO throw exception
				std::cout << "ERROR edge not in List!" << std::endl;
			}

			return this->faceList[this->faceListOut[num]];
		default:
			//TODO throw exception
			std::cout << "getGeometryElement Error" << std::endl;
		}
		return 0;
	}
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec,uint> *GeometryData<prec,uint>::getEdge(const uint &num){
		if(static_cast<std::size_t>(num)>=this->edgeListOut.size()){
			//TODO throw exception
		}
		GenericGeometryElement<prec,uint> *temp = 0;
		temp = this->edgeList[this->edgeListOut[num]];
			
		return temp;
	}
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec, uint> *GeometryData<prec, uint>::getFace(const uint &num) {
		if (static_cast<std::size_t>(num) >= this->faceListOut.size()) {
			//TODO throw exception
		}
		GenericGeometryElement<prec, uint> *temp = 0;
		temp = this->faceList[this->faceListOut[num]];
		
		return temp;
	}
	
	
	template <typename prec, typename uint>
	void GeometryData<prec,uint>::getGeometricElementInPlane(const std::vector<prec> &normal, const std::vector<prec> &point, const GeometryTypes &type, std::stack<GenericGeometryElement<prec,uint>*> &elems) {
		
		Plane<prec, uint> plane;
		plane.set(normal, point);
		std::vector<uint> vertNums;
		uint tempnum;
		uint lsize = static_cast<uint>(this->vertListOut.size());
		GenericGeometryElement<prec, uint> *temp;
		for (uint i = 0; i < lsize; ++i) {
			tempnum = this->vertListOut[i];
			temp = this->vertListIntern[tempnum];
			if (plane.inPlane(temp->getCoordinates())) {
				vertNums.push_back(tempnum);
			}
		}
		


		switch (type) {
		case GeometryTypes::Vertex:
		{
			auto lend = vertNums.size();
			for (auto i = 0; i < lend; ++i) {
				elems.push(this->vertListIntern[vertNums[i]]);
			}
		}
			break;
		case GeometryTypes::Edges:
		{
			if (!vertNums.empty()) {
				auto numEdges = this->edgeListOut.size();
				std::vector<uint> verts;
				for (auto i = 0; i < numEdges; ++i) {
					temp = this->edgeList[this->edgeListOut[i]];
					temp->getVerts(verts);
                    typedef typename  std::vector<uint>::iterator vecIt;
					vecIt it = verts.begin();
					bool search = true;
					while (search && it != verts.end()) {
						if (std::find(vertNums.begin(), vertNums.end(), *it) == vertNums.end()) {
							search = false;
						}
						++it;
					}
					if (search) elems.push(temp);
				}
			}
		}
			break;
		case GeometryTypes::Faces:
		{
			if (!vertNums.empty()) {
				auto numFaces = this->faceListOut.size();
				std::vector<uint> verts;
				for (auto i = 0; i < numFaces; ++i) {
					temp = this->faceList[this->faceListOut[i]];
					temp->getVerts(verts);
                    typedef typename  std::vector<uint>::iterator vecIt;
					vecIt it = verts.begin();
					bool search = true;
					while (search && it != verts.end()) {
						if (std::find(vertNums.begin(), vertNums.end(), *it) == vertNums.end()) {
							search = false;
						}
						++it;
					}
					if (search) elems.push(temp);
				}
			}
		}
		break;
//		case GeometryTypes::Faces:
//
//			break;
		default:
			std::cout << "TODO in GeometryData getGeometricElementInPlane, throw exception" << std::endl;
		}
	}

	template<typename prec, typename uint>
	void GeometryData<prec, uint>::print() {
		OutputHandler &Log = this->pointers->getInfoData()->Log;
		Log(LogLevel::BasicLog, LogLevel::BasicLog) << std::setfill(' ')
			<< "\n Geometry Data informations: \n"
			<< std::left << std::setw(40) << "\tNumber of vertices:"
			<< std::right << std::setw(20) << this->vertListOut.size() << "\n"
			<< std::left << std::setw(40)  << "\tNumber of edges: " 
			<< std::right << std::setw(20) << this->edgeListOut.size() << "\n"
			<< std::left << std::setw(40) << "\tNumber of faces: " 
			<< std::right << std::setw(20) << this->faceListOut.size() << "\n" << std::endl;



		for (auto i = 0; i < this->vertListIntern.size(); ++i) {
			this->vertListIntern[i]->print(*this->pointers);
			Log(LogLevel::FullLog, LogLevel::BasicLog) <<
				std::setw(100) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
		}
		for (auto i = 0; i < this->edgeList.size(); ++i) {
			this->edgeList[i]->print(*this->pointers);
			Log(LogLevel::FullLog, LogLevel::BasicLog) <<
				std::setw(100) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
		}
		for (auto i = 0; i < this->faceList.size(); ++i) {
			this->faceList[i]->print(*this->pointers);
			Log(LogLevel::FullLog, LogLevel::BasicLog) <<
				std::setw(100) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
		}
	}

} /* namespace FEMProject */



instantiate(GeometryData)
