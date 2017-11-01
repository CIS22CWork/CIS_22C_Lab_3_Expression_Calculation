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

//******************************************************
// pop        
//
// removes the top element     
//******************************************************
template <class T>
bool Stack<T>::pop ()
{
	return List::erase (List::size () - 1);
}

//******************************************************
// push        
//
// inserts element at the top     
//******************************************************
template <class T>
bool Stack<T>::push (T newEntry) 
{ 
	return List::push_back (newEntry); 
}

//******************************************************
// empty        
//
// checks whether the underlying container is empty     
//******************************************************
template <class T>
bool Stack<T>::empty () 
{ 
	return List::empty (); 
}

//******************************************************
// size         
//
// returns the number of elements     
//******************************************************
template <class T>
int Stack<T>::size () 
{ 
	return List::size (); 
}

//******************************************************
// clear          
//
// Removes all elements from the list container
// and leaving the container with a size of 0.
//******************************************************
template <class T>
void Stack<T>::clear () 
{ 
	List::clear (); 
}

//******************************************************
// top        
//
// accesses the top element     
//******************************************************
template <class T>
T Stack<T>::top () 
{ 
	return List::getValue (size () - 1); 
}

//******************************************************
// copy        
//
// pushes the target stack object elements to this stack
// call clear() if you want an exact copy
// this method wont make a copy if the element is an object   
//******************************************************
template <class T>
void Stack<T>::copy (Stack<T> *target) 
{ 
	List::copy (target); 
}

#endif