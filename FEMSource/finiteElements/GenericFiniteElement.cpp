/*
 * GenericFiniteElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#include <preprocessDefine.h>

#include <finiteElements/GenericFiniteElement.h>

#include <elementFormulations/GenericElementFormulation.h>

#include <equations/GeometryData.h>

#include <materials/Material.h>

#include <finiteElements/ElementTypes.h>


#include <Eigen/Dense>





namespace FEMProject {



	template<typename prec, typename uint>
	GenericFiniteElement<prec,uint>::GenericFiniteElement(){
		
		this->material = 0;
	}
	
	template<typename prec, typename uint>
	GenericFiniteElement<prec,uint>::~GenericFiniteElement(){
		
	}
	

	
	template<typename prec, typename uint>
	void GenericFiniteElement<prec, uint>::insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, 1, Eigen::Dynamic> &residual
		, std::vector<uint> &eqIds, std::vector<dofStatus> &eqStatus) {
	
	}
	

	template<typename prec, typename uint>
	void GenericFiniteElement<prec, uint>::GenericSetDegreesOfFreedom() {

		this->material->getElementFormulation()->setDegreesOfFreedom(this);
	}


	template<typename prec, typename uint>
	void GenericFiniteElement<prec, uint>::GenericSetTangentResidual(
		  Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
		, Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
		, std::vector<DegreeOfFreedom<prec,uint>*> &Dofs) {

		this->material->getElementFormulation()->setTangentResidual(this,stiffness,residual,Dofs);
	}

	template<typename prec, typename uint>
	void GenericFiniteElement<prec, uint>::GenericSetMass(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
	{
		this->material->getElementFormulation()->setMass(this, stiffness, residual, Dofs);
	}

} /* namespace FEMProject */

instantiate(GenericFiniteElement)
