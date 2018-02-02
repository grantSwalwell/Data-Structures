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

	// the front of the queue
	int front;

	// the back of the Queue
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
			x temp = (*queue)[front + 1];
			
			// increment front
			front++;

			// set front
			front = front % queue->size;

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

			// if back is at the end of the array set back to (back + 1) modulus max, the front of the array
			if (back + 1 == queue->size)
			{
				back = (back + 1) % queue->size;
				(*queue)[back] = X;
			}
			// else set queue[back] and increment back
			else
			{
				back++;
				back = back % queue->size;
				(*queue)[back] = X;	
			}

			
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
		return front == back;
	};

	// full or not
	bool full()
	{
		// if back + 1 = front or if (back + 1) modulus size
		return (back + 1 == front) || ((back + 1) % queue->size == front);
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

	// get front
	int Front()
	{
		return front;
	};

	// get back
	int Back()
	{
		return back;
	};

	// overloaded assignment operator
	Queue& operator= (Queue& queue)
	{
		this->queue = queue.queue;
		front = queue.front;
		top = queue.top;
		max = queue.max;
	};

	// overloaded output operator
	friend ostream& operator<< (ostream& os, Queue&	queue)
	{
		// if the Queue is empty indicate so
		if (queue.queue == NULL) return os << "EMPTY QUEUE" << endl;

		return os << "Front: " << queue.Front() << ", Back: " << queue.Back() << ", Queue: " << (*queue.queue) << endl;

	};

	// default constructor
	Queue()
	{
		queue = NULL;
		front = 0;
		back = 0;
		max = 0;
	};

	// initializer
	Queue(int size)
	{
		queue = new Array<x>(size + 1);
		front = 0;
		back = 0;
		max = size + 1;
	}

	// copy constructor
	Queue(Queue& queue)
	{
		this->queue = queue.queue;
		front = queue.front;
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
