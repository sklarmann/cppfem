/*
 * Timefunction.h
 *
 *  Created on: 30.07.2016
 *      Author: simon
 */

#include <preprocessDefine.h>

#include <loads/Timefunction.h>

#include <pointercollection/pointercollection.h>
#include <control/HandlingStructs.h>
#include <control/OutputHandler.h>

#include <math/Userconstants.h>

namespace FEMProject {
	
	
	template <typename prec, typename uint>
	Timefunction<prec,uint>::Timefunction(){
		this->isSet = false;
		this->calculated = false;
		this->propLoadold = static_cast<prec>(0);
		this->propLoadCurr = static_cast<prec>(0);
		this->ctime = static_cast<prec>(0);
	}
	
	template <typename prec, typename uint>
	Timefunction<prec,uint>::~Timefunction(){
	
	}
	
	
	
	template <typename prec, typename uint>
	void Timefunction<prec, uint>::calculate(PointerCollection<prec,uint> &pointers) {
		std::size_t num = this->functions.size();
		bool search = true;
		std::size_t i = 0;
		while (search && i < num) {
			if (this->ctime >= this->tmin[i] && this->ctime < this->tmax[i]) search = false;
			++i;
		}
		--i;
		if (search) {
			this->propLoadCurr = static_cast<prec>(0);
			this->calculated = true;
		}
		else {
			this->propLoadCurr = pointers.getUserConstants()->process(this->functions[i]);
			this->calculated = true;
		}
	}
	
	template <typename prec, typename uint>
	void Timefunction<prec,uint>::set(const std::string &ifunc
			, const prec &tmin, const prec &tmax){
	
		if (tmin > tmax) {
			// throw exception
		}
		std::size_t num = this->functions.size();
		for (auto i = 0; i < num; ++i) {
			if (tmin < this->tmax[i]) {
				//throw exception
			}
		}
		this->tmin.emplace_back(tmin);
		this->tmax.emplace_back(tmax);
		this->functions.emplace_back(ifunc);
		this->isSet = true;
	}
	
	
	template <typename prec, typename uint>
	prec Timefunction<prec,uint>::currLoad(PointerCollection<prec,uint> &pointers){
		if (!this->calculated) this->calculate(pointers);
		return this->propLoadCurr;
	}
	
	template <typename prec, typename uint>
	void Timefunction<prec,uint>::timeIncr(prec &ctime){
		this->ctime = ctime;
		this->calculated = false;
		this->propLoadold = this->propLoadCurr;
	}
	
	template <typename prec, typename uint>
	prec Timefunction<prec,uint>::dcurrLoad(PointerCollection<prec, uint> &pointers){
		if (!this->calculated) this->calculate(pointers);
		return this->propLoadCurr-this->propLoadold;
	}
	
	
	template <typename prec, typename uint>
	void Timefunction<prec, uint>::print(PointerCollection<prec, uint> &pointers) {
		std::size_t num = this->functions.size();
		OutputHandler &Log = pointers.getInfoData()->Log;
		Log(LogLevel::NoLog, LogLevel::NoLog) << "Current Load Level: " << std::setw(10) << this->currLoad(pointers) << " Current Load increment: " << this->dcurrLoad(pointers) << std::endl;
		for (auto i = 0; i < num; ++i) {
			Log(LogLevel::NoLog, LogLevel::NoLog) << "tmin: " << std::setw(10) << this->tmin[i]
				<< " tmax: " << std::setw(10) << this->tmax[i] << " function: " << this->functions[i] << std::endl;
		}
		
	}

	template<typename prec, typename uint>
	void Timefunction<prec, uint>::update() {
		this->propLoadold = this->propLoadCurr;
	}

} /* namespace FEMProject */

instantiate(Timefunction)