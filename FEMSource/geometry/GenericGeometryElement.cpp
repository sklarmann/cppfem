/*
 * GenericGeometryElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <geometry/GenericGeometryElement.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>


#include <equations/NodeSet.h>
#include <equations/GenericNodes.h>
#include <equations/EquationHandler.h>

#include <iomanip>

namespace FEMProject {


	
	template<typename prec, typename uint>
	GenericGeometryElement<prec,uint>::GenericGeometryElement(){
		this->numberOfNodeSets = 0;
		this->nodeSetId = 0;
	}
	
	
	
	template<typename prec, typename uint>
	GenericGeometryElement<prec,uint>::~GenericGeometryElement(){

	}
	
	
	template<typename prec, typename uint>
	inline void GenericGeometryElement<prec, uint>::print(PointerCollection<prec, uint> &pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			"Generic geometry element call" 
			<< std::left << std::setw(20) << "\tId:"
			<< std::right << std::setw(10) << this->id << "\n"
			<< std::left << std::setw(20) << "\tNumber of nodesets:"
			<< std::right << std::setw(10) << this->numberOfNodeSets << std::endl;

	}

	template<typename prec, typename uint>
	inline void GenericGeometryElement<prec, uint>::printEqInfo(PointerCollection<prec, uint> &pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) 
			<< std::left << std::setw(20) << "\tId:"
			<< std::right << std::setw(10) << this->id << "\n"
			<< std::left << std::setw(20) << "\tNumber of nodesets:"
			<< std::right << std::setw(10) << static_cast<uint>(this->numberOfNodeSets) << std::endl;

		if (this->numberOfNodeSets > 0) {
			std::vector<NodeSet<prec, uint>*> sets;
			pointers.getEquationHandler()->getSets(sets, this->nodeSetId, this->numberOfNodeSets);
			for (auto i = 0; i < sets.size(); ++i) {
				sets[i]->print(pointers);
			}
		}
	}

	
	template<typename prec, typename uint>
	void GenericGeometryElement<prec,uint>::setNumberOfNodeSets(ptrCol &pointers, uint &numberOfSetsIn){
		if(this->numberOfNodeSets == 0){
			this->numberOfNodeSets = numberOfSetsIn;
			this->nodeSetId = pointers.getEquationHandler()->requestNodeSets(numberOfSetsIn);
		}else if(this->numberOfNodeSets!=numberOfSetsIn){
			//TODO throw exception
		}
	}
	
	template<typename prec,typename uint>
	NodeSet<prec,uint> *GenericGeometryElement<prec,uint>::getSet(ptrCol &pointers, uint &setNumber){
		if(setNumber>=this->numberOfNodeSets){
			//TODO throw exceptions
		}
		return pointers.getEquationHandler()->getSet(this->nodeSetId,setNumber);
	}
	
	template<typename prec,typename uint>
	void GenericGeometryElement<prec,uint>::getSets(ptrCol &pointers,std::vector<NodeSet<prec,uint>*> &sets){
		sets.clear();
		for(auto i=0;i<this->numberOfNodeSets;++i){
			sets.push_back(this->getSet(pointers,i));
		}
	}
	
	
	template <typename prec, typename uint>
	void GenericGeometryElement<prec, uint>::setAllNodeBoundaryConditionMeshId(ptrCol &pointers, const uint &meshId, const uint &dof) {
		EquationHandler<prec, uint> *temp;
		temp = pointers.getEquationHandler();
		NodeSet<prec, uint> *tempNodeSet;
		tempNodeSet = temp->getSetMeshId(this->nodeSetId, meshId);
	
		if (tempNodeSet != 0) {
			GenericNodes<prec, uint> *tempNode;
			for (auto i = 0; i < tempNodeSet->getNumberOfNodes(); ++i) {
				tempNode = temp->getNode(*tempNodeSet, i);
				tempNode->setBoundaryCondition(pointers, dof);
			}
		}
	
	}
	
	template <typename prec, typename uint>
	void GenericGeometryElement<prec, uint>::getNodesOfSet(ptrCol &pointers, std::vector<GenericNodes<prec, uint>*> &nodeVector, const uint &meshId) {
		//if (setNumber >= this->numberOfNodeSets) {
		//	//TODO throw exception
		//	std::cout << "Set not present!" << std::endl;
		//}
		NodeSet<prec, uint> *tempSet;
		tempSet = pointers.getEquationHandler()->getSetMeshId(this->nodeSetId, meshId);// ->getNodes(nodeVector);
		pointers.getEquationHandler()->getNodes(nodeVector, *tempSet);
	}
	
//	template<typename prec, typename uint>
//	void GenericGeometryElement<prec, uint>::getEquationsIds(std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus, const unsigned char &meshId) {
//		
//		unsigned char pos = 0;
//		bool search = true;
//		while (pos < this->numberOfNodeSets && search) {
//	
//			if (meshId == (*this->eqHandler)->getSet(this->nodeSetId, pos)->getMeshId()) {
//				search = false;
//			}
//			else {
//				++pos;
//			}
//		}
//	
//		unsigned char numNodes = (*this->eqHandler)->getSet(this->nodeSetId, pos)->getNumberOfNodes();
//		uint nodeStorageId = (*this->eqHandler)->getSet(this->nodeSetId, pos)->getNodeStorageStartId();
//		unsigned char dofsPerNode = (*this->eqHandler)->getNode((*(*this->eqHandler)->getSet(this->nodeSetId, pos)),0)->getDegreesOfFreedom();
//	
//		uint vecSize = static_cast<uint>(numNodes)*dofsPerNode;
//		eqIds.resize(vecSize);
//		eqStatus.resize(vecSize);
//	
//		std::vector<uint> eqTemp;
//		std::vector<dofStatus> statusTemp;
//	
//	
//	
//		for (auto i = 0; i < numNodes; ++i)
//		{
//			(*this->eqHandler)->getNode((*(*this->eqHandler)->getSet(this->nodeSetId, pos)), i)->getEquationIds(eqTemp, statusTemp);
//			for (auto j = 0; j < dofsPerNode; ++j) {
//				eqIds[i*dofsPerNode + j] = eqTemp[j];
//				eqStatus[i*dofsPerNode + j] = statusTemp[j];
//			}
//		}
//	
//	}
	
	template<typename prec, typename uint>
	void GenericGeometryElement<prec, uint>::getAllEquationsIds(ptrCol &pointers, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {
		Dofs.clear();
	
		EquationHandler<prec, uint> *tempEq = pointers.getEquationHandler();
		for (auto i = 0; i < this->numberOfNodeSets; ++i) {
			unsigned char numNodes = tempEq->getSet(this->nodeSetId, i)->getNumberOfNodes();
			for (unsigned char j = 0; j < numNodes; ++j) {
				std::vector<DegreeOfFreedom<prec, uint>*> tempDofs;
				tempEq->getNode((*(tempEq->getSet(this->nodeSetId, i))), j)->getDegreesOfFreedom(pointers,tempDofs);
				for (auto k = 0; k < tempDofs.size(); k++) {
					Dofs.push_back(tempDofs[k]);
				}
	
			}
		}
		
	}

	template<typename prec, typename uint>
	void GenericGeometryElement<prec,uint>::getNodeEquationIds(ptrCol &pointers, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs, const uint &meshId, const uint &nodeNumber) {
		NodeSet<prec,uint> *tempSet = this->getSetMeshId(pointers, meshId);
		auto numnodes = tempSet->getNumberOfNodes();
		if (nodeNumber <= numnodes) {
			GenericNodes<prec,uint> *tempnode = pointers.getEquationHandler()->getNode(*tempSet, nodeNumber);
			tempnode->getDegreesOfFreedom(pointers,Dofs);
		}


	}
	
	template<typename prec, typename uint>
	NodeSet<prec, uint> *GenericGeometryElement<prec, uint>::getSetMeshId(ptrCol &pointers, const uint &meshId) {
		NodeSet<prec, uint> *ret;
		if (this->numberOfNodeSets > 0) {
			auto *tempEq = pointers.getEquationHandler();
			ret = tempEq->getSetMeshId(this->nodeSetId, meshId);
		}
		else {
			ret = 0;
		}
		return ret;
	}
	
	
	template<typename prec, typename uint>
	bool GenericGeometryElement<prec, uint>::checkSetWithMeshId(ptrCol &pointers, const uint &meshId) {
		if (this->numberOfNodeSets > 0) {
			bool ret = false;
			unsigned char i = 0;
			NodeSet<prec, uint> *temp;
			while (i < this->numberOfNodeSets && !ret) {
				temp = pointers.getEquationHandler()->getSet(this->nodeSetId, i);
				if (meshId == temp->getMeshId()) ret = true;
				++i;
			}
	
			return ret;
		}
		else {
			return false;
		}
	}


} /* namespace FEMProject */


instantiate(GenericGeometryElement)