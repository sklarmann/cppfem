/*
 * GenericGeometryElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <geometry/GeometryTypes.h>

#include <vector>

namespace FEMProject {

	
	template<typename prec, typename uint>
	class GenericGeometryElement {
		typedef PointerCollection<prec, uint> ptrCol;
	public:
		GenericGeometryElement();
		virtual ~GenericGeometryElement();
		void setId(const uint &id){this->id = id;};
		uint getId() { return this->id; };
		void setNumberOfNodeSets(ptrCol &pointers, uint &numberOfSets);
		NodeSet<prec,uint> *getSet(ptrCol &pointers, uint &setNumber);
		NodeSet<prec, uint> *getSetMeshId(ptrCol &pointers, const uint &meshId);
		void getSets(ptrCol &pointers, std::vector<NodeSet<prec,uint>*> &sets);
		void getNodesOfSet(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &nodeVector, const uint &setNumber);
		bool checkSetWithMeshId(ptrCol &pointers, const uint &meshId);
	
		void setAllNodeBoundaryConditionMeshId(ptrCol &pointers, const uint &meshId, const uint &dof);
		//void getEquationsIds(std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus, const unsigned char &meshId);
		void getAllEquationsIds(ptrCol &pointers, std::vector<DegreeOfFreedom<prec,uint>*> &Dofs);
		void getNodeEquationIds(ptrCol &pointers, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs, const uint &meshId, const uint &nodeNumber);

		virtual GeometryTypes getType(){return GeometryTypes::Generic;};
		virtual void print(PointerCollection<prec,uint> &pointers);
		void printEqInfo(PointerCollection<prec,uint> &pointers);

		virtual uint getNumberOfVerts() { return 0; };
	
	
		virtual void setCoordinates(const prec &x=0, const prec &y=0, const prec &z=0){};
		virtual std::vector<prec> getCoordinates(){std::vector<prec> u;u.resize(0);return u;};;
		//virtual void setTriangleEdges(const uint &edge1, const uint &edge2, const uint &edge3) {};
	
		virtual void setVerts(std::vector<uint> &vertsIn) {};
		virtual void getVerts(std::vector<uint> &vertsOut) { vertsOut.resize(0); };

		virtual void setEdges(std::vector<uint> &edgesIn) {};
		virtual void getEdges(std::vector<uint> &edgesOut) { edgesOut.resize(0); };
	protected:
		uint id;
		unsigned char numberOfNodeSets;
		uint nodeSetId;
	
	};


} /* namespace FEMProject */
