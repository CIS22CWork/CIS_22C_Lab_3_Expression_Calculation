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
ExpressionString::ExpressionString (void) {}

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
// 
// Math Operators :
// + || Addition
// - || Subtraction
// * || Multiplication
// / || Division
// % || Modulus
// ^ || Power
// $ || Square Root
// s || Sine
// c || Cosine
// t || Tangent
// ~ || Negative Number
//******************************************************
string ExpressionString::InfixToPostfix (string expression)
{
	// Declaring a Stack from Standard template library in C++. 
	Stack<string> S;
	string postfix = ""; // Initialize postfix as empty string.
	string entity = "";
	bool operand = false;
	bool operandContinue = false;
	unsigned int i;
	unsigned int j;
	unsigned int n = (unsigned int)expression.length ();
	// stack test output
	stringstream stackoutput;
	cout << setw (5) << left << "step" << setw (7) << "symbol" << setw (6) << "stack" << setw (8) << "postfix" << endl;
	for (i = 0, j = 1; i < n; i++)
	{
		// Instructions from http://csis.pace.edu/~wolf/CS122/infix-postfix.htm
		// Scanning each character from left. If character is a delimitter, move on. 
		if (expression[i] == ' ' || expression[i] == ',') continue;
		// If this and next character are numbers or a '.' then combine them
		isOperand (expression[i]) ? operand = true : operand = false;
		if (i + 1 < n && isNumeric (expression[i]) && isNumeric (expression[i + 1]))
		{
			operandContinue = true;
			entity += expression[i];
			continue;
		}
		if(operandContinue) entity += expression[i];
		if (entity == "") entity = expression[i];
		// Print operands as they arrive.
		if (operand) postfix += entity + " ";
		// 	If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
		else if (S.empty () || S.top () == "(") S.push (entity);
		// 	If the incoming symbol is a left parenthesis, push it on the stack.
		else if (entity == "(") S.push (entity);
		// 	If the incoming symbol is a right parenthesis, pop the stack and print the operators until you see a left parenthesis. Discard the pair of parentheses.
		else if (entity == ")")
		{
			while (!S.empty () && S.top () != "(")
			{
				postfix += S.top () + " ";
				S.pop ();
			}
			S.pop ();
		}
		// If the incoming symbol has higher precedence than the top of the stack, push it on the stack.
		else if (!S.empty () && operatorWeight (S.top ()) < operatorWeight (entity)) S.push (entity);
		// If the incoming symbol has equal precedence with the top of the stack, use association. 
		// If the association is left to right, pop and print the top of the stack and then push the incoming operator. 
		// If the association is right to left, push the incoming operator.
		else if (!S.empty () && operatorWeight (S.top ()) == operatorWeight (entity))
		{
			postfix += S.top () + " ";
			S.pop ();
			S.push (entity);
		}
		// If the incoming symbol has lower precedence than the symbol on the top of the stack, 
		// pop the stack and print the top operator. 
		// Then test the incoming operator against the new top of stack.
		else if (!S.empty () && operatorWeight (S.top ()) > operatorWeight (entity))
		{
			while (!S.empty () && operatorWeight (S.top ()) > operatorWeight (entity))
			{
				postfix += S.top () + " ";
				S.pop ();
			}
			S.push (entity);
		}
		// stack test results
		stackoutput << &S;
		cout << setw (5) << left << j << setw (7) << entity << setw (6) << stackoutput.str() << postfix << endl;
		stackoutput.str ("");
		// symbol clear and step increment
		entity = "";
		j++;
		operandContinue = false;
	}
	// At the end of the expression, pop and print all operators on the stack. 
	// (No parentheses should remain.)
	while (!S.empty ())
	{
		postfix += S.top () + " ";
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
bool ExpressionString::isOperand (char C)
{
	if (C >= '0' && C <= '9') return true;
	if (C >= 'a' && C <= 'z') return true;
	if (C >= 'A' && C <= 'Z') return true;
	return false;
}

//******************************************************
// ExpressionString::IsNumeric      
//
// returns true if character is numeric and false if not
//******************************************************
bool ExpressionString::isNumeric (char C)
{
	if (C >= '0' && C <= '9') return true;
	if (C == '.') return true;
	return false;
}

//******************************************************
// ExpressionString::IsOperand      
//
// Function to verify whether a character is operator symbol or not. 
//******************************************************
bool ExpressionString::isOperator (char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '%' || C == '^')
		return true;

	return false;
}

//******************************************************
// ExpressionString::GetOperatorWeight     
//
// returns the precedence "weight" for an operator 
//******************************************************
int ExpressionString::operatorWeight (string op)
{
	int weight = -1;
	if (op == "+") weight = 1;
	else if (op == "-") weight = 1;
	else if (op == "*") weight = 2;
	else if (op == "/") weight = 2;
	else if (op == "%") weight = 2;
	else if (op == "$") weight = 3;
	else if (op == "^") weight = 3;
	return weight;
}


//******************************************************
// operator<<        
//******************************************************
template <class T>
std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr)
{
	// Since operator<< is a friend of the List class, we can access
	// it's members directly.
	int itemCount = 0;
	if (ListPtr->empty ()) cout << "List is empty" << endl;
	else
	{
		Node<T> *currPtr = ListPtr->getTail ();
		while (currPtr != nullptr)
		{
			itemCount++;
			foo << itemCount << ". " << currPtr->value << endl;
			currPtr = currPtr->next;
		}
	}
	return foo;
}
template <class T>
std::ostream& operator<< (std::ostream &foo, Stack<T> *ListPtr)
{
	int itemCount = 0;
	if (ListPtr->empty ()) cout << "" << endl;
	else
	{
		Node<T> *currPtr = ListPtr->getTail ();
		while (currPtr != nullptr)
		{
			itemCount++;
			//foo << itemCount << ". " << currPtr->value << endl;
			foo << currPtr->value;
			currPtr = currPtr->next;
		}
	}
	return foo;
}