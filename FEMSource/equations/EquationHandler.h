/*
 * EquationHandler.h
 *
 *  Created on: 05.08.2016
 *      Author: Klarmann
 */

#pragma once

#include <forwarddeclaration.h>

#include <vector>
#include <ostream>


namespace FEMProject {

	/**
	 * @class EquationHandler
	 * @brief Groups nodeSets and dofHandler for further management of the equation system.
	 */
	
	template<typename prec, typename uint>
	class EquationHandler {
	public:
		EquationHandler(PointerCollection<prec, uint> *ptrCol);
		~EquationHandler();
		uint requestNodeSets(const unsigned char &numberOfSets);
		NodeSet<prec, uint> *getSet(const uint &setCollectionIndex, const unsigned char &setNumber);
		NodeSet<prec, uint> *getSetMeshId(const uint &setCollectionIndex, const unsigned char &meshId);
		GenericNodes<prec, uint> *getNode(NodeSet<prec, uint> &nodeSet, const unsigned char &node);
		void getSets(std::vector<NodeSet<prec,uint>*> &nodeSets, const uint &setCollectionIndex, const unsigned char &setSize);
		void getNodes(std::vector<GenericNodes<prec, uint>*> &nodes, const uint &setCollectionIndex, const unsigned char &setNumber);
		void getNodes(std::vector<GenericNodes<prec, uint>*> &nodes, const NodeSet<prec,uint> &Nodeset);
		
		uint requestDegreesOfFreedom(const uint number);
		void getDegreesOfFreedom(const uint &indexpos, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		
		void update();
		void updateEquations();   // TODO
		void print(std::ostream &out);
	
		void initSolutionState();
		std::vector<DegreeOfFreedom<prec, uint>> *getDegreesOfFreedomList();

		std::vector<DegreeOfFreedom<prec, uint>>* getDofList() { return &this->degreesOfFreedom; };
	private:
		PointerCollection<prec, uint> *pointers;
	
		std::vector<uint> nodesetCompressedIndex;
		std::vector<NodeSet<prec,uint>> nodeSetList;
		uint currNodeSets;
	
	
		uint currNodes;
		std::vector<uint> nodesIndex;
		std::vector<GenericNodes<prec,uint>> nodes;
	
		
		std::vector<DegreeOfFreedom<prec, uint>> degreesOfFreedom;
		uint activeIds;
		uint inActiveIds;
		uint totalIds;
	
	
	};

} /* namespace FEMProject */

