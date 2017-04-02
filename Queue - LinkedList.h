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

public:

	// push to the back of the queue
	void push(x& X)
	{
		// insert at the back
		queue->insert(queue->size(), X);
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

	// print method
	ostream& print(ostream& os)
	{
		// if the queue is empty indicate so
		if (queue->info == NULL) return os << "QUEUE EMPTY" << endl;

		// output the ll
		return os << (*this->queue);
	};

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
	Queue() { queue = new LinkedList<x>; };

	// copy constructor
	Queue(Queue& queue) { this->queue = queue.queue; };

	// destructor
	~Queue() { delete queue; }

};