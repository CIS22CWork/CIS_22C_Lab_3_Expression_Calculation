/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 3

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
IF LIBRARYS ARE NOT FOUND, THEN SWITCH SDK VERSION
OR INSTALL THIS SDK VERSION

ExpressionString
Infix to Postfix conversion in C++ using stack.
We are assuming that both operators and operands in input will be single character.
*/

#ifndef EXPRESSIONSTRING_H
#define EXPRESSIONSTRING_H
#include "Stack.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class ExpressionString
{
private:
	bool leftAssociative;
public:
	ExpressionString ();
	ExpressionString (std::string expression);
	~ExpressionString ();

	std::string InfixToPostfix (std::string expression);
	bool isOperand (char C);
	bool isNumeric (char C);
	bool isOperator (char C);
	int operatorWeight (std::string op);

	//******************************************************
	// operator<<        
	//******************************************************
	//friend std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr);
};

#endif