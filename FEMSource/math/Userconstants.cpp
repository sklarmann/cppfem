/*
 * Userconstants.h
 *
 *  Created on: 20.07.2016
 *      Author: simon
 */

#include <preprocessDefine.h>

#include <math/Userconstants.h>

#include <iomanip>

#include <stringoperations/stringoperations.h>
#include <iostream>
#include <fstream>

namespace FEMProject {
		
	template <typename prec>
	Userconstants<prec>::Userconstants() {
		// TODO Auto-generated constructor stub, adding more functions
	
		this->cons.clear();

		mathmap["sin"] = &sinWarp;
		mathmap["cos"] = &cosWarp;
		mathmap["tan"] = &tanWarp;
		mathmap["asin"] = &asinWarp;
		mathmap["acos"] = &acosWarp;
		mathmap["atan"] = &atanWarp;
		mathmap["sqrt"] = &sqrtWarp;
		mathmap["abs"] = &absWarp;
	
	}
	
	template <typename prec>
	Userconstants<prec>::~Userconstants() {
		// TODO Auto-generated destructor stub
	
	}
	
	
	template <typename prec>
	prec Userconstants<prec>::process(std::string &input)
	{
		if (!input.empty()) {
			if (stringOperations::checkBalancedParentheses(input))
			{
				std::size_t pos = input.find("=");
				prec retval;
				if (pos != std::string::npos) {
					std::string consadd = input.substr(0, pos);
					std::string toproc = input.substr(pos + 1, input.length() - pos - 1);
					stringOperations::removeWhitespaces(consadd);
					stringOperations::removeWhitespaces(toproc);
					retval = mathpm(toproc);
					this->cons[consadd] = retval;
				}
				else {
					stringOperations::removeWhitespaces(input);
					retval = mathpm(input);
				}
				return retval;
			}
			else
			{
				std::cout << "Error: Parantheses are not balanced, returning 0" << std::endl;
				return (prec)0;
			}
		}
		else
		{
			return (prec)0;
		}
	}
	
	
	
	/**
	 * @brief Seperates the input string into the next addition substraction
	 * @param input String to process
	 * @return Evaluation of the String as numeric value
	 */
	template <typename prec>
	prec Userconstants<prec>::mathpm(std::string &input)
	{
		prec retval = (prec) 0;
		std::size_t slen = input.length(), pos = 0;
	
		bool search = true;
		bool found  = false;
		std::stack<char> parent;
	
		while(pos<slen && search)
		{
			if(stringOperations::isParantheses(input[pos])){
				if(parent.empty()){
					parent.push(input[pos]);
				}else if(stringOperations::AreParanthesesPair(parent.top(),input[pos])){
					parent.pop();
				}else{
					parent.push(input[pos]);
				}
			}else if(parent.empty() && (input[pos] == '+' || input[pos] == '-') && pos!=0){
				if (input[pos - 1] == 'e' || input[pos - 1] == 'E') {
					std::size_t pos2 = pos - 2;
					if (pos2 >= 0) {
						std::string test;
						test = input[pos2];
						std::stringstream ss(test);
						std::string check;
						bool isNum = true;

						try {
							ss >> retval >> check;
						}
						catch (const std::exception) {
							check = input;
							isNum = false;
							//std::cout << e.what();
						}
						if(!isNum){
							search = false;
							found = true;
						}
					}
					else {
						search = false;
						found = true;
					}
				}
				else {
					search = false;
					found = true;
				}
			}
			++pos;
		}
		--pos;
	
	
		if(found){
			std::string firstval = input.substr(0,pos), secondval = input.substr(pos+1,input.length()-pos-1);
			stringOperations::removeWhitespaces(firstval);
			stringOperations::removeWhitespaces(secondval);
	
	
			if(firstval[0] == '-'){
				firstval.erase(0,1);
				retval -= mathmul(firstval);
			}else if(firstval[0]=='+'){
				firstval.erase(0,1);
				retval += mathmul(firstval);
			}else{
				retval += mathmul(firstval);
			}
	
			if(input[pos] == '+'){
				retval += mathpm(secondval);
			}else{
				retval -= mathpm(secondval);
			}
		} else {
			retval = mathmul(input);
		}
	
	
	
	
	
		return retval;
	}
	
	
	template <typename prec>
	prec Userconstants<prec>::mathmul(std::string &input)
	{
		prec retval = (prec) 0;
		std::size_t slen = input.length(), pos = input.length();
	
		bool search = true;
		bool found  = false;
		std::stack<char> parent;
	
		while(pos>0 && search)
		{
			--pos;
			if(stringOperations::isParantheses(input[pos])){
				if(parent.empty()){
					parent.push(input[pos]);
				}else if(stringOperations::AreParanthesesPair(input[pos], parent.top())){
					parent.pop();
				}else{
					parent.push(input[pos]);
				}
			}else if(parent.empty() && (input[pos] == '*' || input[pos] == '/')){
				search = false;
				found  = true;
			}
		}
	
	
	
		if(found){
			std::string firstval = input.substr(0,pos), secondval = input.substr(pos+1,input.length()-pos-1);
			stringOperations::removeWhitespaces(firstval);
			stringOperations::removeWhitespaces(secondval);
	
	
	
			if(input[pos] == '*'){
				prec fval = mathpm(firstval);
				prec sval = mathexp(secondval);
				retval = fval*sval;
			}else{
				prec fval = mathpm(firstval);
				prec sval = mathexp(secondval);
				retval = fval/sval;
			}
		} else {
			retval = mathexp(input);
		}
	
		return retval;
	}
	
	
	template <typename prec>
	prec Userconstants<prec>::mathexp(std::string &input)
	{
		prec retval = (prec) 1;
	
		std::size_t slen = input.length(), pos = 0;
	
		bool search = true;
		bool found  = false;
		std::stack<char> parent;
	
		while(pos<slen && search)
		{
			if(stringOperations::isParantheses(input[pos])){
				if(parent.empty()){
					parent.push(input[pos]);
				}else if(stringOperations::AreParanthesesPair(parent.top(),input[pos])){
					parent.pop();
				}else{
					parent.push(input[pos]);
				}
			}else if(parent.empty() && input[pos] == '^'){
				search = false;
				found  = true;
			}
			++pos;
		}
		--pos;
	
		if(found){
			std::string firstval = input.substr(0,pos), secondval = input.substr(pos+1,input.length()-pos-1);
			stringOperations::removeWhitespaces(firstval);
			stringOperations::removeWhitespaces(secondval);
			retval = pow(mathfun(firstval),mathfun(secondval));
		}else{
			retval = mathfun(input);
		}
	
	
		return retval;
	}
	
	
	template <typename prec>
	prec Userconstants<prec>::mathfun(std::string &input)
	{
		prec retval = (prec) 0;
	
	
		std::size_t pos1, pos2;
	
		stringOperations::findParenthesesPositions(pos1,pos2,input);
	
		if(pos1!=std::string::npos){
			std::string fun, arg;
			arg = input.substr(pos1+1,pos2-pos1-1);
			stringOperations::removeWhitespaces(arg);
			if(pos1 > 0){
				fun = input.substr(0,pos1);
				stringOperations::removeWhitespaces(fun);
				typename std::map<std::string,FuncPtr>::iterator it;
				it = mathmap.find(fun);
	
				if(it != mathmap.end()){
					prec argval = mathpm(arg);
	//				cout << arg << endl;
					retval = it->second(argval);
				}else{
					std::cout << "Function " << fun << " unknown!" << std::endl;
				}
			}else{
				retval = mathpm(arg);
			}
	
		}else{
			retval = matheval(input);
		}
	
	
	
		return retval;
	}
	
