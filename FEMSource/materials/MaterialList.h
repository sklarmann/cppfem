/*
 * MaterialList.h
 *
 *  Created on: 17.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <vector>

namespace FEMProject{
	template<typename prec, typename uint>
	class MaterialList{
	public:
		MaterialList(PointerCollection<prec, uint> *ptrCol);
		~MaterialList();
		Material<prec,uint> *getMaterial(const uint &number);
		uint getNumberOfMaterials() { return static_cast<uint>(this->list.size()); };
	
	private:
		std::vector<Material<prec,uint>*> list;
		PointerCollection<prec, uint> *ptrCol;
	};

}
