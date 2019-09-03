/*
 * stringCommandHandler.h
 *
 *  Created on: 15.07.2016
 *      Author: simon
 */

#ifndef STRINGCOMMANDHANDLER_H_
#define STRINGCOMMANDHANDLER_H_

#include <string>
#include <control/OutputHandler.h>
#include <vector>
#include <map>

namespace FEMProject {


	class stringCommandHandler {
	public:
		stringCommandHandler();
		virtual ~stringCommandHandler();
		void operator=(const std::string &input);
		void operator+=(const std::string &input);
		bool empty();
		bool processCommand(std::string &CommandOut, std::string &passString);
		bool processCommand(std::string &CommandOut, stringCommandHandler &passString);
		void userInteraction(const std::string &name);
		std::string getRhs(const std::string &lhs);
		std::vector<std::string> getRhsArray(const std::string &lhs);
		std::string getStringTillDelim();
		std::string remainingCommands();
		void errorReport(OutputHandler &Log, std::string command);
		std::pair<std::string, std::string> getNextPair();
		
	private:
		std::string Command;
		std::string delim;
	};

} /* namespace FEMProject */

#endif /* STRINGCOMMANDHANDLER_H_ */
