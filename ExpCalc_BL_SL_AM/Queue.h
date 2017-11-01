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

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, Queue<T> *ListPtr);
};

//******************************************************
// Default Constructor        
//******************************************************
template <class T>
Queue<T>::Queue () { List::List (); }
//******************************************************
// Destructor          
//******************************************************
template <class T>
Queue<T>::~Queue () { List::clear (); }

//******************************************************
// empty        
//
// Returns whether the queue is empty: 
// i.e. whether its size is zero.
//******************************************************
template <class T>
bool Queue<T>::empty () { return List::empty (); }

//******************************************************
// size         
//
// Returns the number of elements in the queue. 
//******************************************************
template <class T>
int Queue<T>::size () { return List::size (); }

//******************************************************
// pop        
//
// Removes the next element in the queue, 
// effectively reducing its size by one.   
//******************************************************
template <class T>
bool Queue<T>::pop () { return List::pop_front (); }

//******************************************************
// push        
//
// Inserts a new element at the end of the queue, 
// after its current last element. The content of this 
// new element is initialized to val.
//******************************************************
template <class T>
bool Queue<T>::push (T val) { return List::push_back (val); }

//******************************************************
// clear          
//
// Removes all elements from the list container
// and leaving the container with a size of 0.
//******************************************************
template <class T>
void Queue<T>::clear () { List::clear (); }

//******************************************************
// front       
//
// Returns a reference to the next element in the queue.  
//******************************************************
template <class T>
T Queue<T>::front () { return List::getValue (List::size () - 1); }

//******************************************************
// back       
//
// Returns a reference to the last element in the queue. 
// This is the "newest" element in the queue 
// (i.e. the last element pushed into the queue). 
//******************************************************
template <class T>
T Queue<T>::back () { return List::getValue (0); }

/** pushes the target stack object elements to this stack
not a true copy. this method wont make a copy if the element is an object
@pre None
@post Queue has target's elements pushed on
@param target Queue to copy from
@return None */
template <class T>
void Queue<T>::copy (Queue<T> *target) { List::copy (target); }
#endif