/*
 * Timer.h
 *
 *  Created on: 23.07.2016
 *      Author: Klarmann
 */

#pragma once

#include <chrono>
#include <iostream>

namespace FEMProject {

	typedef std::chrono::seconds sec;
	typedef std::chrono::milliseconds ms;
	
	template <typename timef>
	class Timer {
	public:
		Timer(){started = false; running=false; stopped=false;};
		~Timer(){};
		void start(){
			if(!running){
				t1 = std::chrono::steady_clock::now();
				started = true;
				running = true;
			}
		};
		void stop(){
			if(started){
				stopped = true;
				running = false;
				t2 = std::chrono::steady_clock::now();
			}
		}
		friend std::ostream &operator << (std::ostream &out, Timer<timef> &self)
		{
			if(self.started){
				if(self.running){
					std::chrono::steady_clock::time_point temp = std::chrono::steady_clock::now();
					std::chrono::duration<double> time_diff = std::chrono::duration_cast<std::chrono::duration<double>>(temp-self.t1);
					out << time_diff.count() << " seconds";
				}else{
					std::chrono::duration<double> time_diff = std::chrono::duration_cast<std::chrono::duration<double>>(self.t2-self.t1);
					out << time_diff.count() << " seconds";
				}
			}
			return out;
		}
	private:
		std::chrono::steady_clock::time_point t1, t2;
		bool started, running, stopped;
	
	};

} /* namespace FEMProject */


