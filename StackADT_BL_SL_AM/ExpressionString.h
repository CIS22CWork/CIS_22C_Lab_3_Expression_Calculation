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
#include "Queue.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>       /* pow */
#include <regex>

class ExpressionString
{
private:
	bool leftAssociative;
	std::string expressionInfix;
	std::string expressionPrefix;
	std::string expressionEval;
	Queue<std::string> expressionPostQ;
public:
	ExpressionString ();
	ExpressionString (std::string expression);
	~ExpressionString ();

	void setExpression (std::string expression);
	std::string getPostfix ();
	std::string infixToPostfix ();
	void evaluate ();
	void operatorEval (Stack<std::string> *S, std::string operate);
	bool isOperand (std::string str);
	bool isNumeric (char C);
	bool isOperator (char C);
	int operatorWeight (std::string op);

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr);
};

#endif