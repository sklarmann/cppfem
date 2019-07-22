/*
 * Userconstants.h
 *
 *  Created on: 20.07.2016
 *      Author: simon
 */

#pragma once
#include <preprocessDefine.h>
#include <forwarddeclaration.h>

#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <cmath>
#include <typeinfo>


//instantiateHeaderPrec(Userconstants)


namespace FEMProject {


	template<typename prec>
	prec sinWarp(const prec &arg) { return sin(arg); };
	template<typename prec>
	prec cosWarp(const prec &arg) { return cos(arg); };
	template<typename prec>
	prec tanWarp(const prec &arg) { return tan(arg); };
	template<typename prec>
	prec sqrtWarp(const prec &arg) { return sqrt(arg); };



	template <typename prec>
	class Userconstants {
	public:
		Userconstants();
		virtual ~Userconstants();
		prec process(std::string &input);
		friend std::ostream &operator<< (std::ostream &out,const Userconstants<prec> &self)
		{
			if(!self.cons.empty()){
				typename std::map<std::string,prec>::const_iterator it = self.cons.begin();
	
				std::size_t strlen = 0;
	
				while(it!=self.cons.end())
				{
					if(it->first.length()>strlen) strlen = it->first.length();
					++it;
				}
				it = self.cons.begin();
				int oprec = 128;
				if(typeid(prec) == typeid(float)){
					oprec = 8;
				}else if(typeid(prec)==typeid(double)){
					oprec = 16;
				}
				while(it!=self.cons.end())
				{
					out << std::setw(strlen+2) << std::left << it->first << "=";
					out << std::setprecision(oprec) << std::right << it->second << std::endl;
					++it;
				}
			}
	
			return out;
		}
	private:
		prec mathpm(std::string &input);
		prec mathmul(std::string &input);
		prec mathexp(std::string &input);
		prec mathfun(std::string &input);
		prec matheval(std::string &input);
	
		typedef prec(*FuncPtr)(const prec&);
		std::map<std::string,prec> cons;
	
		std::map<std::string, FuncPtr> mathmap;
	
	};
	


} /* namespace FEMProject */
