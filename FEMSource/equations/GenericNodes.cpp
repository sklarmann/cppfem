/*
 * GenericNodes.h
 *
 *  Created on: 05.08.2016
 *      Author: simon
 */


#include <preprocessDefine.h>

#include <equations/GenericNodes.h>

#include <iostream>
#include <equations/Nodetypes.h>
#include <equations/DofStatus.h>
#include <equations/DegreeOfFreedom.h>
#include <equations/EquationHandler.h>

#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <pointercollection/pointercollection.h>

#include <iomanip>


namespace FEMProject {
	
	template<typename prec, typename uint>
	GenericNodes<prec,uint>::GenericNodes(){
		this->type = NodeTypes::undef;
	
	}
	
	template<typename prec, typename uint>
	GenericNodes<prec,uint>::~GenericNodes(){
		
	}
	
	template<typename prec, typename uint>
	void GenericNodes<prec,uint>::print(std::ostream &out){
		out << "Generic Node print! Id: " << this->nodeId << std::endl;
	}
	
	
	template<typename prec, typename uint>
	void GenericNodes<prec,uint>::requestEquationIds(PointerCollection<prec,uint> &pointers){
		this->dofStorageId = pointers.getEquationHandler()->requestDegreesOfFreedom(3);
	}
	
	template<typename prec, typename uint>
	void GenericNodes<prec, uint>::setBoundaryCondition(PointerCollection<prec, uint> &pointers, const unsigned char &dof) {
		if (dof >= 2) {
			//TODO throw exception
			std::cout << "dof exceeds number of degrees of freedom" << std::endl;
		}
		//(*(this->dofHandler))->setDofInactive(this->dofHandlerStorageId, dof);
		std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
		pointers.getEquationHandler()->getDegreesOfFreedom(this->dofStorageId,Dofs);
		Dofs[dof]->setStatus(dofStatus::inactive);
		
	}
	
	
	template<typename prec, typename uint>
	void GenericNodes<prec, uint>::getDegreesOfFreedom(PointerCollection<prec,uint> &pointers, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs) {
		
		pointers.getEquationHandler()->getDegreesOfFreedom(this->dofStorageId, Dofs);
		
	}

	template<typename prec, typename uint>
	inline void GenericNodes<prec, uint>::print(PointerCollection<prec, uint>& pointers)
	{
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::FullLog, LogLevel::BasicLog) <<
			std::left << std::setw(20) << "Node id:" <<
			std::right << std::setw(10) << this->nodeId << "\n";

		std::vector<DegreeOfFreedom<prec, uint>*> dofs(3);
		pointers.getEquationHandler()->getDegreesOfFreedom(this->dofStorageId, dofs);
		for (auto i = 0; i < dofs.size(); ++i) {
			dofs[i]->print(pointers);
		}
	}


} /* namespace FEMProject */

instantiate(GenericNodes)
