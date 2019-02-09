#ifndef POINTERCOLLECTIONBASE_HPP_
#define POINTERCOLLECTIONBASE_HPP_


namespace FEMProject {
	template <typename prec, typename uint>
	class PointerCollectionBase {
	public:
		PointerCollectionBase() {};
		virtual ~PointerCollectionBase() {};
		virtual InfoData *getInfoData() { std::cout << "Something wrong" << std::endl; return 0; };
	};


} /* End namespace */


#endif