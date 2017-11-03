/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 2

Used Microsoft Visual Studio 2017

List
A Singly Linked List ADT which will be composed of one or more nodes.
Implement the most common linked-list behaviors as explained in class -
new list, add anywhere, delete anywhere, find anywhere,
count of items in the list, empty the list, etc.
*/

#ifndef LIST_H
#define LIST_H
#include "Node.h"
#include <iostream>

/*
To make an array have linked lists
DynamicArray<LinkedList<int>> dynamicList
That is a declaration, not a class!!!
*/
template <class T>
class List
{
private:
	Node<T> *head;
	Node<T> *tail;
	unsigned int itemCount;
public:
	List ();
	virtual ~List ();

	bool empty ();
	int size () const;
	void clear ();
	bool insert (unsigned int position, T val);
	T front ();
	T back ();
	bool push_back (T newEntry);
	bool push_front (T newEntry);
	bool pop_front ();
	bool pop_back ();
	bool erase (unsigned int position);
	bool remove (T anEntry);
	bool find (T anEntry);
	T getValue (unsigned int position);
	Node<T>* getTail ();
	void copy (List<T> *target);
	void reverse (List<T> *target);

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr);
};

//******************************************************
// Default Constructor        
//******************************************************
template <class T>
List<T>::List ()
{
	head = nullptr;
	tail = nullptr;
	itemCount = 0;
}
//******************************************************
// Destructor          
//******************************************************
template <class T>
List<T>::~List () { clear (); }
//******************************************************
// Copy Constructor (May not contain template argument)
//******************************************************


/** Sees whether this list is empty.
@return True if the list is empty; otherwise returns false. */
template <class T>
bool List<T>::empty ()
{
	if (itemCount == 0) return true;
	return false;
}

/** Gets the current number of entries in this list.
@return The integer number of entries currently in the list. */
template <class T>
int List<T>::size () const
{
	return itemCount;
}

/** Removes all entries from this list.
@post List contains no entries and the count of items is 0. */
template <class T>
void List<T>::clear ()
{
	Node<T> *currentNode;
	Node<T> *deletedNode;
	Node<T> *nextNode;

	if (!empty ())
	{
		currentNode = tail;
		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
			deletedNode = currentNode;
			currentNode = nextNode;
			delete deletedNode;
		}
	}
	itemCount = 0;
}

/** Inserts an entry into this list at a given position.
@pre None.
@post If 0 <= position <= size() and the insertion is
successful, val is at the given position in the list,
other entries are renumbered accordingly, and the returned
value is true.
@param position The list position at which to insert newEntry.
@param val The entry to insert into the list.
@return True if insertion is successful, or false if not. */
template <class T>
bool List<T>::insert (unsigned int position, T val)
{
	Node<T> *newNode;
	Node<T> *currentNode;
	Node<T> *prevNode;
	bool returnStatus = false;
	unsigned int i;

	newNode = nullptr;
	currentNode = tail;
	prevNode = nullptr;
	// position 0 = front
	// position size = back
	// position 1 = after first element
	if (position >= 0 && position <= itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position)
			{
				newNode = new Node<T> (val);
				returnStatus = true;
				if (i != 0) prevNode->next = newNode;
				else tail = newNode;
				if (i != itemCount) newNode->next = currentNode;
				else head = newNode;
				itemCount++;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
		}
	}
	return returnStatus;
}

/** get the value of the element from front of the list
@pre None
@post None
@return The front value */
template <class T>
T List<T>::front () 
{ 
	return getValue (0); 
}

/** get the value of the element from back of the list
@pre None
@post None
@return The back value */
template <class T>
T List<T>::back () 
{ 
	return getValue (size () - 1); 
}

/** pushes the the given element value to the back
@pre None
@post the entry is added to the back position in the list
and the returned value is true.
@return True if push is successful, or false if not. */
template <class T>
bool List<T>::push_back (T newEntry)
{
	bool returnStatus = insert (itemCount, newEntry);
	return returnStatus;
}

/** Prepends the given element value to the front
@pre None
@post the entry is added to the front position in the list
and the returned value is true.
@return True if push is successful, or false if not. */
template <class T>
bool List<T>::push_front (T val)
{
	bool returnStatus = insert (0, val);
	return returnStatus;
}

