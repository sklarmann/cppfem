/*
 * NodeSet.h
 *
 *  Created on: 05.08.2016
 *      Author: simon
 */

#pragma once

#include <forwarddeclaration.h>

#include <equations/Nodetypes.h>
#include <vector>

namespace FEMProject {


	/**
	 * @class NodeSet
	 * @brief Nodeset groups  a set of nodes and is associated to a geometric element.
	 */
	template<typename prec, typename uint>
	class NodeSet {
	public:
		NodeSet();
		~NodeSet();
		void setType(const NodeTypes &type);
		void setMeshId(const uint &meshId) { this->meshId = meshId; };
		const uint &getMeshId() { return this->meshId; };
		void setNumberOfNodes(const uint &numberOfNodes);
		const uint &getNumberOfNodes() const {return this->numberOfNodes;};
		const NodeTypes &getNodeSetType() const {return this->type;};

		void setNodeStorageId(const uint &storageId) {this->nodeStorageId = storageId;};
		uint getNodeStorageStartId() const { return this->nodeStorageId; };


		void getNodes(std::vector<GenericNodes<prec, uint>*> &Nodes) {};

		void print(PointerCollection<prec, uint> &pointers);
	private:
		NodeTypes type;							/**< Node type of the set.  */
		uint meshId;					/**< Used for identification of the nodeSets in the preprocessing steps */
		uint numberOfNodes;			/**< Stores the number of nodes in the set. */
		uint dofsPerNode;
		uint nodeStorageId;						/**< Stores the Storage id of the nodes in the set. */
	};
	


} /* namespace FEMProject */




