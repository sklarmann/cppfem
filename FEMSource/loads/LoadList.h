

#pragma once

#include <preprocessDefine.h>
#include <forwarddeclaration.h>

#include <map>
#include <vector>

namespace FEMProject {


	template <typename prec, typename uint>
	class loadList {
	public:
		loadList(PointerCollection<prec, uint> *pointerCol);
		~loadList();
		void setLoad(uint propNum, uint Dof, prec loadValue, bool add);
		prec getLoad(uint Dof);
		prec getLoadIncr(uint Dof);
		void computeLoads(PointerCollection<prec, uint> &pointers, std::vector<uint> &ids, std::vector<prec> &loads, std::vector<prec> &loadincs);
	private:
		PointerCollection<prec, uint> *pointers;
		std::map <uint,std::map<uint,prec>> loads; // contains propfunction number, dofId and value
	};
}

instantiateHeader(loadList)
