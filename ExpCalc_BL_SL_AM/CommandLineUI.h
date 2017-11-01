#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <sstream>
#include <limits>
#include "Stack.h"
#include "Queue.h"
#include "List.h"
#include "ExpressionString.h"

class CommandLineUI
{
private:
	ExpressionString* ExpressionStringObj;
public:
	CommandLineUI (ExpressionString *StackObjInt);
	void enterLoop ();
};

#endif