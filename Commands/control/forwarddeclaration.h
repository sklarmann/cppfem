#pragma once

namespace FEMProject {


	//-----------------control-------------------------------------------------
	template<typename prec, typename uint>
	class FEMProgram;
	struct InfoData;
	class OutputHandler;
	class stringCommandHandler;
	template<typename prec>
	class Timer;
		//-----------------commands------------------------------------------------
	namespace Commands {
		template<typename prec, typename uint>
		class InputParser;
		template<typename prec, typename uint>
		class GenericCommand;
	}


	//-----------------elementFormulations-----------------------------------
	template<typename prec, typename uint>
	class ElementFormulation201;
	template<typename prec, typename uint>
	class GenericElementFormulation;

	//-----------------equations-----------------------------------------------
	template<typename prec, typename uint>
	class DegreeOfFreedom;
	template<typename prec, typename uint>
	class EquationHandler;
	template<typename prec, typename uint>
	class GenericNodes;
	template<typename prec, typename uint>
	class GeometryData;
	template<typename prec, typename uint>
	class NodeSet;


	//-----------------finiteElements------------------------------------------
	template<typename prec, typename uint>
	class ElementList;
	template<typename prec, typename uint>
	class GenericFiniteElement;
	template<typename prec, typename uint>
	class LinearTriangleElement;
	template<typename prec, typename uint>
	class QuadrilateralNodal;


	//-----------------geometry------------------------------------------------
	template<typename prec, typename uint>
	class LinearEdge;
	template<typename prec, typename uint>
	class GenericGeometryElement;
	template<typename prec, typename uint>
	class LinearBrick;
	template<typename prec, typename uint>
	class LinearQuadrilateral;
	template<typename prec, typename uint>
	class LinearTriangle;
	template<typename prec, typename uint>
	class Vertex;

	//-----------------loads---------------------------------------------------
	template<typename prec, typename uint>
	class DofLoad;
	template<typename prec, typename uint>
	class GenericLoad;
	template<typename prec, typename uint>
	class loadList;
	template<typename prec, typename uint>
	class PropfunctionHandler;
	template<typename prec, typename uint>
	class Timefunction;

	//-----------------materials-----------------------------------------------
	template<typename prec, typename uint>
	class GenericMaterialFormulation;
	template<typename prec, typename uint>
	class Material;
	template<typename prec, typename uint>
	class MaterialFormulation1;
	template<typename prec, typename uint>
	class MaterialList;

	//-----------------math----------------------------------------------------
	template<typename prec, typename uint>
	class Plane;
	template<typename prec>
	class Userconstants;

	//-----------------plot----------------------------------------------------
	template<typename prec, typename uint>
	class vtkPlotInterface;

	//-----------------pointercollection---------------------------------------
	template<typename prec, typename uint>
	class PointerCollection;

	//-----------------solver--------------------------------------------------
	template<typename prec, typename uint>
	class EigenPardisoLDLT;
	template<typename prec, typename uint>
	class EigenPardisoLLT;
	template<typename prec, typename uint>
	class EigenPardisoLU;
	template<typename prec, typename uint>
	class EigenSimplicialLDLT;
	template<typename prec, typename uint>
	class EigenSimplicialLLT;
	template<typename prec, typename uint>
	class EigenSparseLU;
	template<typename prec, typename uint>
	class EigenSparseQR;
	template<typename prec, typename uint>
	class GenericSolutionState;
	template<typename prec, typename uint>
	class GenericSolver;
	template<typename prec, typename uint>
	class StaticSolutionState;

}
