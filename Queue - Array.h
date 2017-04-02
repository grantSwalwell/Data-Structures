#pragma once
#include <iostream>
#include "Array.h"

using namespace std;

class QueueException : public exception {};
class QueueUnderflow : public QueueException {} underflow;
class QueueOverflow : public QueueException {} overflow;

template <class x> class Queue
{

protected:

	// the array we use for the Queue
	Array<x>* queue;

	// the front of the Queue
	int back;

	// the max size of the Queue
	int max;


public:

	// pop off the top of the Queue
	x dequeue()
	{
		try
		{
			// throw if empty
			if (this->empty()) throw overflow;

			// get the front element
			x temp = (*queue)[0];

			// shift the queue back
			for (int i = 1; i < back; i++)
			{
				(*queue)[i - 1] = (*queue)[i];
			};

			// decrement rear
			back--;

			// return temp
			return temp;
		}
		catch (QueueUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "QUEUE UNDERFLOW" << "- - - - - - - -" << endl;
		};
	};

	// push onto the top of the Queue
	void enqueue(x& X)
	{
		try
		{
			// if at capacity; throw
			if (this->full()) throw overflow;

			// set back of array to new element
			(*queue)[back] = X;

			// increment back
			back++;
		}
		catch (QueueOverflow e)
		{
			cout << "- - - - - - - -" << endl << "QUEUE OVERFLOW" << "- - - - - - - -" << endl;
		};
	};

	// peak at the top of the Queue
	x& peak()
	{
		try
		{
			// if there are no elements throw
			if (top == 0) throw underflow;

			// else peak at the top element
			return (*queue)[top - 1];
		}
		catch (QueueUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "QUEUE UNDERFLOW" << "- - - - - - - -" << endl;
		}
	};

	// empty or not
	bool empty()
	{
		return back == 0;
	};

	// full or not
	bool full()
	{
		return back == max;
	};

	// return the size of the Queue
	int size()
	{
		return back;
	};

	// return capacity
	int capacity()
	{
		return max;
	};

	// overloaded assignment operator
	Queue& operator= (Queue& queue)
	{
		this->queue = queue.queue;
		top = queue.top;
		max = queue.max;
	};

	// overloaded output operator
	friend ostream& operator<< (ostream& os, Queue&	queue)
	{
		// if the Queue is empty indicate so
		if (queue.queue == NULL) return os << "EMPTY QUEUE" << endl;

		return os << (*queue.queue) << endl;

	};

	// default constructor
	Queue()
	{
		queue = new Array<x>;
		back = 0;
		max = 0;
	};

	// initializer
	Queue(int size)
	{
		queue = new Array<x>(size);
		back = 0;
		max = size;
	}

	// copy constructor
	Queue(Queue& queue)
	{
		this->queue = queue.queue;
		back = queue.back;
		max = queue.max;
	};

	// destructor
	~Queue()
	{
		if (queue != NULL)
		{
			delete queue;
			queue = NULL;
		}
	};
};
