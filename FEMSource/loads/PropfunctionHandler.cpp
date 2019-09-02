/*
 * PropfunctionHandler.h
 *
 *  Created on: 31.07.2016
 *      Author: simon
 */

#include <preprocessDefine.h>

#include <loads/PropfunctionHandler.h>

#include <loads/Timefunction.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

namespace FEMProject {
		
	template <typename prec, typename uint>
	PropfunctionHandler<prec,uint>::PropfunctionHandler(){
		numtime = 0;
	};
	
	template <typename prec, typename uint>
	PropfunctionHandler<prec,uint>::~PropfunctionHandler(){
	
	}
	
	template<typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::setNames(
		PointerCollection<prec, uint> &pointers,
		std::string &timename, std::string &dtname) {
		this->timename = timename;
		this->dtname = dtname;
	
		std::string temp;
		temp = timename + "=0";
		
		pointers.getUserConstants()->process(temp);
		temp = dtname + "=0";
		pointers.getUserConstants()->process(temp);
	}
	
	template<typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::addFunction(
		PointerCollection<prec, uint> &pointers,
		uint &num, std::string &function, prec &tmin, prec &tmax) {
	
		std::size_t cnum = this->timefunctions.size();
	
		while (cnum < num+1) {
			this->timefunctions.emplace_back();
			++cnum;
		}
		this->numtime = static_cast<uint>(cnum);
		Timefunction<prec, uint> *temp;
		temp = &this->timefunctions[num];
		temp->set(function, tmin, tmax);
	
	}
	
	template <typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::print(PointerCollection<prec, uint> &pointers) {
		std::size_t num = this->timefunctions.size();
		Timefunction<prec, uint> *temp;
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::NoLog, LogLevel::NoLog) << "Time variable: " << this->timename << "=" << pointers.getUserConstants()->process(this->timename)
			<< " Time increment variable: " << this->dtname << "=" << pointers.getUserConstants()->process(this->dtname) << std::endl;
		Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;
		for (auto i = 0; i < num; ++i) {
			temp = &this->timefunctions[i];
			Log(LogLevel::NoLog, LogLevel::NoLog) << "Timefunction: " << i << std::endl;
			temp->print(pointers);
			Log(LogLevel::NoLog, LogLevel::NoLog) << std::endl;
		}
	}
	
	template <typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::setDt(
		PointerCollection<prec, uint> &pointers,
		std::string dtval) {
		std::string temp;
		temp = this->dtname + "=" + dtval;
		pointers.getUserConstants()->process(temp);
	}
	
	template <typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::incrTime(PointerCollection<prec, uint> &pointers) {
		std::string temp;
		temp = this->timename + "=" + this->timename + "+" + this->dtname;
		prec timetemp = pointers.getUserConstants()->process(temp);
		std::size_t num = this->timefunctions.size();
		Timefunction<prec, uint> *tempfun;
		for (auto i = 0; i < num; ++i) {
			tempfun = &this->timefunctions[i];
			tempfun->timeIncr(timetemp);
		}
	}

	template<typename prec, typename uint>
	prec PropfunctionHandler<prec, uint>::getPropValue(PointerCollection<prec, uint> &pointers, uint propNum) {
		
		if (propNum < this->numtime) {
			Timefunction<prec, uint> *temp;
			temp = &this->timefunctions[propNum];
			return temp->currLoad(pointers);
		}
		else {
			return 0;
		}
	}

	template<typename prec, typename uint>
	prec PropfunctionHandler<prec, uint>::getPropValueIncr(PointerCollection<prec,uint> &pointers, uint &propNum) {

		if (propNum < this->numtime) {
			Timefunction<prec, uint> *temp;
			temp = &this->timefunctions[propNum];
			return temp->dcurrLoad(pointers);
		}
		else {
			return 0;
		}
	}

	template<typename prec, typename uint>
	prec PropfunctionHandler<prec, uint>::getTime(PointerCollection<prec, uint>& pointers)
	{
		return pointers.getUserConstants()->process(this->timename);
	}

	template<typename prec, typename uint>
	void PropfunctionHandler<prec, uint>::update() {
		Timefunction<prec, uint> *tempfun;
		std::size_t num = this->timefunctions.size();
		for (auto i = 0; i < num; ++i) {
			tempfun = &this->timefunctions[i];
			tempfun->update();
		}
	}
} /* namespace FEMProject */

instantiate(PropfunctionHandler)