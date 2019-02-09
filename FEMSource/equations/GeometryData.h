/*
 * Model.h
 *
 *  Created on: 01.08.2016
 *      Author: simon
 */

#pragma once

#include <forwarddeclaration.h>

#include <geometry/GeometryTypes.h>
#include <stack>
#include <vector>

namespace FEMProject {

	template<typename prec, typename uint>
	class GeometryData {
	public:
		GeometryData(PointerCollection<prec,uint> *pointers);
		virtual ~GeometryData();
		uint requestNewVert();
		GenericGeometryElement<prec,uint> *getVertex(const uint &num);
	
		GenericGeometryElement<prec,uint> *getEdge(const uint &num);
		GenericGeometryElement<prec, uint> *getFace(const uint &num);
	
	
		uint requestNewGeometryObject(const GeometryTypes &type);
		GenericGeometryElement<prec,uint> *getGeometryElement(const GeometryTypes &type, uint num);
	
	
		uint getNumberOfVertices(){uint ret = static_cast<uint>(this->vertListOut.size());return ret;};
		uint getNumberOfEdges(){uint ret = static_cast<uint>(this->edgeListOut.size());return ret;};
	
		void getGeometricElementInPlane(const std::vector<prec> &normal, const std::vector<prec> &point, const GeometryTypes &type, std::stack<GenericGeometryElement<prec,uint>*> &elems);
		void print();
	private:
		PointerCollection<prec, uint> *pointers;
	
		std::vector<uint> vertListOut;
		std::vector<GenericGeometryElement<prec,uint>*>  vertListIntern;
		uint numberOfVerts;
	
		std::vector<uint> edgeListOut;
		std::vector<GenericGeometryElement<prec,uint>*> edgeList;

		std::vector<uint> faceListOut;
		std::vector<GenericGeometryElement<prec,uint>*> faceList;
	};
	
	
} /* namespace FEMProject */

