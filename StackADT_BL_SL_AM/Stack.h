/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2

Used Microsoft Visual Studio 2017

Stack
A Stack ADT derived from a singly linked list which will implement
the most common Stack operations like push, pop, isempty etc.
and only expose them.
*/

#ifndef STACK_H
#define STACK_H
#include "List.h"

template <class T>
class Stack : protected List<T>
{
public:
	//******************************************************
	// Default Constructor        
	//******************************************************
	Stack () { List (); }
	//******************************************************
	// Destructor          
	//******************************************************
	~Stack () { clear (); }

	//******************************************************
	// pop        
	//
	// removes the top element     
	//******************************************************
	bool pop ()
	{
		return erase (size () - 1);
	}

	//******************************************************
	// push        
	//
	// inserts element at the top     
	//******************************************************
	bool push (T newEntry)
	{
		return push_back (newEntry);
	}

	//******************************************************
	// empty        
	//
	// checks whether the underlying container is empty     
	//******************************************************
	bool empty () { return List::empty (); }

	//******************************************************
	// size         
	//
	// returns the number of elements     
	//******************************************************
	int size () { return List::size (); }

	//******************************************************
	// clear          
	//
	// Removes all elements from the list container
	// and leaving the container with a size of 0.
	//******************************************************
	void clear () { List::clear (); }

	//******************************************************
	// top        
	//
	// accesses the top element     
	//******************************************************
	T top ()
	{
		return getValue (size () - 1);
	}
	//******************************************************
	// operator<<        
	//******************************************************
	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, Stack<T> *ListPtr);
};

#endif