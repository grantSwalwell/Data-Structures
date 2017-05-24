#pragma once
#include <iostream>
using namespace std;
// LinkedList class, classic implementation

// LinkedList exception
class LinkedListException : public exception {} LLException;

// LinkedList memory exception
class LLMemory : public LinkedListException {} LLMemory;

// LinkedList bounds exception
class LLBounds : public LinkedListException {} Bounds;

// LinkedList not found exception
class LLNotFound : public LinkedListException {} NotFound;

// LinkedList attach to empty list exception
class LLAttachToEmpty : public LinkedListException {} AttachToEmpty;



template <class x> class LinkedList
{
public:

	// data
	x* info;

	// next link
	LinkedList<x>* next;

	// get ll size
	int size ()
	{
		// if next is NULL
		if (this->next == NULL)
		{
			// if info is null size is zero
			if (this->info == NULL) return 0;
			else return 1; // else size is 1
		}
		else return 1 + this->next->size(); // else next is not NULL, return 1 + next.size 
		
	};

	// add method
	void add(const x& info)
	{
		// if info is NULL this->info = info
		if (this->info == NULL) this->info = new x(info);
		else
		{
			// create a new node out of the head node [head]->[next], new ll(head) = [new]->[next]
			LinkedList<x>* newll = new LinkedList<x>((*this->info), this->next);

			// set the heads info to the new info  [new head]->[next]
			this->info = new x(info);

			// set next to the new node [head]->[new]->[next]
			this->next = newll;
		}
	};

	// insert method
	void insert(int position, const x& obj)
	{
		// if add to first position call add
		if (position == 0) add(obj);
		else
		{
			// if we are at the end of the list
			if (next == NULL)
			{
				next = new LinkedList<x>(obj);
			}
			else this->next->insert(position - 1, obj); // else call insert on next link			
		}
	};
	
	// remove object method
	x remove()
	{
		// hold old info
		x temp = *info;

		// delete old info
		delete info;

		// if next is NULL dont worry about it, the list is now empty
		if (this->next == NULL) info = NULL;
		else
		{

			// set this info to next info because next is the new head
			this->info = this->next->info;

			// set next to next->next because it's the new next
			this->next = this->next->next;
		}

		return temp;
	};

	// remove at method
	x remove(int position)
	{
		// if we are at the spot to remove remove it
		if (position == 0) return remove();
		else
		{
			// else call remove on the next
			return this->next->remove(position - 1);
		}

	};

	// find method
	x& find(const x& key)
	{
		// if this is right return this info
		if (key == *info) return *info;
		else return next->find(key); //  else check the next link
	};

	// contains
	bool contains(x& key)
	{
		// if key = info return true
		if (info == NULL) return false;
		if (*info == key) return true;
		if (next == NULL) return false;
		else return next->contains(key); // otherwise return false
	};

	// data at index
	x& data(int index)
	{
		if (index == 0) return (*this->info);

		return next->data(index - 1);
	};

	// returns index of key
	int index(const x& key, int position)
	{
		// index
		int i = 0;

		if (*info == key) return position;
		else
		{
			return next->index(key, position + 1);
		}
	};

	// print method for printing entire ll
	ostream& print (ostream& os)
	{
		// send this info to ostream
		os << (*this->info) << endl;

		// if there is a next link
		//if (this->next != NULL)
		//{
			// print the next link, recursive
			//this->next->print(os);
		//}

		// return the ostream
		return os;

	};

	// is empty
	bool empty()
	{
		return info == NULL;
	}

	// cout << operator override
	friend ostream& operator<< (ostream& os, LinkedList& ll)
	{
		// just calls print
		return ll.print(os);
	};

	// [] operator override
	x& operator[] (int index)
	{
		return data(index);
	};

	// overloaded = operator
	LinkedList& operator= (LinkedList& ll)
	{
		// if info isnt null delete it
		if (this->info != NULL) delete info;

		// copy over info
		this->info = ll.info;

		// if next isnt null delete it
		if (this->next != NULL) delete info;

		// copy over next
		this->next = ll.next;
	};

	// default constructor
	LinkedList () { this->info = NULL; this->next = NULL; };

	// info initializer
	LinkedList (const x& info) { this->info = new x(info); this->next = NULL; };

	// info and next initializer
	LinkedList(const x& info, LinkedList* next)
	{
		this->info = new x(info);

		this->next = next;
	}

	// copy constructor
	LinkedList (LinkedList& ll)
	{
		// If the list to be copied is NULL info is NULL
		if (ll.info == NULL) this->info = NULL;
		else 
		{
			// set info to ll.info
			this->info = ll.info;
		}

		// if ll.next == null this->next = null
		if (ll.next = NULL) this->next = NULL;
		else 
		{
			// else next = ll.next
			this->next = ll.next;
		}
	};

	// destructor
	~LinkedList ()
	{ 
		// if there is info
		if (this->info != NULL)
		{
			// delete it
			delete info;

			// set it to null
			this->info = NULL;
		}
		
		// if there is a next
		if (this->next != NULL)
		{
			// delete next, recursive, next calls destructor on next
			delete next;

			// set to null
			this->next = NULL;
		}
		
	};
};
