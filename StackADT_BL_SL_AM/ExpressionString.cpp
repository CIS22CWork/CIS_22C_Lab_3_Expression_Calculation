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

//******************************************************
// class constructor (no argument version)      
//******************************************************
ExpressionString::ExpressionString (void) {

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
std::string ExpressionString::getPostfix ()
{
	std::stringstream queueOutput;
	queueOutput << &expressionPostQ;
	return queueOutput.str ();
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
//
// TESTED WITH: 1000-(57*23/5*b-(69-9*(1))%2)
//******************************************************
std::string ExpressionString::infixToPostfix ()
{
	Stack<std::string> S;
	std::string entity = "";
	bool operatorFlag = false;
	bool operandContinue = false;
	bool pushed;
	unsigned int i;
	unsigned int j;
	unsigned int n = (unsigned int)expressionInfix.length ();
	std::stringstream queueOutput;
	std::stringstream stackOutput;
	// stack test output
	std::cout << std::setw (5) << std::left << "step" << std::setw (7) << "symbol" << std::setw (8) << "stack" << std::setw (8) << "postfix" << std::endl;
	for (i = 0, j = 1; i < n; i++)
	{
		// Instructions from http://csis.pace.edu/~wolf/CS122/infix-postfix.htm
		// Scanning each character from left. If character is a delimitter, move on. 
		if (expressionInfix[i] == ' ' || expressionInfix[i] == ',') continue;
		// If this and next character are numbers or a '.' then combine them
		isOperator (expressionInfix[i]) ? operatorFlag = true : operatorFlag = false;
		if (i + 1 < n && isNumeric (expressionInfix[i]) && isNumeric (expressionInfix[i + 1]))
		{
			operandContinue = true;
			entity += expressionInfix[i];
			continue;
		}
		if (operandContinue) entity += expressionInfix[i];
		if (entity == "") entity = expressionInfix[i];
		// Print operands as they arrive.
		if (isOperand (entity)) expressionPostQ.push (entity);
		// 	If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
		else if (operatorFlag && (S.empty () || S.top () == "(")) S.push (entity);
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
		// stack test results
		// keeps stream together for setw()
		stackOutput << &S;
		queueOutput << &expressionPostQ;
		std::cout << std::setw (5) << std::left << j << std::setw (7) << entity << std::setw (8) << stackOutput.str () << queueOutput.str () << std::endl;
		stackOutput.str ("");
		queueOutput.str ("");
		// symbol clear and step increment
		entity = "";
		j++;
		operandContinue = false;
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

/** evaluates the expression
@pre expressionPostfix exists
@post expressionEval is evaluated from expressionPostfix
@param None
@return evaluated expression */
void ExpressionString::evaluate ()
{
	Stack<std::string> S;
	unsigned int i;
	unsigned int n = (unsigned int)expressionPostQ.size ();
	for (i = 0; i < n; i++)
	{
		std::cout << "back: " << expressionPostQ.back () << std::endl;
		std::cout << "stack: " << &S << std::endl;
		if (isOperand (expressionPostQ.back ()))
		{
			// we saw an operand, push the digit onto stack
			S.push (expressionPostQ.back ());
			expressionPostQ.pop ();
		}
		else
		{
			// we saw an operator, pop off the top two operands from the
			// stack and evalute them using the current operator
			// push the value obtained after evaluating
			// onto the stack
			operatorEval (&S, expressionPostQ.back ());
			expressionPostQ.pop ();
		}
	}
	std::stringstream queueOutput;
	queueOutput << &S;
	std::cout << queueOutput.str ();
}

/** evaluates a two argument operator
@pre Stack is not empty and has two elements on top
@post Operands returned to the stack
@param S operand stack
@param operate operator
@return None */
void ExpressionString::operatorEval (Stack<std::string> *S, std::string operate)
{
	bool op1Numberic = false;
	bool op2Numberic = false;
	double op1 = 0;
	double op2 = 0;
	std::string op1Str = "";
	std::string op2Str = "";
	std::ostringstream strs;
	if (!S->empty ())
	{
		op1Str = S->top ();
		if (std::regex_match (op1Str, std::regex ("^[0-9.]*$")))
		{
			op1Numberic = true;
			op1 = stod (op1Str);
		}
		S->pop ();
		if (!S->empty ())
		{
			op2Str = S->top ();
			if (std::regex_match (op2Str, std::regex ("^[0-9.]*$")))
			{
				op2Numberic = true;
				op2 = stod (op2Str);
			}
			S->pop ();
		}
	}
	if (operate == "*")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5*6=30
			strs << op2 * op1;
			S->push (strs.str ());
		}
		else if (!op1Numberic && op2Numberic)
		{
			// a*6 = a 6
			S->push (op1Str);
			S->push (op2Str);
		}
		else if (op1Numberic && !op2Numberic)
		{
			// 5*b = b 5
			S->push (op2Str);
			S->push (op1Str);
		}
		else
		{
			// a*b = ab
			S->push (op2Str + op1Str);
		}
	}
	else if (operate == "/")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5/6=0.8333
			strs << (double)(op2 / op1);
			S->push (strs.str ());
		}
		else if (!op1Numberic && op2Numberic)
		{
			// 6/a = 1/a 6
			S->push ("(1/" + op1Str + ")");
			S->push (strs.str ());
		}
		else if (op1Numberic && !op2Numberic)
		{
			// b/5 = b 1/5
			S->push (op2Str);
			strs << 1 / op1;
			S->push (strs.str ());
		}
		else
		{
			// a/b = a/b
			S->push (op2Str + "/" + op1Str);
		}
	}
	else if (operate == "+")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5+6=11
			strs << op2 + op1;
			S->push (strs.str ());
		}
		else
		{
			// a+b = (a+b)
			S->push ("(" + op2Str + "+" + op1Str + ")");
		}
	}
	else if (operate == "-")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5-6=-1
			strs << op2 - op1;
			S->push (strs.str ());
		}
		else
		{
			// a-b = (a-b)
			S->push ("(" + op2Str + "-" + op1Str + ")");
		}
	}
	else if (operate == "%")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5%6=5
			strs << (int)op2 % (int)op1;
			S->push (strs.str ());
		}
		else
		{
			// a%b = (a%b)
			S->push ("(" + op2Str + "%" + op1Str + ")");
		}
	}
	else if (operate == "^")
	{
		if (op1Numberic && op2Numberic)
		{
			// 5^6=15625
			strs << pow (op2, op1);
			S->push (strs.str ());
		}
		else
		{
			// a^b = (a^b)
			S->push ("(" + op2Str + "^" + op1Str + ")");
		}
	}
}

/** verify whether a character is english letter or numeric digit.
@pre None.
@post None.
@param str The string to check
@return True if numeric, or false if not */
bool ExpressionString::isOperand (std::string str)
{
	if (std::regex_match (str, std::regex ("^[a-zA-Z0-9_]*$"))) return true;
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
bool ExpressionString::isOperator (char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '%' || C == '^')
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
			foo << currPtr->value;
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