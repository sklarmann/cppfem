/*
 * Material.h
 *
 *  Created on: 17.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <materials/Material.h>

#include <materials/MaterialFormulation1.h>
#include <elementFormulations/ElementFormulation201.h>
#include <elementFormulations/ElementFormulation2DGreenBeam.h>



namespace FEMProject {

	template<typename prec,typename uint>
	Material<prec,uint>::Material(PointerCollection<prec,uint> *ptrCol){
		this->materialFormulation = 0;
		this->elementFormulation = 0;
		this->ptrCol = ptrCol;
	}
	
	template<typename prec,typename uint>
	Material<prec,uint>::~Material(){
		if (this->materialFormulation != 0) delete this->materialFormulation;
		if (this->elementFormulation != 0) delete this->elementFormulation;
		this->ptrCol = 0;
	}
	
	
	template<typename prec, typename uint>
	void Material<prec,uint>::setElementForumaltion(const uint &elementFormulation) {
		if (this->elementFormulation == 0) {
			switch (elementFormulation) {

			case 101:
				this->elementFormulation = new ElementFormulation2DGreenBeam<prec, uint>(this->ptrCol);
				break;
			case 201:
				this->elementFormulation = new ElementFormulation201<prec, uint>(this->ptrCol);
				break;

			}
		}
	}


	template<typename prec, typename uint>
	void Material<prec, uint>::setMaterialFormulation(const uint &materialFormulation) {
		if (this->materialFormulation == 0) {
			switch (materialFormulation) {
			case 1:
				this->materialFormulation = new MaterialFormulation1<prec, uint>();
				break;
			}
		}
	}

	template<typename prec, typename uint>
	GenericMaterialFormulation<prec, uint>* Material<prec, uint>::getMaterialFormulation() {
		
		return this->materialFormulation;
	}


	template<typename prec, typename uint>
	GenericElementFormulation<prec, uint>* Material<prec, uint>::getElementFormulation() {
		return this->elementFormulation;
	}

} /* namespace FEMProject */

instantiate(Material)