/** Removes the entry at the front of the list
@pre List is non-empty or returns false
@post the entry at the front position in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@return True if removal is successful, or false if not. */
template <class T>
bool List<T>::pop_front ()
{
	bool returnStatus = erase (0);
	return returnStatus;
}

/** Removes the entry at the back of the list
@pre List is non-empty or returns false
@post the entry at the back position in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@return True if removal is successful, or false if not. */
template <class T>
bool List<T>::pop_back ()
{
	bool returnStatus = erase (itemCount - 1);
	return returnStatus;
}

/** Removes the entry at a given position from this list.
@pre None.
@post If 0 <= position <= size() and the removal is successful,
the entry at the given position in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@param position The list position of the entry to remove.
@return True if removal is successful, or false if not. */
template <class T>
bool List<T>::erase (unsigned int position)
{
	Node<T> *currentNode;
	Node<T> *prevNode;
	Node<T> *deletedNode;
	bool returnStatus = false;
	unsigned int i;

	currentNode = tail;
	prevNode = nullptr;
	deletedNode = nullptr;

	if (position >= 0 && position < itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position)
			{
				deletedNode = currentNode;
				if (i != 0 && i != itemCount) prevNode->next = currentNode->next;
				if (i == 0 && i == itemCount) { head = nullptr; tail = nullptr; };
				if (i == 0 && i != itemCount) tail = currentNode->next;
				if (i != 0 && i == itemCount) head = prevNode->next;
				currentNode->next = nullptr;
				delete currentNode;
				itemCount--;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
		}
	}
	return returnStatus;
}

/** Removes the entry matching val from this list.
@pre None.
@post If val exists and the removal is successful,
the entry matching the val in the list is removed, other
items are renumbered accordingly, and the returned value is true.
@param val The value of the entry to remove.
@return True if removal is successful, or false if not. */
template <class T>
bool List<T>::remove (T val)
{
	Node<T> *currentNode;
	Node<T> *prevNode;

	currentNode = tail;
	prevNode = currentNode;
	bool returnStatus = true;

	if (currentNode->value == val)
	{
		currentNode = currentNode->next;
		delete tail;
		tail = currentNode;
	}
	else
	{

		while (currentNode != nullptr && currentNode->value != val)
		{
			prevNode = currentNode;
			currentNode = currentNode->next;
		}

		if (currentNode->value == val && head->value == val)
		{
			prevNode->next = currentNode->next;
			//delete currentNode;
			//delete head;
			head = prevNode;

		}
		else if (currentNode->value == val)
		{
			prevNode->next = currentNode->next;
			delete currentNode;
		}
	}
	if (itemCount != 0)
	{
		itemCount--;
	}
	return returnStatus;
}

/** Tests whether this list contains a given value
@pre None.
@post None
@param val The value of the entry to find.
@return True if list contains val, or false otherwise. */
template <class T>
bool List<T>::find (T val)
{
	Node<T> *currentNode;
	currentNode = tail;
	while (currentNode)
	{
		if (currentNode->value == val) return true;
		else currentNode = currentNode->next;
	}
	return false;
}

/** Gets the entry at the given position in this list.
@pre 0 <= position < size().
@post The desired entry has been returned.
@param position The list position of the desired entry.
@return The entry at the given position. */
template <class T>
T List<T>::getValue (unsigned int position)
{
	Node<T> *currentNode;
	T returnValue;

	unsigned int i;
	currentNode = tail;

	if (position >= 0 && position < itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position) returnValue = currentNode->value;
			else currentNode = currentNode->next;
		}
	}
	return returnValue;
}

/** Gets the tail node
@pre None
@post None
@return The tail node. */
template <class T>
Node<T>* List<T>::getTail ()
{
	return tail;
}

/** pushes the target stack object elements to this stack
@pre None
@post Queue has target's elements pushed on
@param target Queue to push from
@return None */
template <class T>
void List<T>::copy (List<T> *target)
{
	unsigned int n = target->size ();
	for (unsigned int i = 0; i < n; i++) push_back (target->getValue (i));
}

/** pushes the target stack object elements to this stack in reverse
@pre None
@post Queue has target's elements pushed on
@param target Queue to reverse from
@return None */
template <class T>
void List<T>::reverse (List<T> *target)
{
	unsigned int n = target->size ();
	for (unsigned int i = n; i > 0; i--) push_back (target->getValue (i-1));
}
#endif