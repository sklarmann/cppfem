/*
 * GeometryTypes.h
 *
 *  Created on: 18.08.2016
 *      Author: Klarmann
 */


#pragma once


/**
 * @
*/


namespace FEMProject {
	enum class GeometryTypes{Generic,
		Vertex,
		Edges=100,LinearEdge=102,QuadraticEdge=103,
		Faces=200,LinearTriangle=203,LinearQuadrilateral=204, QuadrilateralNodal,
		Volumes=300,Tetra=303
	};

}