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
#include "ExpressionString.h"

using namespace std;

//******************************************************
// class constructor (no argument version)      
//******************************************************
ExpressionString::ExpressionString (void){}

//******************************************************
// class constructor    
//******************************************************
ExpressionString::ExpressionString (string expression)
{
	
}

//******************************************************
// class destructor  
//******************************************************
ExpressionString::~ExpressionString ()
{
	
}

//******************************************************
// InfixToPostfix       
//
// Function to evaluate Postfix expression and return output
//******************************************************
string ExpressionString::InfixToPostfix (string expression)
{
	// Declaring a Stack from Standard template library in C++. 
	Stack<char> S;
	string postfix = ""; // Initialize postfix as empty string.
	for (int i = 0; i< expression.length (); i++)
	{

		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		if (expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if (IsOperator (expression[i]))
		{
			while (!S.empty () && S.top () != '(' && HasHigherPrecedence (S.top (), expression[i]))
			{
				postfix += S.top ();
				S.pop ();
			}
			S.push (expression[i]);
		}
		// Else if character is an operand
		else if (IsOperand (expression[i]))
		{
			postfix += expression[i];
		}

		else if (expression[i] == '(')
		{
			S.push (expression[i]);
		}

		else if (expression[i] == ')')
		{
			while (!S.empty () && S.top () != '(')
			{
				postfix += S.top ();
				S.pop ();
			}
			S.pop ();
		}
		/*for (Stack<char> dump = S; !dump.empty (); dump.pop ())
			std::cout << dump.top ();
		cout << endl;*/
	}

	while (!S.empty ())
	{
		postfix += S.top ();
		S.pop ();
	}

	return postfix;
}

//******************************************************
// ExpressionString::IsOperand      
//
// Function to verify whether a character is english letter or numeric digit. 
// We are assuming in this solution that operand will be a single character
//******************************************************
bool ExpressionString::IsOperand (char C)
{
	if (C >= '0' && C <= '9') return true;
	if (C >= 'a' && C <= 'z') return true;
	if (C >= 'A' && C <= 'Z') return true;
	return false;
}

//******************************************************
// ExpressionString::IsOperand      
//
// Function to verify whether a character is operator symbol or not. 
//******************************************************
bool ExpressionString::IsOperator (char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$')
		return true;

	return false;
}

//******************************************************
// ExpressionString::IsRightAssociative      
//
// Function to verify whether an operator is right associative or not. 
//******************************************************
int ExpressionString::IsRightAssociative (char op)
{
	if (op == '$') return true;
	return false;
}

//******************************************************
// ExpressionString::GetOperatorWeight     
//
// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
//******************************************************
int ExpressionString::GetOperatorWeight (char op)
{
	int weight = -1;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	case '$':
		weight = 3;
	}
	return weight;
}

//******************************************************
// ExpressionString::GetOperatorWeight     
//
// Function to perform an operation and return output. 
//******************************************************
int ExpressionString::HasHigherPrecedence (char op1, char op2)
{
	int op1Weight = GetOperatorWeight (op1);
	int op2Weight = GetOperatorWeight (op2);

	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if (op1Weight == op2Weight)
	{
		if (IsRightAssociative (op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ? true : false;
}

//******************************************************
// operator<<        
//******************************************************
std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr)
{
	foo << "hey";
	return foo;
}