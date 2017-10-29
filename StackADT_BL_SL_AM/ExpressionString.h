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

class ExpressionString
{
public:
	ExpressionString ();
	ExpressionString (std::string expression);
	~ExpressionString ();

	std::string InfixToPostfix (std::string expression);
	bool IsOperand (char C);
	bool IsOperator (char C);
	int IsRightAssociative (char op);
	int GetOperatorWeight (char op);
	int HasHigherPrecedence (char op1, char op2);

	//******************************************************
	// operator<<        
	//******************************************************
	friend std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr);
};

#endif