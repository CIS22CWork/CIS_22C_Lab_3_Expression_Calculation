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
	//******************************************************
	// Default Constructor        
	//******************************************************
	List ()
	{
		head = nullptr;
		tail = nullptr;
		itemCount = 0;
	}
	//******************************************************
	// Destructor          
	//******************************************************
	virtual ~List () { clear (); }
	//******************************************************
	// Copy Constructor (May not contain template argument)
	//******************************************************

	//******************************************************
	// empty        
	//
	// Returns whether the list container is empty
	//******************************************************
	bool empty ()
	{
		if (itemCount == 0) return true;
		return false;
	}

	//******************************************************
	// size         
	//
	// Returns the number of elements in the list container.
	//******************************************************
	int size () const
	{
		return itemCount;
	}

	//******************************************************
	// clear          
	//
	// Removes all elements from the list container
	// and leaving the container with a size of 0.
	//******************************************************
	void clear ()
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

	//******************************************************
	// insert       
	//
	// The container is extended by inserting new elements 
	// before the element at the specified position.
	// This effectively increases the list size by the
	// amount of elements inserted.
	//******************************************************
	bool insert (unsigned int position, T val)
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

	//******************************************************
	// front       
	//
	// Returns a reference to the first element in the 
	// list container.
	//******************************************************
	T front () { return getValue (0); }

	//******************************************************
	// back       
	//
	// Returns a reference to the last element in the 
	// list container.
	//******************************************************
	T back () { return getValue (size () - 1); }

	//******************************************************
	// push_back             
	//
	// posts to the end of the list. If successful, newEntry 
	// is stored in the list and the count of items in the 
	// list has increased by 1.
	// param newEntry The object to be added as a new entry.
	// return True if addition was successful, or false if not.    
	//******************************************************
	bool push_back (T newEntry)
	{
		bool returnStatus = insert (itemCount, newEntry);
		return returnStatus;
	}

	//******************************************************
	// push_front           
	//
	// Prepends the given element value to the beginning of 
	// the container.  
	// return: true on success, false on fail
	//******************************************************
	bool push_front (T newEntry)
	{
		bool returnStatus = insert (0, newEntry);
		return returnStatus;
	}

	//******************************************************
	// pop_front          
	//
	// Removes the first element of the container.
	// return: true on success, false on fail
	//******************************************************
	bool pop_front ()
	{
		bool returnStatus = erase (0);
		return returnStatus;
	}

	//******************************************************
	// pop_back         
	//
	// Removes the first element of the container.
	// return: true on success, false on fail
	//******************************************************
	bool pop_back ()
	{
		bool returnStatus = erase (itemCount - 1);
		return returnStatus;
	}

	//******************************************************
	// erase          
	//
	// removes an entry at the defined index
	// index 0=tail, SIZE-1=head 
	// list count decremented by 1 if successful.
	// returns true if addition was successful, or false if not.    
	//******************************************************
	bool erase (unsigned int position)
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
	//******************************************************
	// remove         
	//
	// removes all entries with the same value
	// list count decremented by entries removed if successful.
	// returns true if removal was successful, or false if not.    
	//******************************************************
	bool remove (T anEntry)
	{
		Node<T> *currentNode;
		Node<T> *prevNode;

		currentNode = tail;
		prevNode = currentNode;
		bool returnStatus = true;

		if (currentNode->value == anEntry)
		{
			currentNode = currentNode->next;
			delete tail;
			tail = currentNode;
		}
		else
		{

			while (currentNode != nullptr && currentNode->value != anEntry)
			{
				prevNode = currentNode;
				currentNode = currentNode->next;
			}

			if (currentNode->value == anEntry && head->value == anEntry)
			{
				prevNode->next = currentNode->next;
				//delete currentNode;
				//delete head;
				head = prevNode;

			}
			else if (currentNode->value == anEntry)
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
	//******************************************************
	// find         
	//
	// Tests whether this list contains a given entry.
	// param anEntry  The entry to locate.
	// return  True if list contains anEntry, or false otherwise.
	//******************************************************
	bool find (T anEntry)
	{
		Node<T> *currentNode;
		currentNode = tail;
		while (currentNode)
		{
			if (currentNode->value == anEntry) return true;
			else currentNode = currentNode->next;
		}
		return false;
	}
	//******************************************************
	// getValue           
	//
	// returns the value of the list node index.
	//******************************************************
	T getValue (unsigned int position)
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

	//******************************************************
	// getTail        
	//
	// returns tail node
	//******************************************************
	Node<T>* getTail ()
	{
		return tail;
	}

	//******************************************************
	// copy       
	//
	// pushes the target list object elements to this list
	// call clear() if you want an exact copy
	// this method wont make a copy if the element is an object
	//******************************************************
	void copy (List<T> *target)
	{
		unsigned int n = target->size ();
		for (unsigned int i = 0; i < n; i++) push_back (target->getValue (i));
	}

	//******************************************************
	// operator<<        
	//******************************************************
	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr);
};
#endif