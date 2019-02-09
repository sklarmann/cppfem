

#pragma once


#include <forwarddeclaration.h>
#include <equations/DofStatus.h>

namespace FEMProject {

	template<typename prec, typename uint>
	class DegreeOfFreedom {
	public:
		DegreeOfFreedom();
		~DegreeOfFreedom() {};

		void setId(const uint &arg) { this->id = arg; };
		void setEqId(const uint &arg) { this->eqid = arg; };
		void setStatus(const dofStatus &status) { this->status = status; };
		uint getId() { return this->id; };
		uint getEqId() { return this->eqid; };
		dofStatus getStatus() { return this->status; };
		void print(PointerCollection<prec, uint> &pointers);

	private:
		uint id;
		uint eqid;
		dofStatus status;
	};

}
