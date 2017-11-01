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
Infix to Postfix conversion in C++ using stack and queue.

TESTED WITH THE FOLLOWING EXPRESSIONS:
1000-(57*23/5-(69-9*(1))%2)
-(-2--3/-1*-1)+2--3
-3%-2(-4--3/2)/-1
*/
#include "ExpressionString.h"

//******************************************************
// class constructor (no argument version)      
//******************************************************
ExpressionString::ExpressionString (void)
{
	expressionEval = 0;
	debugMode = false;
}

//******************************************************
// class constructor    
//******************************************************
ExpressionString::ExpressionString (std::string expression)
{

}

//******************************************************
// class destructor  
//******************************************************
ExpressionString::~ExpressionString ()
{

}

//******************************************************
// ExpressionString::IsNumeric      
//
// returns true if character is numeric and false if not
//******************************************************
void ExpressionString::setExpression (std::string expression)
{
	expressionInfix = expression;
}

//******************************************************
// ExpressionString::IsNumeric      
//
// returns true if character is numeric and false if not
//******************************************************
void ExpressionString::setDebug (bool flag)
{
	debugMode = flag;
}

/** getter for the calculated postfix string
@pre expressionPostQ required
@post None
@return postfix string delimited by spaces for readability */
std::string ExpressionString::getPostfix ()
{
	std::stringstream queueOutput;
	queueOutput << &expressionPostQ;
	return queueOutput.str ();
}

/** getter for the calculated prefix string
@pre expressionPreQ required
@post None
@return prefix string delimited by spaces for readability */
std::string ExpressionString::getPrefix ()
{
	std::stringstream queueOutput;
	queueOutput << &expressionPreQ;
	return queueOutput.str ();
}

