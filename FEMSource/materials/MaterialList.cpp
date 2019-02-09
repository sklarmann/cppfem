/*
 * MaterialList.h
 *
 *  Created on: 17.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <materials/MaterialList.h>

#include <materials/Material.h>

namespace FEMProject{

	template<typename prec, typename uint>
	MaterialList<prec, uint>::MaterialList(PointerCollection<prec, uint> *ptrCol) {
		this->ptrCol = ptrCol;
	}

	
	template<typename prec, typename uint>
	MaterialList<prec,uint>::~MaterialList(){
		typename std::vector<Material<prec,uint>*>::iterator it;
		it = this->list.begin();
	
		while(it!=this->list.end()){
			delete *it;
			++it;
		}
	}
	
	
	template<typename prec, typename uint>
	Material<prec,uint> *MaterialList<prec,uint>::getMaterial(const uint &number){
		uint currSize = static_cast<uint>(this->list.size());
		if(number < currSize){
			return this->list[number];
		}else{
			for(auto i=currSize;i<number+1;++i){
				this->list.emplace_back();
				this->list.back() = new Material<prec, uint>(this->ptrCol);
			}
			return this->list[number];
		}
	}

}

instantiate(MaterialList)