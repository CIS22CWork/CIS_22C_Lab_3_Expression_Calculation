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
#include "Stack.h"
#include "List.h"
#include "ExpressionString.h"

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
		cout << "Please enter the equation to convert to postfix and infix format and evaluate:" << endl;
		cin.clear (); // clears failure state
		getline (cin, equationString);
		cout << endl;
		cout << "Postfix: " << ExpressionStringObj->InfixToPostfix (equationString) << endl << endl;
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
/*
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
			//foo << itemCount << ". " << currPtr->value << endl;
			foo << currPtr->value;
			currPtr = currPtr->next;
		}
	}
	return foo;
}
std::ostream& operator<< (std::ostream &foo, ExpressionString *ObjPtr)
{
	foo << "hey";
	return foo;
}*/