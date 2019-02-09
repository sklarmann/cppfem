

#pragma once

namespace FEMProject {

	template<typename prec, typename uint>
	class DofLoad {
	public:
		DofLoad();
		~DofLoad();
		void setLoad(const prec &valueIn, const uint &dofNumber);
		//void getLoad(prec valueOut, uint dofNumber);
	private:
		prec value;
		uint dof;
	};

	template<typename prec, typename uint>
	DofLoad<prec, uint>::DofLoad() {
		this->value = 0;
	}


	template<typename prec, typename uint>
	DofLoad<prec, uint>::~DofLoad() {

	}

	template<typename prec, typename uint>
	void DofLoad<prec, uint>::setLoad(const prec &valueIn, const uint &dofNumber) {
		this->value = valueIn;
		this->dof = dofNumber;
	}

	//template<typename prec, typename uint>
	//DofLoad<prec, uint>::getLoad()
}
