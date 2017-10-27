/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2b

Used Microsoft Visual Studio 2017

Queue Class
queues are a type of container adaptor, 
specifically designed to operate in a FIFO context (first-in first-out), 
where elements are inserted into one end of the container and extracted from the other.
*/

#ifndef STACK_H
#define STACK_H
#include "List.h"

template <class T>
class Queue : protected List<T>
{
public:
	//******************************************************
	// Default Constructor        
	//******************************************************
	Queue () { List (); }
	//******************************************************
	// Destructor          
	//******************************************************
	~Queue () { clear (); }

	//******************************************************
	// empty        
	//
	// Returns whether the queue is empty: 
	// i.e. whether its size is zero.
	//******************************************************
	bool empty () { return List::empty (); }

	//******************************************************
	// size         
	//
	// Returns the number of elements in the queue. 
	//******************************************************
	int size () { return List::size (); }

	//******************************************************
	// pop        
	//
	// Removes the next element in the queue, 
	// effectively reducing its size by one.   
	//******************************************************
	bool pop (){ return List::pop_front(); }

	//******************************************************
	// push        
	//
	// Inserts a new element at the end of the queue, 
	// after its current last element. The content of this 
	// new element is initialized to val.
	//******************************************************
	bool push (T val){ return List::push_back (val); }

	//******************************************************
	// clear          
	//
	// Removes all elements from the list container
	// and leaving the container with a size of 0.
	//******************************************************
	void clear () { List::clear (); }

	//******************************************************
	// front       
	//
	// Returns a reference to the next element in the queue.  
	//******************************************************
	T front (){ return getValue (size () - 1); }

	//******************************************************
	// back       
	//
	// Returns a reference to the last element in the queue. 
	// This is the "newest" element in the queue 
	// (i.e. the last element pushed into the queue). 
	//******************************************************
	T back () { return getValue (0); }

	//******************************************************
	// operator<<        
	//******************************************************
	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, Queue<T> *ListPtr);
};

#endif