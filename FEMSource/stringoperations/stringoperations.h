/**
 * @file stringoperations.h
 *
 *  Created on: 15.07.2016
 *      Author: simon
 **/

#ifndef STRINGOPERATIONS_H_
#define STRINGOPERATIONS_H_

#include <string>
#include <stack>
#include <vector>


namespace stringOperations{


bool isParantheses(const char &in);
bool AreParanthesesPair(const char &open,const char &close);
bool checkBalancedParentheses(const std::string &input);
bool findParenthesesPositions(std::size_t &start, std::size_t &end, const std::string &input);
void removeWhitespaces(std::string &input, const std::string &whitespace = " \t\n\v\f\r");
void removeComment(std::string &input, const std::string &Comment = "!");
void commaToArray(std::string &input, std::vector<std::string> &strArray);

}


#endif /* STRINGOPERATIONS_H_ */
