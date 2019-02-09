/*
 * Timefunction.h
 *
 *  Created on: 30.07.2016
 *      Author: simon
 */

#include <forwarddeclaration.h>

#include <string>
#include <vector>

namespace FEMProject {

	template <typename prec, typename uint>
	class Timefunction {
	public:
		Timefunction();
		~Timefunction();
		void set(const std::string &ifunc
				,const prec &tmin, const prec &tmax);
		prec currLoad(PointerCollection<prec, uint> &pointers);
		prec dcurrLoad(PointerCollection<prec, uint> &pointers);
		void timeIncr(prec &ctime);
		void print(PointerCollection<prec, uint> &pointers);
		void update();
	private:
		void calculate(PointerCollection<prec,uint> &pointers);
		bool isSet, calculated;
		std::vector<std::string> functions;
		std::vector<prec> tmin, tmax;
		prec propLoadCurr;
		prec propLoadold;
		prec ctime;
	};

} /* namespace FEMProject */

