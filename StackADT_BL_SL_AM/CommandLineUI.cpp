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

#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "commandLineUI.h"
#include "List.h"

using namespace std;

CommandLineUI::CommandLineUI (Stack<int> *StackObjInt, Stack<std::string> *StackObjString)
{
	StackInt = StackObjInt;
	StackString = StackObjString;
}

/* ******************** enterLoop ********************
the main menu UI loop
*/
void CommandLineUI::enterLoop ()
{
	cout << "Welcome to our linked list demo. ";
	bool loopActive = true;
	while (loopActive)
	{
		cout << "Please enter the number representing the menu options below:" << endl
			<< "1. Push random integers to the integer type Stack" << endl
			<< "2. Pop from the integer type Stack" << endl
			<< "3. Clear the integer type Stack" << endl
			<< "4. Push \"ExampleStrings.txt\" to the string type Stack." << endl
			<< "5. Pop from the string type Stack" << endl
			<< "6. Clear the string type Stack" << endl
			<< "7. Exit Application" << endl << endl
			<< "Selection Number: ";
		// there is a bug that when you enter "test,2,3,hey" in the menu selection. 
		// The program gets stuck in an infinite loop
		cin >> menuOption;
		if (cin.fail ())
		{
			cin.clear (); // clears failure state
			cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n'); // discards "bad" characters
			menuOption = 0;
		}
		cout << endl;
		if (menuOption < 1 || menuOption > 10)
		{
			cout << "************************************" << endl;
			cout << "Your selection was not valid. Please try again." << endl;
			cout << "************************************" << endl << endl;
		}
		else
		{
			/* please keep each sub-menu in a separate function to increase readability and prevent
			a huge blob of unorganized code. */
			if (menuOption == 1) intStackPush ();
			else if (menuOption == 2) intStackPop ();
			else if (menuOption == 3) intStackClear ();
			else if (menuOption == 4) stringStackPush ();
			else if (menuOption == 5) stringStackPop ();
			else if (menuOption == 6) stringStackClear ();
			else if (menuOption == 7) loopActive = false;
		}
	}
}

//******************************************************
// CommandLineUI::intStackPush   
//      
// This is an example of the Stack push method
//******************************************************
void CommandLineUI::intStackPush ()
{
	int intRandom = rand () % 99999;
	StackInt->push (intRandom);
	cout << "integer Stack items:" << endl << StackInt << endl << endl;
}

//******************************************************
// CommandLineUI::intStackPop         
//      
// This is an example of the Stack pop method
//******************************************************
void CommandLineUI::intStackPop ()
{
	if (StackInt->empty ())
	{
		cout << "************************************" << endl;
		cout << "Stack is empty! Underflow Condition!" << endl;
		cout << "************************************" << endl << endl;
	}
	else
	{
		StackInt->pop ();
		cout << "integer Stack items:" << endl << StackInt << endl << endl;
	}
}

//******************************************************
// CommandLineUI::intStackClear         
//      
// This is an example of the list clear method
//******************************************************
void CommandLineUI::intStackClear ()
{
	StackInt->clear ();
	cout << "integer Stack items:" << endl << StackInt << endl << endl;
}

//******************************************************
// CommandLineUI::stringStackPush
//      
// This is an example of the Stack push method
//******************************************************
void CommandLineUI::stringStackPush ()
{
	string buffer;
	ifstream read_input_file ("ExampleStrings.txt");

	cout << "Pushing \"ExampleStrings.txt\" contents to Stack:" << endl;
	while (true)
	{
		read_input_file >> buffer;
		if (!read_input_file) break;
		StackString->push (buffer);
	}
	read_input_file.close ();
	cout << "string Stack items:" << endl << StackString << endl << endl;
}

//******************************************************
// CommandLineUI::stringStackPop        
//      
// This is an example of the Stack pop method
//******************************************************
void CommandLineUI::stringStackPop ()
{
	if (StackString->empty ())
	{
		cout << "************************************" << endl;
		cout << "Stack is empty! Underflow Condition!" << endl;
		cout << "************************************" << endl << endl;
	}
	else
	{
		StackString->pop ();
		cout << "string Stack items:" << endl << StackString << endl << endl;
	}
}

//******************************************************
// CommandLineUI::stringStackClear         
//      
// This is an example of the list clear method
//******************************************************
void CommandLineUI::stringStackClear ()
{
	StackString->clear ();
	cout << "string Stack items:" << endl << StackString << endl << endl;
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