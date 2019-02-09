/**
 * @file stringoperations.cpp
 *
 * @brief Contains functions for string operations
 *
 *  Created on: 14.07.2016
 *      Author: simon
 **/


#include <string>
#include <stack>
#include <vector>


namespace stringOperations{

	/**
	 * @brief Checks if char is parantheses
	 * @param in
	 * @return
	 */
	bool isParantheses(const char &in)
	{
		if(in == '(' || in == '{' || in == '[' || in == ')' || in == '}' || in == ']'){
			return true;
		}else{
			return false;
		}
	}
	
	/**
	 * @brief Checks if Open matches close parentheses
	 * @param open  Open bracket char
	 * @param close Current char to test
	 * @return Returns true if parentheses match
	 */
	bool AreParanthesesPair(const char &open,const char &close)
	{
		if(open=='(' && close == ')') return true;
		else if(open=='[' && close == ']') return true;
		else if(open=='{' && close == '}') return true;
		else return false;
	}
	
	/**
	 * @brief bool function to check if parentheses are balanced
	 * @param input input string to check
	 * @return bool true if balanced, false if not.
	 */
	bool checkBalancedParentheses(const std::string &input)
	{
		std::stack<char> parent;
		bool ret = false;
		for(size_t i = 0;i<input.size();++i)
		{
			if(input[i]=='(' || input[i] == '[' || input[i]=='{')
			{
				parent.push(input[i]);
			}else if(!parent.empty())
			{
				if(AreParanthesesPair(parent.top(),input[i]))
				{
					parent.pop();
				}
			}
		}
		if(parent.empty()) ret = true;
	
		return ret;
	}
	
	/**
	 * @brief Remove leading and trailing whitespaces of the input string
	 * @param input string to process
	 * @param whitespace whitespaces to remove, default " \t\n\v\f\r"
	 */
	void removeWhitespaces(std::string &input, const std::string &whitespace = " \t\n\v\f\r")
	{
		const auto strBegin = input.find_first_not_of(whitespace);
		if(strBegin!=std::string::npos)
		{
			input = input.substr(strBegin,input.size()-strBegin);
			const auto strEnd = input.find_last_not_of(whitespace);
			input = input.substr(0,strEnd+1);
		}else{
			input.clear();
		}
	}
	
	
	/**
	 * @brief Finds start and end position of outer matching parentheses
	 * @param start Output value of the opening position
	 * @param end   Output value of the closing position
	 * @param input Const string to parse
	 * @return Returns true if parentheses are found, else false.
	 */
	bool findParenthesesPositions(std::size_t &start, std::size_t &end, const std::string &input)
	{
		bool ret = false;
		std::stack<char> parent;
		std::string Sparent = "({[";
		start = input.find_first_of(Sparent);
		if(start!=std::string::npos)
		{
			parent.push(input[start]);
			size_t i = start + 1;
			while(!parent.empty())
			{
				if(input[i] == '(' || input[i] == '[' || input[i] == '{')
				{
					parent.push(input[i]);
				}else if(AreParanthesesPair(parent.top(),input[i]))
				{
					parent.pop();
				}
				++i;
			}
			end = i - 1;
			ret = true;
		}else{
			end = start;
		}
		return ret;
	}
	
	void removeComment(std::string &input, const std::string &Comment = "!")
	{
		std::size_t commentPos = input.find_first_of(Comment);
		if(commentPos!=std::string::npos) input = input.substr(0,commentPos);
	}
	
	
	void commaToArray(std::string &input, std::vector<std::string> &strArray) {
		std::string delimiter = ",";
		std::size_t pos = input.find(delimiter);
		while (pos!=std::string::npos)
		{
			strArray.push_back(input.substr(0, pos));
			input.erase(0, pos + 1);
			pos = input.find(delimiter);
		}
		pos = input.find(";");
		if (pos != std::string::npos) {
			strArray.push_back(input.substr(0, pos));
			input.erase(0, pos + 1);
		}
		removeWhitespaces(input);
		if (!input.empty()) {
			strArray.push_back(input);
			input.clear();
		}
	}

}
