/*
 * OutputHandler.h
 *
 *  Created on: 11.08.2016
 *      Author: klari
 */

#ifndef OUTPUTHANDLER_H_
#define OUTPUTHANDLER_H_

#include <iostream>
#include <fstream>

#include <iomanip>


namespace FEMProject {

	enum LogLevel  {NoLog = 0 , BasicLog = 1,FullLog = 2};
	
	class OutputHandler {
	public:
		OutputHandler(){
	
			Lfile = LogLevel::NoLog; Lconsole = LogLevel::NoLog;
			CLfile= LogLevel::NoLog; CLconsole= LogLevel::NoLog;
		};
		~OutputHandler(){};
		template<class T> OutputHandler &operator << (const T &bla){
	
			if(this->CLconsole >= this->Lconsole){
				std::cout << bla;
			}
	
			if(this->CLfile >= this->Lfile && this->LogFile.is_open()){
				this->LogFile << bla;
			}
	
			return *this;
		};
		OutputHandler &operator<<(std::ostream& (*pf) (std::ostream&)){
			if(this->CLconsole >= this->Lconsole){
				std::cout << pf;
			}
	
			if(this->CLfile >= this->Lfile && this->LogFile.is_open()){
				
				this->LogFile << pf;
			}
		    return *this;
		};
	
		OutputHandler &operator()(const LogLevel &Console, const LogLevel &File) {
	
			this->Lconsole = Console;
			this->Lfile = File;
	
			return *this;
		}
	
		OutputHandler  &loglevel(LogLevel File, LogLevel Console){
			this->Lconsole = Console;
			this->Lfile    = File;
			return *this;
		};
	
		void setLogLevel(LogLevel File, LogLevel Console){
			this->CLconsole = Console;
			this->CLfile    = File;
		}
	
		void openLogFile(const std::string &file){
			if (!this->LogFile.is_open()) {
				this->LogFile.open(file);
			}
			this->LogFile << std::setprecision(this->numberWidth) << std::scientific;
			std::cout << std::setprecision(this->numberWidth) << std::scientific;
			//else {
			//	this->LogFile.close();
			//	this->LogFile.open(file);
			//}
		}
	
		void closeLogFile() {
			if (this->LogFile.is_open()) {
				this->LogFile.close();
			}
		}

		void setPrecision(int num) {
			this->numberWidth = num;
			(*this)(LogLevel::NoLog, LogLevel::NoLog) << std::setprecision(num);
		}

		int getNumberWidth() { return this->numberWidth + 9; };
	
	protected:
		LogLevel Lfile, Lconsole;		// Outputloglevel
		LogLevel CLfile, CLconsole;		// Loglevel
		std::ofstream LogFile;
		int numberWidth = 6;

	};

} /* namespace FEMProject */

#endif /* OUTPUTHANDLER_H_ */
