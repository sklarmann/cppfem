
#pragma once

#include <preprocessDefine.h>
#include <forwarddeclaration.h>

class vtkUnstructuredGrid;
class vtkRenderer;

namespace FEMProject {


	template<typename prec, typename uint>
	class vtkPlotInterfaceBase {
	public: 
        virtual ~vtkPlotInterfaceBase() {};
		virtual void mesh(PointerCollection<prec, uint> &pointers) = 0;
		virtual void solution(PointerCollection<prec, uint> &pointers, uint &meshId, uint &comp) = 0;
		//virtual vtkRenderer *getRenderer() = 0;
		virtual vtkUnstructuredGrid *getGrid() = 0;
		virtual void interact() = 0;

	};



}

