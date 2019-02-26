/*
 * stringCommandHandler.cpp
 *
 *  Created on: 15.07.2016
 *      Author: simon
 */

#include <control/stringCommandHandler.h>

#include <control/stringCommandHandler.h>
#include <stringoperations/stringoperations.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

namespace FEMProject {



	/**
	 * @brief Default constructor
	 */
	stringCommandHandler::stringCommandHandler() {
		// TODO Auto-generated constructor stub
		this->delim = ";";
	}
	
	/**
	 * @brief Default destructor
	 */
	stringCommandHandler::~stringCommandHandler() {
		// TODO Auto-generated destructor stub
	}
	
	/**
	 * @brief Set command string
	 * @param input string containing the commands
	 */
	void stringCommandHandler::operator=(const std::string &input)
	{
		Command = input;
		stringOperations::removeComment(Command);
		stringOperations::removeWhitespaces(Command);
	}

	
	/**
	 * @brief extending the command handler
	 * @param input string to append
	 */
	void stringCommandHandler::operator+=(const std::string &input)
	{
		std::string temp = input;
		stringOperations::removeComment(temp);
		stringOperations::removeWhitespaces(temp);
		Command += temp;
	}
	
	/**
	 * @brief Gets the next command and command parameter to process
	 * @param CommandOut Returns string with the next command to process
	 * @param passString Returns string with the corresponding command parameters
	 * @return Returns true if something to do, else false
	 */
	bool stringCommandHandler::processCommand(std::string &CommandOut, std::string &passString)
	{
		std::size_t start, end;
		bool ret = false;
		if(stringOperations::findParenthesesPositions(start, end, Command))
		{
			CommandOut = Command.substr(0,start);
			passString = Command.substr(start+1,end-start-1);
			Command    = Command.substr(end+1,Command.length()-end-1);
			stringOperations::removeWhitespaces(Command);
			stringOperations::removeWhitespaces(CommandOut);
			stringOperations::removeWhitespaces(passString);
			std::transform(CommandOut.begin(), CommandOut.end(), CommandOut.begin(), ::tolower);
			ret = true;
		}else if(!Command.empty())
		{
			CommandOut = Command;
			stringOperations::removeWhitespaces(CommandOut);
			Command.clear();
			std::transform(CommandOut.begin(), CommandOut.end(), CommandOut.begin(), ::tolower);
			ret = true;
		
		}
		return ret;
	}
	/**
	 * @brief Gets the next command and command parameter to process
	 * @param CommandOut Returns string with the next command to process
	 * @param passString Returns stringCommandHandler with the corresponding command parameters
	 * @return Returns true if something to do, else false
	 */
	bool stringCommandHandler::processCommand(std::string &CommandOut, stringCommandHandler &passString)
	{
		std::size_t start, end;
		bool ret = false;
		if(stringOperations::findParenthesesPositions(start, end, Command))
		{
			CommandOut = Command.substr(0,start);
			passString = Command.substr(start+1,end-start-1);
			Command    = Command.substr(end+1,Command.length()-end-1);
			stringOperations::removeWhitespaces(Command);
			stringOperations::removeWhitespaces(CommandOut);
			std::transform(CommandOut.begin(), CommandOut.end(), CommandOut.begin(), ::tolower);
			
			ret = true;
		}else if(!Command.empty())
		{
			CommandOut = Command;
			stringOperations::removeWhitespaces(CommandOut);
			Command.clear();
			std::transform(CommandOut.begin(), CommandOut.end(), CommandOut.begin(), ::tolower);
			ret = true;
		}
		return ret;
	}
	
	
	/**
	 * @brief Handles the user input.
	 * @param name String which is printed on the console.
	 */
	void stringCommandHandler::userInteraction(const std::string &name){
	
	
		bool read = true;
		std::string temp;
		std::size_t strpos;
		Command.erase();
		while(read){
			std::cout << name;
			std::getline(std::cin,temp);
			strpos = temp.find_first_of("!");
			if(strpos!=std::string::npos){
				temp.erase(temp.find_first_of('!'),std::string::npos);
			}
			Command += temp;
	
			if(stringOperations::checkBalancedParentheses(Command)) read = false;
	
	
		}
	}
	
	/**
	 * @brief Searches for the left hand side(lhs) expression and returns the right hand side(rhs) expression as a string.
	 * @param lhs The lhs to search for.
	 * @return Returns the rhs as a string
	 */
	std::string stringCommandHandler::getRhs(const std::string &lhs){
		std::string rhs;
		std::size_t pos1 = this->Command.find(lhs);
		std::size_t pos1e= pos1 + lhs.length();
		std::size_t pos2 = this->Command.find("=",pos1);
		std::size_t pos2e= this->Command.find_first_not_of(" \t\n\v\f\r",pos1e);
	
		if(pos2e==pos2 && pos2e != std::string::npos){
			std::size_t delimpos = this->Command.find_first_of(this->delim,pos1);
			rhs = this->Command.substr(pos2+1,delimpos-pos2-1);
			this->Command.erase(pos1,delimpos-pos1+1);
		}
	
		stringOperations::removeWhitespaces(rhs);
		return rhs;
	}
	
	std::vector<std::string> stringCommandHandler::getRhsArray(const std::string &lhs) {
		
	
		std::vector<std::string> strArray;
		std::string rhs;
		std::size_t pos1 = this->Command.find(lhs);
		std::size_t pos1e = pos1 + lhs.length();
		std::size_t pos2 = this->Command.find("=", pos1);
		std::size_t pos2e = this->Command.find_first_not_of(" \t\n\v\f\r", pos1e);
	
		if (pos2e == pos2) {
			std::size_t delimpos = this->Command.find_first_of(";", pos1);
			rhs = this->Command.substr(pos2 + 1, delimpos - pos2 - 1);
			stringOperations::commaToArray(rhs, strArray);
			this->Command.erase(pos1, delimpos - pos1 + 1);
		}
	
		
		for (std::vector<std::string>::iterator it = strArray.begin(); it != strArray.end(); ++it) {
			stringOperations::removeWhitespaces(*it);
		}
		
	
		return strArray;
	}
	
	std::string stringCommandHandler::getStringTillDelim() {
		std::size_t pos;
		std::string ret;
		pos = this->Command.find_first_of(this->delim);
		if (pos != std::string::npos) {
			ret = this->Command.substr(0, pos);
			this->Command = this->Command.substr(pos + 1, this->Command.length() - pos - 1);
	
		}
		else {
			ret = this->Command;
			this->Command.clear();
		}
		return ret;
	}
	
	
	
	
	bool stringCommandHandler::empty(){
		bool ret = false;
		if(this->Command.empty()) ret = true;
		
		return ret;
	}
	
	std::string stringCommandHandler::remainingCommands() {
		return this->Command;
	}
	
	void stringCommandHandler::errorReport(OutputHandler &Log, std::string command) {
	
		if (!this->empty()) {
			Log(LogLevel::BasicLog, LogLevel::BasicLog) << "Error in command " << command << ", unrecognized arguments:" << std::endl;
			Log(LogLevel::BasicLog, LogLevel::BasicLog) << this->Command << std::endl;
		}
	
	}


} /* namespace FEMProject */
