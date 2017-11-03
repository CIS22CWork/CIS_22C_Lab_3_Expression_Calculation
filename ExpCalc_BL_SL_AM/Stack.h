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
	Stack ();
	~Stack ();
	bool pop ();
	bool push (T newEntry);
	bool empty ();
	int size ();
	void clear ();
	T top ();
	void copy (Stack<T> *target);

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, Stack<T> *ListPtr);
};

//******************************************************
// Default Constructor        
//******************************************************
template <class T>
Stack<T>::Stack () { 
	List (); 
}

//******************************************************
// Copy Constructor argument can't be template
//******************************************************
//******************************************************
// Destructor          
//******************************************************
template <class T> 
Stack<T>::~Stack () 
{ 
	clear (); 
}

/** Removes the entry at the back of the list
@pre List is non-empty or returns false
@post the entry at the back position in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@return True if removal is successful, or false if not. */
template <class T>
bool Stack<T>::pop ()
{
	return List::pop_back();
}

/** pushes the the given element value to the back
@pre None
@post the entry is added to the back position in the list
and the returned value is true.
@return True if push is successful, or false if not. */
template <class T>
bool Stack<T>::push (T newEntry) 
{ 
	return List::push_back (newEntry); 
}

/** Sees whether this list is empty.
@return True if the list is empty; otherwise returns false. */
template <class T>
bool Stack<T>::empty () 
{ 
	return List::empty (); 
}

/** Gets the current number of entries in this list.
@return The integer number of entries currently in the list. */
template <class T>
int Stack<T>::size () 
{ 
	return List::size (); 
}

/** Removes all entries from this list.
@post List contains no entries and the count of items is 0. */
template <class T>
void Stack<T>::clear () 
{ 
	List::clear (); 
}

/** get the value of the element from top of the list
@pre None
@post None
@return The top value */
template <class T>
T Stack<T>::top () 
{ 
	return List::getValue (size () - 1); 
}

/** pushes the target stack object elements to this stack
@pre None
@post Queue has target's elements pushed on
@param target Queue to push from
@return None */
template <class T>
void Stack<T>::copy (Stack<T> *target) 
{ 
	List::copy (target); 
}

#endif