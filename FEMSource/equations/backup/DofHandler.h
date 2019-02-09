/*
 * DofHandler.h
 *
 *  Created on: 05.08.2016
 *      Author: Klarmann
 */

#ifndef DOFHANDLER_H_
#define DOFHANDLER_H_

#define TEMPDOFHANDLER template<typename prec, typename uint>
#define CNAMEDOFHANDLER DofHandler<prec,uint>::

#include <vector>
#include <FEMExceptions.h>
#include <DofStatus.hpp>


namespace FEMProject {





/**
 * @brief Degree of Freedom Handler class.
 *
 */

TEMPDOFHANDLER
class DofHandler {
public:
	DofHandler();
	virtual ~DofHandler();
	uint requestEquationIds(unsigned char &num);
	void setInactive(const uint &StorageId, const unsigned char &dof);
	void setAllInactive(const uint &StorageId);
	void setDofInactive(const uint &StorageId, const unsigned char &dof);
	void setEquationsIds();
	void getEquationIdsOfNode(std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus, uint &node);
	uint getNumberOfEquations() { return this->numberOfEquations; };
	uint getNumberOfActiveEquations() { return this->numberOfActiveEquations; };
private:
	void checkStorageId(const uint &StorageId);
	void checkSetSize(const uint &StorageId, const unsigned char &dof);

	std::vector<uint> dofCompressedIndex;
	std::vector<uint> eqId;
	std::vector<dofStatus> eqStatus;
	uint numberOfEquations;
	uint numberOfActiveEquations;
	uint numberOfInActiveEquations;

};


template<typename prec, typename uint>
DofHandler<prec,uint>::DofHandler(){
	this->dofCompressedIndex.push_back(0);
	this->numberOfEquations         = 0;
	this->numberOfActiveEquations   = 0;
	this->numberOfInActiveEquations = 0;
}

template<typename prec, typename uint>
DofHandler<prec,uint>::~DofHandler(){

}

template <typename prec, typename uint>
void DofHandler<prec,uint>::checkStorageId(const uint &StorageId){
	if(StorageId>=this->dofCompressedIndex.size()-1){
		// TODO throw storage id out of range exception.
	}
}

template<typename prec, typename uint>
void DofHandler<prec,uint>::checkSetSize(const uint &StorageId, const unsigned char &dof){
	unsigned char setsize = static_cast<unsigned char>(this->dofCompressedIndex[StorageId+1]-this->dofCompressedIndex[StorageId]);
	if(dof>=setsize){
		//TODO throw dof out of range exception.
	}
}


/**
 * @brief Request num degrees of freedom, which equals the number of equations.
 * @param num The number of requested degrees of freedom
 * @return Storage id in the dofhandler.
 */
template<typename prec, typename uint>
uint DofHandler<prec,uint>::requestEquationIds(unsigned char &num){

	uint ret = static_cast<uint>(this->dofCompressedIndex.size())-1;
	this->dofCompressedIndex.emplace_back(this->dofCompressedIndex.back()+static_cast<uint> (num));
	for(auto i = 0;i<num;++i){
		this->eqId.emplace_back(0);
		this->eqStatus.emplace_back(dofStatus::active);
	}
	this->numberOfEquations       += num;
	this->numberOfActiveEquations += num;
	return ret;
}

/**
 * @brief Sets the equationId StorageId+dof to inactive, for example it adds an boundary condition.
 * @param StorageId The storage id of the dof set.
 * @param dof The degree of freedom in the set.
 */
template <typename prec, typename uint>
void DofHandler<prec,uint>::setInactive(const uint &StorageId,const unsigned char &dof){
	this->checkStorageId(StorageId);
	this->checkSetSize(StorageId,dof);
	switch(this->eqStatus[StorageId+dof]){

	case dofStatus::active :
		this->eqStatus[StorageId+dof] = dofStatus::inactive;
		++this->numberOfInActiveEquations;
		--this->numberOfActiveEquations;
		break;
	case dofStatus::inactive :
		break;
	}


}

template <typename prec, typename uint>
void DofHandler<prec,uint>::setAllInactive(const uint &StorageId){
	this->checkStorageId(StorageId);
	unsigned char setsize = static_cast<unsigned char>(this->dofCompressedIndex[StorageId+1]-this->dofCompressedIndex[StorageId]);
	for(auto i=0;i<setsize;++i){
		if (this->eqStatus[StorageId + i] == dofStatus::inactive) {
			this->eqStatus[StorageId + i] = dofStatus::active;
			--this->numberOfInActiveEquations;
			++this->numberOfActiveEquations;
		}
		
	}
}


template<typename prec, typename uint>
void DofHandler<prec, uint>::setDofInactive(const uint &StorageId, const unsigned char &dof) {
	//TODO bug
	this->checkStorageId(StorageId);
	this->checkSetSize(StorageId, dof);

	uint nodeId = this->dofCompressedIndex[StorageId];

	if(this->eqStatus[nodeId+dof]==dofStatus::active){
		this->eqStatus[nodeId + dof] = dofStatus::inactive;
		--this->numberOfActiveEquations;
		++this->numberOfInActiveEquations;
	}
}


template<typename prec, typename uint>
void DofHandler<prec, uint>::setEquationsIds() {
	uint aId = 0;
	uint pId = 0;

	for (uint i = 0; i < this->numberOfEquations; ++i) {
		if (this->eqStatus[i] == dofStatus::active) {
			this->eqId[i] = aId;
			++aId;
		}
		else if (this->eqStatus[i] == dofStatus::inactive) {
			this->eqId[i] = pId;
			++pId;
		}
	}
	if (this->numberOfActiveEquations != aId) {
		//TODO throw exception
		std::cout << "Number of active equations do not match !" << std::endl;
	}
	else if (this->numberOfInActiveEquations != pId) {
		//TODO throw exception
		std::cout << "Number of inactive equations do not match !" << std::endl;
	}
}


template<typename prec, typename uint>
void DofHandler<prec, uint>::getEquationIdsOfNode(std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus, uint &node) {
	if (node >= static_cast<uint>(this->dofCompressedIndex.size()) - 1) {
		//TODO throw exception
		std::cout << "No equations for this node in list" << std::endl;
	}
	uint size = this->dofCompressedIndex[node + 1] - this->dofCompressedIndex[node];
	uint pos = this->dofCompressedIndex[node];
	eqIds.resize(size);
	eqStatus.resize(size);

	for (uint i = 0; i < size; ++i) {
		eqIds[i] = this->eqId[pos + i];
		eqStatus[i] = this->eqStatus[pos + i];
	}
}


} /* namespace FEMProject */


#undef TEMPDOFHANDLER
#undef CNAMEDOFHANDLER

#endif /* DOFHANDLER_H_ */