//******************************************************
// ExpressionString::IsNumeric      
//
// returns true if character is numeric and false if not
//******************************************************
double ExpressionString::getEval ()
{
	return expressionEval;
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
@pre expressionInfixQ checks
@post expressionPostQ is populated
@param None
@return expressionPostQ as a string */
std::string ExpressionString::infixToPostfix ()
{
	expressionPostQ.clear ();
	Queue<std::string> infixQ;
	infixQ.copy (&expressionInfixQ);
	Stack<std::string> S;
	std::string entity = "";
	bool pushed;
	unsigned int i;
	unsigned int n = (unsigned int)infixQ.size ();
	std::stringstream queueOutput;
	std::stringstream stackOutput;
	// Test results for debugging. 
	if (debugMode)
		std::cout << std::setw (5) << std::left << "step" << std::setw (7) << "symbol" << std::setw (12) << "stack" << std::setw (8) << "postfix" << std::endl;
	for (i = 0; i < n; i++)
	{
		// Instructions from http://csis.pace.edu/~wolf/CS122/infix-postfix.htm
		entity = infixQ.back ();
		infixQ.pop ();
		// Print operands as they arrive.
		if (isOperand (entity)) expressionPostQ.push (entity);
		// 	If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
		else if (isOperator (entity) && (S.empty () || S.top () == "(")) S.push (entity);
		// 	If the incoming symbol is a left parenthesis, push it on the stack.
		else if (entity == "(") S.push (entity);
		// 	If the incoming symbol is a right parenthesis, pop the stack and print the operators until you see a left parenthesis. Discard the pair of parentheses.
		else if (entity == ")")
		{
			while (!S.empty () && S.top () != "(")
			{
				expressionPostQ.push (S.top ());
				S.pop ();
			}
			S.pop ();
		}
		else
		{
			pushed = false;
			if (!S.empty ())
			{
				while (!pushed)
				{
					// If the incoming symbol has higher precedence than the top of the stack, push it on the stack.
					if (operatorWeight (S.top ()) < operatorWeight (entity))
					{
						S.push (entity);
						pushed = true;
					}
					// If the incoming symbol has equal precedence with the top of the stack, use association. 
					// If the association is left to right, pop and print the top of the stack and then push the incoming operator. 
					// If the association is right to left, push the incoming operator.
					else if (operatorWeight (S.top ()) == operatorWeight (entity))
					{
						expressionPostQ.push (S.top ());
						S.pop ();
						S.push (entity);
						pushed = true;
					}
					// If the incoming symbol has lower precedence than the symbol on the top of the stack, 
					// pop the stack and print the top operator. 
					// Then test the incoming operator against the new top of stack.
					else if (!S.empty () && operatorWeight (S.top ()) > operatorWeight (entity))
					{
						expressionPostQ.push (S.top ());
						S.pop ();
					}
				}
			}
			else
			{
				S.push (entity);
			}
		}
		// Test results for debugging. stringstream keeps stream together for setw()
		if (debugMode)
		{
			stackOutput << &S;
			queueOutput << &expressionPostQ;
			std::cout << std::setw (5) << std::left << i + 1 << std::setw (7) << entity << std::setw (12) << stackOutput.str () << queueOutput.str () << std::endl;
			stackOutput.str ("");
			queueOutput.str ("");
		}
	}
	// At the end of the expression, pop and print all operators on the stack. 
	// (No parentheses should remain.)
	while (!S.empty ())
	{
		expressionPostQ.push (S.top ());
		S.pop ();
	}
	return getPostfix ();
}


/** converts expressionInfixQ Queue to expressionPostQ Queue
@pre expressionInfixQ checks
@post expressionPostQ is populated
@param None
@return expressionPostQ as a string */
std::string ExpressionString::infixToPrefix ()
{
	expressionPreQ.clear ();
	Queue<std::string> infixQ;
	infixQ.copy (&expressionInfixQ);
	Stack<std::string> S;
	std::string entity = "";
	bool pushed;
	unsigned int i;
	unsigned int n = (unsigned int)infixQ.size ();
	std::stringstream queueOutput;
	std::stringstream stackOutput;
	// Test results for debugging. 
	if (debugMode)
		std::cout << std::setw (5) << std::left << "step" << std::setw (7) << "symbol" << std::setw (12) << "stack" << std::setw (8) << "postfix" << std::endl;
	for (i = 0; i < n; i++)
	{
		// Instructions from http://csis.pace.edu/~wolf/CS122/infix-postfix.htm
		entity = infixQ.back ();
		infixQ.pop ();
		// Print operands as they arrive.
		if (isOperand (entity)) expressionPreQ.push (entity);
		// 	If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
		else if (isOperator (entity) && (S.empty () || S.top () == "(")) S.push (entity);
		// 	If the incoming symbol is a left parenthesis, push it on the stack.
		else if (entity == "(") S.push (entity);
		// 	If the incoming symbol is a right parenthesis, pop the stack and print the operators until you see a left parenthesis. Discard the pair of parentheses.
		else if (entity == ")")
		{
			while (!S.empty () && S.top () != "(")
			{
				expressionPreQ.push (S.top ());
				S.pop ();
			}
			S.pop ();
		}
		else
		{
			pushed = false;
			if (!S.empty ())
			{
				while (!pushed)
				{
					// If the incoming symbol has higher precedence than the top of the stack, push it on the stack.
					if (operatorWeight (S.top ()) < operatorWeight (entity))
					{
						S.push (entity);
						pushed = true;
					}
					// If the incoming symbol has equal precedence with the top of the stack, use association. 
					// If the association is left to right, pop and print the top of the stack and then push the incoming operator. 
					// If the association is right to left, push the incoming operator.
					else if (operatorWeight (S.top ()) == operatorWeight (entity))
					{
						expressionPreQ.push (S.top ());
						S.pop ();
						S.push (entity);
						pushed = true;
					}
					// If the incoming symbol has lower precedence than the symbol on the top of the stack, 
					// pop the stack and print the top operator. 
					// Then test the incoming operator against the new top of stack.
					else if (!S.empty () && operatorWeight (S.top ()) > operatorWeight (entity))
					{
						expressionPreQ.push (S.top ());
						S.pop ();
					}
				}
			}
			else
			{
				S.push (entity);
			}
		}
		// Test results for debugging. stringstream keeps stream together for setw()
		if (debugMode)
		{
			stackOutput << &S;
			queueOutput << &expressionPreQ;
			std::cout << std::setw (5) << std::left << i + 1 << std::setw (7) << entity << std::setw (12) << stackOutput.str () << queueOutput.str () << std::endl;
			stackOutput.str ("");
			queueOutput.str ("");
		}
	}
	// At the end of the expression, pop and print all operators on the stack. 
	// (No parentheses should remain.)
	while (!S.empty ())
	{
		expressionPreQ.push (S.top ());
		S.pop ();
	}
	return getPostfix ();
}

/** converts expressionInfix string to expressionInfixQ Queue
@pre expressionInfix valid
@post expressionInfixQ is populated
@param None
@return None */
void ExpressionString::parse ()
{
	expressionInfixQ.clear ();
	std::string entity = "";
	bool operandContinue = false;
	unsigned int i;
	unsigned int n = (unsigned int)expressionInfix.length ();
	for (i = 0; i < n; i++){
		if (debugMode)
		{
			std::cout << "Parse Log: i=" << expressionInfix[i]  << " Q="<< &expressionInfixQ << std::endl;
		}
		// Scanning each character from left. If character is a delimitter, move on. 
		if (expressionInfix[i] == ' ') continue;
		// -, 2 => -2
		if (i == 0 && i + 1 < n && expressionInfix[i] == '-' && isNumeric (expressionInfix[i + 1]))
			operandContinue = true;
		// 5, -, -, 2 => 5 - -2
		if (i != 0 && i + 1 < n && isOperator (std::string (1, expressionInfix[i - 1])) && expressionInfix[i] == '-' && isNumeric (expressionInfix[i + 1]))
			operandContinue = true;
		// (, -, 2, ) => ( -2 )
		if (i != 0 && i + 1 < n && expressionInfix[i] == '-' && expressionInfix[i - 1] == '(' && isNumeric (expressionInfix[i + 1]))
			operandContinue = true;
		// ., 2 => 0.2   3, 5 => 35
		if (i + 1 < n && isNumeric (expressionInfix[i]) && isNumeric (expressionInfix[i + 1]))
			operandContinue = true;
		if (operandContinue)
		{
			operandContinue = false;
			entity += expressionInfix[i];
			continue;
		}
		entity += expressionInfix[i];
		// Print operands as they arrive.
		expressionInfixQ.push (entity);
		// symbol clear and step increment
		entity = "";
	}
	if (debugMode)
	{
		std::cout << "Parsed: " << &expressionInfixQ << std::endl;
	}
}

/** evaluates the expression
@pre expressionPostfix exists
@post expressionEval is evaluated from expressionPostfix
@param None
@return evaluated expression */
void ExpressionString::evaluate ()
{
	Queue<std::string> postQ;
	postQ.copy (&expressionPostQ);
	Stack<std::string> S;
	std::stringstream stackstream;
	std::stringstream stackOutput;
	expressionEval = 0;
	std::string entity = "";
	unsigned int i;
	unsigned int n = (unsigned int)postQ.size ();
	// stack test output
	if (debugMode)
	{
		std::cout << std::setw (5) << std::left << "step" << std::setw (7) << "symbol" << std::setw (10) << "result" << std::setw (8) << "stack" << std::endl;
	}
	for (i = 0; i < n; i++)
	{
		entity = postQ.back ();
		if (isOperand (entity))
		{
			// we saw an operand, push the number onto stack
			S.push (entity);
			postQ.pop ();
		}
		else
		{
			// we saw an operator
			// pop off the top two operands from the
			// stack and evalute them using the current
			// operator
			double op1 = stod (S.top ());
			S.pop ();
			double op2 = stod (S.top ());
			S.pop ();
			expressionEval = operatorEval (op1, op2, entity);
			// push the value obtained after evaluating
			// onto the stack
			stackstream << expressionEval;
			S.push (stackstream.str ());
			stackstream.str ("");
			postQ.pop ();
		}
		// Test results for debugging. stringstream keeps stream together for setw()
		if (debugMode)
		{
			stackOutput << &S;
			std::cout << std::setw (5) << std::left << i + 1 << std::setw (7) << entity << std::setw (10) << expressionEval << stackOutput.str () << std::endl;
			stackOutput.str ("");
		}
	}
}

/** evaluates a two argument operator
@pre None
@post None
@param op1 operand 1
@param op2 operand 2
@param operate operator string
@return evaluated double */
double ExpressionString::operatorEval (double op1, double op2, std::string operate)
{
	if (operate == "*") return op2 * op1;
	else if (operate == "/") return op2 / op1;
	else if (operate == "+") return op2 + op1;
	else if (operate == "-") return op2 - op1;
	else if (operate == "%") return (int)op2 % (int)op1;
	else if (operate == "^") return pow (op2, op1);
	else return 0;
}

/** validates the expression syntax
@pre expressionInfix validation
@post minor clarifications
@return error message. returns empty string if valid */
std::string ExpressionString::validate ()
{
	unsigned int i;
	unsigned int n = (unsigned int)expressionInfix.length ();
	unsigned int parenthesesOpen = 0;
	unsigned int parenthesesClose = 0;
	unsigned int operatorCount = 0;
	// character check
	if (!std::regex_match (expressionInfix, std::regex ("^[0-9\\.\\-\\+\\*\\/\\%\\^\\(\\) ]*$")))
		return "Expression may only contain numbers, decimals, parentheses, and binary arithmetic operators (+, -, *, /, %)";
	//balanced parentheses and syntax check
	for (i = 0; i < n; i++)
	{
		// Scanning each character from left. If character is a delimitter, move on. 
		if (expressionInfix[i] == ' ' || expressionInfix[i] == ',') continue;
		if (expressionInfix[i] == '(')parenthesesOpen++;
		if (expressionInfix[i] == ')')parenthesesClose++;
		if (isOperator (std::string (1, expressionInfix[i])))operatorCount++;
		// +2 not allowed
		if (i == 0 && (isOperator (std::string (1, expressionInfix[i])) && expressionInfix[i] != '-'))
			return "Expression may not start with an operator";
		// --2 not allowed
		if (i == 0 && i + 1 < n && isOperator (std::string (1, expressionInfix[i])) && isOperator (std::string (1, expressionInfix[i + 1])))
			return "Expression may not start with consecutive operators";
		// ++, **, */, +/ not allowed. +- -- *- allowed
		if (i + 1 < n && isOperator (std::string (1, expressionInfix[i])) && (isOperator (std::string (1, expressionInfix[i + 1])) && expressionInfix[i + 1] != '-'))
			return "Two operators may not be in a series.";
		// +-- --- not allowed.
		if (i + 2 < n && isOperator (std::string (1, expressionInfix[i])) && isOperator (std::string (1, expressionInfix[i + 1])) && isOperator (std::string (1, expressionInfix[i + 2])))
			return "Three operators may not be in a series.";
		if (i + 1 == n && isOperator (std::string (1, expressionInfix[i])))
			return "Expression may never end with an operator";
		// (+52)+5 not allowed. (-52)+5 allowed.
		if (i + 1 < n && expressionInfix[i] == '(' && (isOperator (std::string (1, expressionInfix[i + 1])) && expressionInfix[i + 1] != '-'))
			return "Parenthesis may not start with an operator.";
		// (--52)+5 not allowed
		if (i + 2 < n && expressionInfix[i] == '(' && isOperator (std::string (1, expressionInfix[i + 1])) && isOperator (std::string (1, expressionInfix[i + 2])))
			return "Parenthesis may not start with consecutive operators.";
		// (52+)+5 not allowed
		if (i + 1 < n && isOperator (std::string (1, expressionInfix[i])) && expressionInfix[i + 1] == ')')
			return "Parenthesis may not end with an operator.";
		// 52--(6) => 52--1*(6)
		if (i + 3 < n && expressionInfix[i] == '-' && expressionInfix[i + 1] == '(')
		{
			expressionInfix.insert (i + 1, "1*");
			n = (unsigned int)expressionInfix.length ();
		}
		// 52(6) => 52*(6)
		if (i + 3 < n && !isOperator (std::string (1, expressionInfix[i])) && expressionInfix[i + 1] == '(')
		{
			expressionInfix.insert (i + 1, "*");
			n = (unsigned int)expressionInfix.length ();
		}
	}
	if (parenthesesOpen != parenthesesClose)
	{
		return "Parentheses mismatched";
	}
	if (operatorCount == 0)
	{
		return "Expression must contain at least one operator";
	}
	return "";
}

/** verify whether a character is english letter or numeric digit.
@pre None.
@post None.
@param str The string to check
@return True if numeric, or false if not */
bool ExpressionString::isOperand (std::string str)
{
	if (str != "-" && std::regex_match (str, std::regex ("^[a-zA-Z0-9.-]*$"))) return true;
	return false;
}

/** verify whether a character is numeric or not.
@pre None.
@post None.
@param C The character to check
@return True if numeric, or false if not */
bool ExpressionString::isNumeric (char C)
{
	if (C >= '0' && C <= '9') return true;
	if (C == '.') return true;
	return false;
}

/** verify whether a character is operator symbol or not.
@pre None.
@post None.
@param C The character to check
@return True if operator, or false if not */
bool ExpressionString::isOperator (std::string str)
{
	if (str == "+" || str == "-" || str == "*" || str == "/" || str == "%" || str == "^")
		return true;

	return false;
}

/** returns the precedence "weight" for an operator
@pre None.
@post None.
@param op The operator to weigh
@return Weight of the operator and -1 if not found */

int ExpressionString::operatorWeight (std::string op)
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
	if (ListPtr->empty ()) foo << "List is empty" << endl;
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
	if (ListPtr->empty ()) foo << "";
	else
	{
		Node<T> *currPtr = ListPtr->getTail ();
		while (currPtr != nullptr)
		{
			itemCount++;
			//foo << itemCount << ". " << currPtr->value << endl;
			foo << currPtr->value << " ";
			currPtr = currPtr->next;
		}
	}
	return foo;
}
template <class T>
std::ostream& operator<< (std::ostream &foo, Queue<T> *ListPtr)
{
	int itemCount = 0;
	if (ListPtr->empty ()) foo << "";
	else
	{
		Node<T> *currPtr = ListPtr->getTail ();
		while (currPtr != nullptr)
		{
			itemCount++;
			//foo << itemCount << ". " << currPtr->value << endl;
			foo << currPtr->value << " ";
			currPtr = currPtr->next;
		}
	}
	return foo;
}