

#include <preprocessDefine.h>

#include <loads/LoadList.h>


#include <pointercollection/pointercollection.h>
#include <loads/PropfunctionHandler.h>

namespace FEMProject {


	template<typename prec, typename uint>
	loadList<prec, uint>::loadList(PointerCollection<prec,uint> *pointerCol) {
		this->pointers = pointerCol;
	}

	template<typename prec, typename uint>
	loadList<prec, uint>::~loadList() {

	}

	template<typename prec, typename uint>
	void loadList<prec,uint>::setLoad(uint propNum, uint Dof, prec loadValue, bool add) {
		if (add) {
			if (this->loads.find(propNum) != this->loads.end()) {
				if (this->loads[propNum].find(Dof) != this->loads[propNum].end()) {
					this->loads[propNum][Dof] += loadValue;
				}
				else {
					this->loads[propNum][Dof] = loadValue;
				}
			}
			else {
				this->loads[propNum][Dof] = loadValue;
			}
		}
		else {
			this->loads[propNum][Dof] = loadValue;
		}
		
	}

	template<typename prec, typename uint>
	prec loadList<prec, uint>::getLoad(uint Dof) {
		typename std::map <uint, std::map<uint, prec>>::iterator it;
		typename std::map<uint, prec>::iterator it2;
		uint propnum;
		it = this->loads.begin();
		while (it != this->loads.end()) {
			propnum = it->first;
			it2 = it->second.find(Dof);
			if (it2 != it->second.end()) {
				return it2->second*this->pointers->getPropLoads()->getPropValue(*this->pointers,propnum);
			}
			++it;
		}
		return 0;
	}

	template<typename prec, typename uint>
	prec loadList<prec, uint>::getLoadIncr(uint Dof) {
		typename std::map <uint, std::map<uint, prec>>::iterator it;
		typename std::map<uint, prec>::iterator it2;
		uint propnum;
		it = this->loads.begin();
		while (it != this->loads.end()) {
			propnum = it->first;
			it2 = it->second.find(Dof);
			if (it2 != it->second.end()) {
				return it2->second*this->pointers->getPropLoads()->getPropValueIncr(*this->pointers,propnum);
			}
			++it;
		}
		return 0;
	}

	template<typename prec, typename uint>
	void loadList<prec, uint>::computeLoads(PointerCollection<prec, uint> &pointers, std::vector<uint> &ids, std::vector<prec> &loads, std::vector<prec> &loadincs) {
		
		ids.clear();
		loads.clear();
		loadincs.clear();
        typedef typename std::map <uint, std::map<uint, prec>>::iterator MapIterator1;
		MapIterator1 it1;
        typedef typename std::map<uint, prec>::iterator  MapIterator2;
		MapIterator2 it2;
		it1 = this->loads.begin();
		while (it1 != this->loads.end()) {
			uint propnum = it1->first;
			prec prop = this->pointers->getPropLoads()->getPropValue(pointers,propnum);
			prec dprop = this->pointers->getPropLoads()->getPropValueIncr(pointers,propnum);
			it2 = it1->second.begin();
			while (it2 != it1->second.end()) {
				ids.push_back(it2->first);
				loads.push_back(prop*it2->second);
				loadincs.push_back(dprop*it2->second);
				//loads[it2->first] += prop*it2->second;
				//loadincs[it2->first] += dprop*it2->second;
 				++it2;
			}
			++it1;
		}

	}

}

instantiate(loadList)
