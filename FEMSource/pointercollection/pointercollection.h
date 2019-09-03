/*
 * GenericGeometryElement.h
 *
 *  Created on: 13.08.2016
 *      Author: klari
 */

#pragma once

#include <preprocessDefine.h>
#include <forwarddeclaration.h>
#include <plot/vtkplotClassBase.h>



namespace FEMProject {

	template <typename prec,typename uint>
	class PointerCollection {
	public:
		PointerCollection();
		~PointerCollection();

		void renew();
	
		void setGeometryData(GeometryData<prec, uint> *geoDataIn) { this->geometryData = geoDataIn; };
		GeometryData<prec, uint> *getGeometryData() { return this->geometryData; };
		void newGeometry();

		void setSolutionState(GenericSolutionState<prec, uint> *solutionStateIn) { this->solutionState = solutionStateIn; this->solutionState->setProps(); };
		GenericSolutionState<prec, uint> *getSolutionState() { return this->solutionState; };
		//void newSolutionState();

		void setEquationHandler(EquationHandler<prec, uint> *eqHandler) { this->eqHandler = eqHandler; };
		EquationHandler<prec, uint> *getEquationHandler() { return this->eqHandler; };
		void newEqHandler();

		void setElementList(ElementList<prec, uint> *elementList) { this->elementList = elementList; };
		ElementList<prec, uint> *getElementList() { return this->elementList; };
		void newElementList();

		void setMaterialList(MaterialList<prec, uint> *matList) { this->materialList = matList; };
		MaterialList<prec, uint> *getMaterialList() { return this->materialList; };
		void newMaterialList();

		//void setDofHandler(DofHandler<prec, uint> *dofHandler) { this->dofHandler = dofHandler; };
		//DofHandler<prec, uint> *getDofHandler() { return this->dofHandler; };
		//void newDofHandler();

		void setInfoData(InfoData *Info) { this->Info = Info; };
		InfoData *getInfoData() { return this->Info; };

		PropfunctionHandler<prec, uint> *getPropLoads(); 

		void newLoadList();
		loadList<prec, uint> *getLoadList() { return this->loads; };

		void newUserconstants();
		Userconstants<prec> *getUserConstants() { return this->ucons; };

		void newVtkPlot();
		vtkPlotInterfaceBase<prec,uint> *getVtkPlotInterface() { return this->vtkPlot; };
	private:
		GeometryData<prec, uint> *geometryData;
		GenericSolutionState<prec, uint> *solutionState;
		EquationHandler<prec, uint> *eqHandler;
		ElementList<prec, uint>  *elementList;
		MaterialList<prec, uint> *materialList;
		loadList<prec, uint> *loads;
		InfoData *Info;
		PropfunctionHandler<prec, uint> *props;
		Userconstants<prec> *ucons;
		vtkPlotInterfaceBase<prec, uint> *vtkPlot;
	};

} /* namespace FEMProject */

instantiateHeader(PointerCollection)
