/*
 * GenericGeometryElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */


#include <preprocessDefine.h>

#include <pointercollection/pointercollection.h>

#include <equations/GeometryData.h>
#include <equations/EquationHandler.h>
#include <finiteElements/ElementList.h>
#include <materials/MaterialList.h>
#include <plot/vtkplotClass.h>

#include <solver/GenericSolutionState.h>
#include <solver/StaticSolutionState.h>


#include <control/HandlingStructs.h>
#include <loads/PropfunctionHandler.h>
#include <math/Userconstants.h>
#include <loads/LoadList.h>


namespace FEMProject {

	template<typename prec, typename uint>
	PointerCollection<prec, uint>::PointerCollection(){
		this->geometryData = 0;
		this->solutionState = 0;
		this->eqHandler = 0;
		this->elementList = 0;
		this->materialList = 0;
		this->props = 0;
		this->loads = 0;
		this->ucons = 0;
		this->vtkPlot = 0;
	}

	template<typename prec, typename uint>
	PointerCollection<prec, uint>::~PointerCollection() {
		if (this->geometryData != 0)delete this->geometryData;
		if (this->solutionState != 0)delete this->solutionState;
		if (this->eqHandler != 0)delete this->eqHandler;
		if (this->elementList != 0)delete this->elementList;
		if (this->materialList != 0)delete this->materialList;
		if (this->props != 0) delete this->props;
		if (this->loads != 0) delete this->loads;
		if (this->ucons != 0) delete this->ucons;
		if (this->vtkPlot != 0) delete this->vtkPlot;
	}

	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::renew()
	{
		if (this->geometryData != 0)delete this->geometryData;
		if (this->solutionState != 0)delete this->solutionState;
		if (this->eqHandler != 0)delete this->eqHandler;
		if (this->elementList != 0)delete this->elementList;
		if (this->materialList != 0)delete this->materialList;
		if (this->props != 0) delete this->props;
		if (this->loads != 0) delete this->loads;
		if (this->ucons != 0) delete this->ucons;
		if (this->vtkPlot != 0) delete this->vtkPlot;
		this->geometryData = 0;
		this->solutionState = 0;
		this->eqHandler = 0;
		this->elementList = 0;
		this->materialList = 0;
		this->props = 0;
		this->loads = 0;
		this->ucons = 0;
		this->vtkPlot = 0;
		this->newGeometry();
		this->newEqHandler();
		this->newElementList();
		this->newMaterialList();
		this->newLoadList();
		this->newUserconstants();
		this->newVtkPlot();
	}


	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newGeometry() {
		if (this->geometryData == 0) {
			this->geometryData = new GeometryData<prec, uint>(this);
		}
		else {

		}
		
	}

	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newEqHandler() {
		if (this->eqHandler == 0) {
			this->eqHandler = new EquationHandler<prec, uint>(this);
		}
		else {

		}

	}


	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newElementList() {
		if (this->elementList == 0) {
			this->elementList = new ElementList<prec, uint>(this);
		}
		else {

		}

	}

	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newMaterialList() {
		if (this->materialList == 0) {
			this->materialList = new MaterialList<prec, uint>(this);
		}
		else {

		}

	}

	//template<typename prec, typename uint>
	//void PointerCollection<prec, uint>::newSolutionState() {
	//	if (this->solutionState == 0) {
	//		this->solutionState = new StaticSolutionState<prec, uint>(this);
	//		this->solutionState->setProps();
	//	}
	//	else {
	//
	//	}
	//
	//}

	
	//template<typename prec, typename uint>
	//void PointerCollection<prec, uint>::newDofHandler() {
	//	if (this->dofHandler == 0) {
	//		this->dofHandler = new DofHandler<prec, uint>();
	//	}
	//	else {
	//
	//	}
	//
	//}


	template<typename prec, typename uint>
	PropfunctionHandler<prec, uint>* PointerCollection<prec, uint>::getPropLoads()
	{
		return this->solutionState->getProps();
	}

	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newLoadList() {
		if (this->loads == 0) {
			this->loads = new loadList<prec, uint>(this);
		}
	}


	template<typename prec, typename uint>
	void PointerCollection<prec, uint>::newUserconstants() {
		if (this->ucons == 0) {
			this->ucons = new Userconstants<prec>;
		}
	}

	template<typename prec, typename uint>
	inline void PointerCollection<prec, uint>::newVtkPlot()
	{
#ifdef USE_VTK



		if (this->vtkPlot == 0) {
			this->vtkPlot = new vtkPlotInterface<prec,uint>();
		}
#endif // USE_VTK
	}




} /* namespace FEMProject */


instantiate(PointerCollection)
