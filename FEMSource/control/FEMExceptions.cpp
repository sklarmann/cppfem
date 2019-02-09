/*
 * FEMExceptions.h
 *
 *  Created on: 06.08.2016
 *      Author: Klarmann
 */

#ifndef FEMEXCEPTIONS_H_
#define FEMEXCEPTIONS_H_

#include <exception>


namespace FEMProject {

	class FEMExceptions : public std::exception {
	public:
		virtual const char* what() const throw(){
			return "Basic FEM Project Exception happened!";
		}
	};
	
	
	class dofHandlerGenericException : public FEMExceptions {
	public:
		virtual const char* what() const throw(){
			return "Basic Dof Handler Exception happend!";
		}
	};
	
	class dofHandlernewNodeSetException : public dofHandlerGenericException {
	public:
		virtual const char* what() const throw(){
			return "An Error happend when trying to add a new node set!";
		}
	};
	
	
	class nodeSetGenericException : public FEMExceptions {
	public:
		virtual const char* what() const throw(){
			return "Basic Node Set Exception happend!";
		}
	};
	
	class nodeSetSetTypeException : public nodeSetGenericException {
	public:
		virtual const char* what() const throw(){
			return "Error: Tried to change already set node type!";
		}
	};
	
	class nodeSetNumberOfNodesException : public nodeSetGenericException {
	public:
		virtual const char* what() const throw(){
			return "Error: Tried to change the number of nodes in the set!";
		}
	};

} /* namespace FEMProject */

#endif /* FEMEXCEPTIONS_H_ */
