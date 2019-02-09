/*
 * GeoElement.h
 *
 *  Created on: 03.08.2016
 *      Author: Klarmann
 */

#ifndef GEOELEMENT_H_
#define GEOELEMENT_H_

#define GEOTEMP template <typename prec, typename uint>

#include <vector>
#include <Vertex.h>

namespace FEMProject {

GEOTEMP
class GeoElement {
public:
	GeoElement();
	virtual ~GeoElement();
	virtual void setId(uint &iid) {id=iid;};
	virtual short getNumberOfVertices();
	virtual short getNumberOfEdges();
	virtual short getNumberOfFaces();
	virtual void setVertex(std::vector<Vertex<prec,uint>*> &in);
protected:
	uint id;
};

GEOTEMP
GeoElement<prec,uint>::GeoElement(){

}

GEOTEMP
GeoElement<prec,uint>::~GeoElement(){

}

GEOTEMP
short GeoElement<prec,uint>::getNumberOfVertices(){

	return 0;
}

GEOTEMP
short GeoElement<prec,uint>::getNumberOfEdges(){

	return 0;
}


GEOTEMP
short GeoElement<prec,uint>::getNumberOfFaces(){
	return 0;
}

GEOTEMP
void GeoElement<prec,uint>::setVertex(std::vector<Vertex<prec,uint>*> &in){

}
} /* namespace FEMProject */


#undef GEOTEMP
#endif /* GEOELEMENT_H_ */
