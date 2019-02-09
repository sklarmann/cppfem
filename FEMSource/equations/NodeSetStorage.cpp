/*
 * NodeSetStorage.h
 *
 *  Created on: 05.08.2016
 *      Author: simon
 */

#pragma once

#include <NodeSet.h>
#include <vector>
#include <DofHandler.h>

namespace FEMProject {

	template<typename prec, typename uint>
	class NodeSetStorage {
	public:
		NodeSetStorage(DofHandler<prec,uint> *dofHandler);
		~NodeSetStorage();
		void requestNodeSets(uint &first, const unsigned char &num);
		NodeSet<prec,uint> &getNodeSet(const uint &num);
		void setDofHandler(DofHandler<prec,uint> *dofHandlerin) {this->dofHandler = dofHandlerin;};
	private:
		std::vector<NodeSet<prec,uint>> nodeSets;
		DofHandler<prec,uint> *dofHandler;
	};
	
	
	template<typename prec, typename uint>
	NodeSetStorage<prec,uint>::NodeSetStorage(DofHandler<prec,uint> *dofHandler){
		this -> nodeSets.reserve(10000);
		this -> dofHandler = dofHandler;
	}
	
	
	template<typename prec, typename uint>
	NodeSetStorage<prec,uint>::~NodeSetStorage(){
		nodeSets.clear();
	}
	
	template<typename prec, typename uint>
	void NodeSetStorage<prec,uint>::requestNodeSets(uint &first, const unsigned char &num){
		first = this->nodeSets.size();
	
		for(auto i=0;i<num;++i){
			this->nodeSets.emplace_back(&this->dofHandler);
		}
	}
	
	template<typename prec, typename uint>
	NodeSet<prec,uint> &NodeSetStorage<prec,uint>::getNodeSet(const uint &num){
		if(num >= this->nodeSets.size()) {
			return 0;
		}
		return this->nodeSets.at(num);
	}



} /* namespace FEMProject */


