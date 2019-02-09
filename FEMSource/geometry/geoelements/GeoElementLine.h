/*
 * GeoElementLine.h
 *
 *  Created on: 03.08.2016
 *      Author: Klarmann
 */

#ifndef GEOELEMENTLINE_H_
#define GEOELEMENTLINE_H_

#define GEOLTEMP template<typename prec, typename uint>
#define GEONAME GeoElementLine<prec,uint>::


#include <GeoElement.h>
#include <Edge.h>
#include <iostream>

namespace FEMProject {

GEOLTEMP
class GeoElementLine: public GeoElement<prec,uint> {
public:
	GeoElementLine();
	~GeoElementLine();
	void setVertex(std::vector<Vertex<prec,uint>*> &in);
private:
	Edge<prec,uint> *edgePtr;
	Vertex<prec,uint> *vert1, *vert2;
};

GEOLTEMP
GEONAME GeoElementLine(){
	this->edgePtr = 0;
	this->vert1 = 0;
	this->vert2 = 0;
}

GEOLTEMP
GEONAME ~GeoElementLine(){

}

GEOLTEMP
void GEONAME setVertex(std::vector<Vertex<prec,uint>*> &in){
	if(in.size()!=2){

	}else{
		this->vert1 = in[0];
		this->vert2 = in[1];
		std::cout << "Richtig" << std::endl;
	}
}

} /* namespace FEMProject */

#undef GEOTEMP
#undef GEONAME

#endif /* GEOELEMENTLINE_H_ */
