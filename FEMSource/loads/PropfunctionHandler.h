/*
 * PropfunctionHandler.h
 *
 *  Created on: 31.07.2016
 *      Author: simon
 */


#include <forwarddeclaration.h>



#include <string>
#include <vector>



namespace FEMProject {
	template<typename prec, typename uint>
	class PointerCollection;

	template <typename prec, typename uint>
	class PropfunctionHandler {
	public:
		PropfunctionHandler();
		~PropfunctionHandler();
		void setNames(PointerCollection<prec, uint> &pointers, std::string &timename, std::string &dtname);
		void addFunction(PointerCollection<prec, uint> &pointers, uint &num, std::string &function, prec &tmin, prec &tmax);
		void print(PointerCollection<prec, uint> &pointers);
		void setDt(PointerCollection<prec, uint> &pointers, std::string dtval);
		void incrTime(PointerCollection<prec, uint> &pointers);
		void update();
		prec getPropValue(PointerCollection<prec, uint> &pointers, uint propNum);
		prec getPropValueIncr(PointerCollection<prec, uint> &pointers, uint &propNum);
	private:
		std::vector<Timefunction<prec,uint>> timefunctions;
		std::string timename, dtname;
		uint numtime;
	};
} /* namespace FEMProject */
