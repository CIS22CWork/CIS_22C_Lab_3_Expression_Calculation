/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
IF LIBRARYS ARE NOT FOUND, THEN SWITCH SDK VERSION
OR INSTALL THIS SDK VERSION

main
inits different Stack classes and passes the UI for the demo
*/

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Stack.h"
#include "ExpressionString.h"
#include "CommandLineUI.h"

using namespace std;

int main ()
{
	/* initialize random seed: */
	srand ((int)time (NULL));
	Stack<int> StackInt;
	Stack<string> StackString;
	ExpressionString ExpressionObj;
	cout << ExpressionObj.InfixToPostfix("A*(B+C*D)+E") << endl;
	CommandLineUI UI (&StackInt, &StackString);
	// start the UI

	UI.enterLoop ();

	//comment out the next line before compiling final .exe and submitting to the teacher
	system ("pause");
	return 0;
}