#pragma once
#include <iostream>
#include "LinkedList.h"

class QueueException : public exception {};
class QueueUnderflow : public QueueException {} underflow;
class QueueOverflow : public QueueException {} overflow;



template <class x> class Queue
{

private:

	// the ll acting as the queue 
	LinkedList<x>* queue;
		
	// end of the line
	LinkedList<x>* end;

	// print method
	ostream& print(ostream& os)
	{
		// if the queue is empty indicate so
		if (queue->info == NULL) return os << "QUEUE EMPTY" << endl;

		// output the ll
		return os << (*this->queue);
	};

public:

	// push to the back of the queue
	void push(x& X)
	{
		// insert at the back
		//queue->insert(last, X);
		if (queue->empty())         // if the queue is empty add element, set end to queue
		{
			// add to empty LL
			queue->add(X);
			
			// queue is the new end
			end = queue;
		}
		else // else set next of end to be a new LL element, set end to end->next for new end
		{
			// set new element
			end->next = new LinkedList<x>(X);
			
			// set new end
			end = end->next;
		};
				
	};

	// dequeue the front of the queue 
	x dequeue()
	{
		try
		{
			// if queue is empty throw exception
			if (queue->info == NULL) throw underflow;
						
			// remove from the front
			return queue->remove();

		}
		catch (QueueUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "QUEUE UNDERFLOW" << endl << "- - - - - - - -" << endl;
		};
	};

	// peak at the front of the queue 
	x front()
	{
		return (*queue)[0];
	};

	// peak at the back of the queue 
	x back()
	{
		return (*queue)[queue->size() - 1];
	};

	// is empty
	bool empty()
	{
		return queue->empty();
	}

	//  equality operator
	Queue& operator= (Queue queue)
	{
		this->queue = queue.queue;
	};

	// output operator
	friend ostream& operator<<(ostream& os, Queue& queue)
	{
		// call print
		return queue.print(os);
	};

	// default constructor
	Queue()
	{
		queue = new LinkedList<x>; 
		end = queue;
	};

	// copy constructor
	Queue(Queue& queue)
	{
		this->queue = queue.queue; 
		end = queue.end;
	};

	// destructor
	~Queue() { delete queue; }

};