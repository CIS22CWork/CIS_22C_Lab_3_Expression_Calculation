#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <sstream>
#include <limits>
#include "Stack.h"

class CommandLineUI
{
private:
	Stack<int>* StackInt;
	Stack<std::string>* StackString;
	int menuOption;
	int currentMenu;
public:
	CommandLineUI (Stack<int> *StackObjInt, Stack<std::string> *StackObjString);
	void enterLoop ();
	void intStackPush ();
	void intStackPop ();
	void intStackClear ();
	void stringStackPush ();
	void stringStackPop ();
	void stringStackClear ();
};

#endif