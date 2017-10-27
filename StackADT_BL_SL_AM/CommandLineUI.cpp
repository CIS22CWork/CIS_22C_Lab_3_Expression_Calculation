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

CommandLineUI::CommandLineUI (Queue<int> *QueueObjInt, Queue<std::string> *QueueObjString, Queue<Currency> *QueueObjCurrency)
{
	QueueInt = QueueObjInt;
	QueueString = QueueObjString;
	QueueCurrency = QueueObjCurrency;
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
			<< "1. Push random integers to the integer type Queue" << endl
			<< "2. Pop from the integer type Queue" << endl
			<< "3. Clear the integer type Queue" << endl
			<< "4. Push \"ExampleStrings.txt\" to the string type Queue." << endl
			<< "5. Pop from the string type Queue" << endl
			<< "6. Clear the string type Queue" << endl
			<< "7. Push a random Currency to the currency type Queue" << endl
			<< "8. Pop from the Currency type Queue" << endl
			<< "9. Clear the Currency type Queue" << endl
			<< "10. Exit Application" << endl << endl
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
			if (menuOption == 1) intQueuePush ();
			else if (menuOption == 2) intQueuePop ();
			else if (menuOption == 3) intQueueClear ();
			else if (menuOption == 4) stringQueuePush ();
			else if (menuOption == 5) stringQueuePop ();
			else if (menuOption == 6) stringQueueClear ();
			else if (menuOption == 7) currencyQueuePush ();
			else if (menuOption == 8) currencyQueuePop ();
			else if (menuOption == 9) currencyQueueClear ();
			else if (menuOption == 10) loopActive = false;
		}
	}
}

//******************************************************
// CommandLineUI::intQueuePush   
//      
// This is an example of the Queue push method
//******************************************************
void CommandLineUI::intQueuePush ()
{
	int intRandom = rand () % 99999;
	QueueInt->push (intRandom);
	cout << "integer Queue items:" << endl << QueueInt << endl << endl;
}

//******************************************************
// CommandLineUI::intQueuePop         
//      
// This is an example of the Queue pop method
//******************************************************
void CommandLineUI::intQueuePop ()
{
	if (QueueInt->empty ())
	{
		cout << "************************************" << endl;
		cout << "Queue is empty! Underflow Condition!" << endl;
		cout << "************************************" << endl << endl;
	}
	else
	{
		QueueInt->pop ();
		cout << "integer Queue items:" << endl << QueueInt << endl << endl;
	}
}

//******************************************************
// CommandLineUI::intQueueClear         
//      
// This is an example of the list clear method
//******************************************************
void CommandLineUI::intQueueClear ()
{
	QueueInt->clear ();
	cout << "integer Queue items:" << endl << QueueInt << endl << endl;
}

//******************************************************
// CommandLineUI::stringQueuePush
//      
// This is an example of the Queue push method
//******************************************************
void CommandLineUI::stringQueuePush ()
{
	string buffer;
	ifstream read_input_file ("ExampleStrings.txt");

	cout << "Pushing \"ExampleStrings.txt\" contents to Queue:" << endl;
	while (true)
	{
		read_input_file >> buffer;
		if (!read_input_file) break;
		QueueString->push (buffer);
	}
	read_input_file.close ();
	cout << "string Queue items:" << endl << QueueString << endl << endl;
}

//******************************************************
// CommandLineUI::stringQueuePop        
//      
// This is an example of the Queue pop method
//******************************************************
void CommandLineUI::stringQueuePop ()
{
	if (QueueString->empty ())
	{
		cout << "************************************" << endl;
		cout << "Queue is empty! Underflow Condition!" << endl;
		cout << "************************************" << endl << endl;
	}
	else
	{
		QueueString->pop ();
		cout << "string Queue items:" << endl << QueueString << endl << endl;
	}
}

//******************************************************
// CommandLineUI::stringQueueClear         
//      
// This is an example of the list clear method
//******************************************************
void CommandLineUI::stringQueueClear ()
{
	QueueString->clear ();
	cout << "string Queue items:" << endl << QueueString << endl << endl;
}

//******************************************************
// CommandLineUI::currencyQueuePush
//      
// This is an example of the Queue push method
//******************************************************
void CommandLineUI::currencyQueuePush ()
{
	// randomly generates a derived currency class class and fills it with
	// money 0-100 whole and 0-99 fractional parts then pushes it onto the Queue
	int intRandom = rand () % 4;
	if (intRandom == 0) QueueCurrency->push (CurrencyDollar (rand () % 100, rand () % 99));
	else if (intRandom == 1) QueueCurrency->push (CurrencyEuro (rand () % 100, rand () % 99));
	else if (intRandom == 2) QueueCurrency->push (CurrencyRupee (rand () % 100, rand () % 99));
	else if (intRandom == 3) QueueCurrency->push (CurrencyYen (rand () % 100, rand () % 99));
	else if (intRandom == 4) QueueCurrency->push (CurrencyYuan (rand () % 100, rand () % 99));
	cout << "Currency Queue items:" << endl << QueueCurrency << endl << endl;
}

//******************************************************
// CommandLineUI::currencyQueuePop      
//      
// This is an example of the Queue pop method
//******************************************************
void CommandLineUI::currencyQueuePop ()
{
	if (QueueCurrency->empty ())
	{
		cout << "************************************" << endl;
		cout << "Queue is empty! Underflow Condition!" << endl;
		cout << "************************************" << endl << endl;
	}
	else
	{
		QueueCurrency->pop ();
		cout << "Currency Queue items:" << endl << QueueCurrency << endl << endl;
	}
}

//******************************************************
// CommandLineUI::currencyQueueClear         
//      
// This is an example of the list clear method
//******************************************************
void CommandLineUI::currencyQueueClear ()
{
	QueueCurrency->clear ();
	cout << "Currency Queue items:" << endl << QueueCurrency << endl << endl;
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
std::ostream& operator<< (std::ostream &foo, Queue<T> *ListPtr)
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