#include <preprocessDefine.h>
#include <solver/TransientSolutionNewmark.h>

#include <pointercollection/pointercollection.h>
namespace FEMProject {

	template<typename prec, typename uint>
	TransientSolutionNewmark<prec, uint>::TransientSolutionNewmark(PointerCollection<prec, uint> *pointers) : GenericSolutionState<prec, uint>(pointers) {


	}

	template<typename prec, typename uint>
	TransientSolutionNewmark<prec, uint>::~TransientSolutionNewmark() {
		
	}


	template<typename prec, typename uint>
	void TransientSolutionNewmark<prec, uint>::setValues(std::map<std::string, prec> &values) {
		std::map<std::string, prec>::iterator it;
		it = values.find("beta");
		if (it != values.end()) {
			this->beta = it->second;
		}
		else {
			this->beta = (prec)1 / (prec)4;
		}
		it = values.find("gamma");
		if (it != values.end()) {
			this->gamma = it->second;
		}
		else {
			this->gamma = (prec)1 / (prec)2;
		}
	}

}


instantiate(TransientSolutionNewmark)