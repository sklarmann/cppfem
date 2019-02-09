/*
 * NodeSet.h
 *
 *  Created on: 05.08.2016
 *      Author: simon
 */


#include <preprocessDefine.h>

#include <equations/NodeSet.h>

#include <equations/GenericNodes.h>
#include <equations/EquationHandler.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>
#include <control/FEMExceptions.h>

#include <iomanip>

namespace FEMProject {

	
	
	template<typename prec, typename uint>
	NodeSet<prec,uint>::NodeSet(){
		this->type     			= undef;
		this->numberOfNodes 	= 0;
		this->meshId 			= 0;
	}
	
	
	template<typename prec, typename uint>
	NodeSet<prec,uint>::~NodeSet(){
	
	}
	
	
	/**
	 * @brief Set the node type of the set.
	 * @param type Node type of the set
	 */
	template<typename prec, typename uint>
	void NodeSet<prec,uint>::setType(const NodeTypes &type){
		switch(this->type){
		case undef:
			this->type = type;
			break;
		default:
			if(this->type!=type){
				nodeSetSetTypeException except;
				throw except;
			}
		}
	}
	
	
	/**
	 * @brief Set the number of nodes in the set.
	 * @param numberOfNodes Number of nodes in the set.
	 */
	template<typename prec, typename uint>
	void NodeSet<prec,uint>::setNumberOfNodes(const uint &numberOfNodes){
	
		if(this->numberOfNodes==0||this->numberOfNodes==numberOfNodes){
			this->numberOfNodes = numberOfNodes;
		}else{
			nodeSetNumberOfNodesException except;
			throw except;
		}
	}

	template<typename prec, typename uint>
	inline void NodeSet<prec, uint>::print(PointerCollection<prec, uint> &pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::FullLog) <<
			std::left << std::setw(20) << "Nodeset meshId:" <<
			std::right << std::setw(10) << this->meshId <<
			std::left << std::setw(20) << "  Number of nodes:" <<
			std::right << std::setw(10) << this->numberOfNodes << "\n";

		std::vector<GenericNodes<prec, uint>*> nodes;
		pointers.getEquationHandler()->getNodes(nodes, (*this));
		for (auto i = 0; i < nodes.size(); ++i) {
			nodes[i]->print(pointers);
		}
	}


	template<typename prec, typename uint>
	void getNodes(std::vector<GenericNodes<prec, uint>*> &Nodes) {
		
	}


} /* namespace FEMProject */


instantiate(NodeSet)



