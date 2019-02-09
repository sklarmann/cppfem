/*
 * GenericNodes.h
 *
 *  Created on: 05.08.2016
 *      Author: simon
 */

#pragma once

#include <forwarddeclaration.h>

#include <vector>
#include <equations/Nodetypes.h>
#include <ostream>


namespace FEMProject {
	template<typename prec, typename uint>
	class GenericNodes {
	public:
		GenericNodes();
		~GenericNodes();
		void print(std::ostream &out);
		void setId(const uint &nodeId) {this->nodeId = nodeId;};
		void initEqIds(){};
		void setBoundaryCondition(PointerCollection<prec,uint> &pointers, const unsigned char &dof);
		void requestEquationIds(PointerCollection<prec, uint> &pointers);
		void setNodeType(NodeTypes type) {this->type = type;};
		void getDegreesOfFreedom(PointerCollection<prec, uint> &pointers, std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
		//void setDegreesOfFreedom(unsigned char dofs) {this->numberOfDofs = dofs;};
		//unsigned char getDegreesOfFreedom() { return this->numberOfDofs; };
		void print(PointerCollection<prec, uint> &pointers);
	protected:
		NodeTypes type;
		uint nodeId;
		uint dofStorageId;
	};

} /* namespace FEMProject */
