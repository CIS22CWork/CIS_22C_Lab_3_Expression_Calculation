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

#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

template <class T>
class Queue : protected List<T>
{
public:
	Queue ();
	~Queue ();
	bool empty ();
	int size ();
	bool pop ();
	bool push (T val);
	void clear ();
	T front ();
	T back ();
	void copy (Queue<T> *target);
	void reverse (Queue<T> *target);

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, Queue<T> *ListPtr);
};

//******************************************************
// Default Constructor        
//******************************************************
template <class T>
Queue<T>::Queue () 
{ 
	List::List (); 
}
//******************************************************
// Destructor          
//******************************************************
template <class T>
Queue<T>::~Queue () 
{ 
	List::clear (); 
}

/** Sees whether this list is empty.
@return True if the list is empty; otherwise returns false. */
template <class T>
bool Queue<T>::empty () 
{ 
	return List::empty (); 
}

/** Gets the current number of entries in this list.
@return The integer number of entries currently in the list. */
template <class T>
int Queue<T>::size () 
{
	return List::size (); 
}

/** Removes the entry at the front of the list
@pre List is non-empty or returns false
@post the entry at the front position in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@return True if removal is successful, or false if not. */
template <class T>
bool Queue<T>::pop () 
{ 
	return List::pop_front (); 
}

/** pushes the the given element value to the back
@pre None
@post the entry is added to the back position in the list
and the returned value is true.
@return True if push is successful, or false if not. */
template <class T>
bool Queue<T>::push (T val) 
{ 
	return List::push_back (val); 
}

/** Removes all entries from this list.
@post List contains no entries and the count of items is 0. */
template <class T>
void Queue<T>::clear () 
{ 
	List::clear (); 
}

/** get the value of the element from front of the list
@pre None
@post None
@return The front value */
template <class T>
T Queue<T>::front () 
{ 
	return List::front ();
}

/** get the value of the element from back of the list
@pre None
@post None
@return The back value */
template <class T>
T Queue<T>::back () 
{ 
	return List::back ();
}

/** pushes the target stack object elements to this stack
not a true copy. this method wont make a copy if the element is an object
@pre None
@post Queue has target's elements pushed on
@param target Queue to copy from
@return None */
template <class T>
void Queue<T>::copy (Queue<T> *target) 
{ 
	List::copy (target); 
}

/** pushes the target stack object elements to this stack in reverse
@pre None
@post Queue has target's elements pushed on
@param target Queue to reverse from
@return None */
template <class T>
void Queue<T>::reverse (Queue<T> *target)
{
	List::reverse (target);
}
#endif