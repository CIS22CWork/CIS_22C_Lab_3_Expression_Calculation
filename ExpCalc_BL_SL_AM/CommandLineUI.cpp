/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2

Used Microsoft Visual Studio 2017

CommandLineUI class
contains the presentational and interactive interface in the command line for the user.
KEEP ALL COUT<< AND CIN>> HERE
*/

#include "commandLineUI.h"

using namespace std;

CommandLineUI::CommandLineUI (ExpressionString *Expression)
{
	ExpressionStringObj = Expression;
}

//******************************************************
// CommandLineUI::enterLoop  
//      
// the main menu UI loop
//******************************************************
void CommandLineUI::enterLoop ()
{
	cout << "Welcome to the infix expression calculator and evaluator. " << endl;
	bool loopActive = true;
	string equationString;
	//cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n'); // discards "bad" characters
	while (loopActive)
	{
		cout << "Please enter the equation to convert to postfix from infix format and evaluate:" << endl;
		cin.clear (); // clears failure state
		getline (cin, equationString);
		cout << endl;
		ExpressionStringObj->setExpression (equationString);
		if (ExpressionStringObj->validate () == "")
		{
			ExpressionStringObj->parse ();
			ExpressionStringObj->infixToPostfix ();
			cout << "Postfix: " << ExpressionStringObj->getPostfix () << endl;
			//ExpressionStringObj->infixToPrefix ();
			//cout << "Prefix: " << ExpressionStringObj->getPrefix () << endl;
			ExpressionStringObj->evaluate ();
			cout << "Evaluation: " << ExpressionStringObj->getEval () << endl << endl;
		}
		else
		{
			cout << "Error: " << ExpressionStringObj->validate () << endl << endl;
		}
	}
}

//******************************************************
// CommandLineUI::intStackPush   
//      
// This is an example of the Stack push method
//******************************************************
//something

//******************************************************
// operator<<        
//******************************************************
std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr)
{
	foo << "hey";
	return foo;
}