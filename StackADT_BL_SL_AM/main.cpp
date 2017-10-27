/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0

main
inits different Queue classes and passes the UI for the demo
*/

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Queue.h"
#include "Currency.h"
#include "CommandLineUI.h"

using namespace std;

int main ()
{
	/* initialize random seed: */
	srand ((int)time (NULL));
	Queue<int> QueueInt;
	Queue<string> QueueString;
	Queue<Currency> QueueCurrency;
	CommandLineUI UI (&QueueInt, &QueueString, &QueueCurrency);
	// start the UI
	UI.enterLoop ();

	//comment out the next line before compiling final .exe and submitting to the teacher
	system ("pause");
	return 0;
}