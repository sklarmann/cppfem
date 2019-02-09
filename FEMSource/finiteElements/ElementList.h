/*
 * ElementList.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once


#include <finiteElements/GenericFiniteElement.h>
#include <equations/GeometryData.h>
#include <finiteElements/LinearTriangleElement.h>
#include <vector>
#include <iostream>


namespace FEMProject {

	template <typename prec, typename uint>
	class PointerCollection;


template<typename prec, typename uint>
class ElementList {
public:
	ElementList(PointerCollection<prec,uint> *pointers);
	~ElementList();
	GenericFiniteElement<prec,uint> *requestNewElement(const Elementtypes &type);
	GenericFiniteElement<prec,uint> *getElement(const uint &number);
	uint getNumberOfElements(){uint num; num = static_cast<uint>(this->elementIndex.size()); return num;};
private:
	PointerCollection<prec, uint> *pointers;

	std::vector<uint> elementIndex;
	std::vector<Elementtypes> elementTypes;

	std::vector<LinearTriangleElement<prec,uint>> linearTriangles;
};


template<typename prec, typename uint>
ElementList<prec,uint>::ElementList(PointerCollection<prec, uint> *pointers){
	this->pointers = pointers;
}


template<typename prec, typename uint>
ElementList<prec,uint>::~ElementList(){
	//this->elementIndex.clear();
	//this->elementIndex.clear();
	//this->elementTypes.clear();
	//this->linearTriangles.clear();
	this->pointers = 0;
}

template<typename prec, typename uint>
GenericFiniteElement<prec,uint> *ElementList<prec,uint>::requestNewElement(const Elementtypes &type){

	GenericFiniteElement<prec,uint> *temp = 0;

	switch(type){
	case Elementtypes::Line:

		break;
	case Elementtypes::LinearTriangle:
		uint number;
		number = static_cast<uint>(this->linearTriangles.size());
		this->elementIndex.push_back(number);
		this->elementTypes.push_back(Elementtypes::LinearTriangle);
		number = static_cast<uint>(this->elementTypes.size())-1;
		this->linearTriangles.emplace_back(this->pointers);
		temp = &this->linearTriangles.back();
		temp -> setId(number);

		break;
	case Elementtypes::Generic:
		std::cout << "Error" << std::endl;
		break;
	default:
		break;
	}
	return temp;
}


template<typename prec, typename uint>
GenericFiniteElement<prec,uint> *ElementList<prec,uint>::getElement(const uint &number){
	if(static_cast<std::size_t>(number)>=this->elementIndex.size()){
		//TODO throw exception
	}

	switch(this->elementTypes[number]){
	case Elementtypes::Line:
		break;
	case Elementtypes::LinearTriangle:
		return &this->linearTriangles[this->elementIndex[number]];
		break;
	default:
		//TODO throw exception
		return 0;
	}
	return 0;
}


} /* namespace FEMProject */