	template <typename prec>
	prec Userconstants<prec>::matheval(std::string &input)
	{
		prec retval = (prec) 0;
	
		std::string toproc = "0"+input;
		if(!input.empty()) toproc = input;
	
		std::stringstream ss(toproc);
		std::string check;
	
		try {
			ss >> retval >> check;
		}
		catch (const std::exception) {
			check = input;
			//std::cout << e.what();
		}

		if (input.size() == 1 && input.find_first_not_of("+-1234567890") != std::string::npos) check = input;

		auto pos = input.find_first_not_of("+-1234567890");
		if (input.size() == 1 && pos != std::string::npos) {
			check = input;
		}
		else if (pos == 0) {
			check = input;
		}

		//if (input[0] == 'e' || input[0] == 'd' ) check = input;
		
	//	cout << setprecision(64) << retval;
	
		if(!check.empty())
		{
			typename std::map<std::string,prec>::iterator it = cons.find(input);
	
			if(it!=cons.end())
			{
				retval = it->second;
			}else{
				retval = (prec) 0;
			}
	
		}
	
		
		return retval;
	}
	
	template <typename prec>
	void Userconstants<prec>::allToFile(std::string &file){
        std::ifstream iFile;
        std::ofstream oFile;
        bool exists = false;
        bool hasContent = false;
        
        iFile.open(file);
        if(iFile.is_open()){
            exists = true;
            int numLines = 0;
            while(!iFile.eof()){
                std::string line;
                getline(iFile,line);
                numLines++;
            }
            if(numLines>1) hasContent = true;
            iFile.close();
        }
            
        oFile.open(file,std::ofstream::app);
        if(oFile.is_open()){
			auto digi = std::numeric_limits<prec>::digits10;
			//std::cout << digi << std::endl;
            if(!exists || !hasContent){
                auto it = this->cons.begin();
                while(it != this->cons.end()){
                    oFile << it->first << ",";
                    ++it;
                }
                oFile << std::endl;
            }
			oFile << std::setprecision(digi) << std::scientific;
            auto it = this->cons.begin();
            while(it != this->cons.end()){
                oFile << it->second << ",";
                ++it;
            }
            oFile << std::endl;
            
            oFile.close();
        } else {
            std::cout << "Failed to open file " << file << std::endl;
        }
        
        
    }



} /* namespace FEMProject */

instantiatePrec(Userconstants)
