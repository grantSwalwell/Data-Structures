#pragma once
#include <iostream>
#include "Array.h"

using namespace std;

class StackException : public exception {};
class StackUnderflow : public StackException {} underflow;
class StackOverflow : public StackException {} overflow;

template <class x> class Stack
{

protected:

	// the array we use for the stack
	Array<x>* stack;

	// the top of the stack
	int top;

	// the max size of the stack
	int max;


public:

	// pop off the top of the stack
	x pop()
	{
		try
		{
			// if empty throw
			if (this->empty()) throw underflow;

			// decrement top
			top--;

			// return top
			return (*stack)[top];

		}
		catch (StackUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "STACK UNDERFLOW" << "- - - - - - - -" << endl;
		};
	};

	// push onto the top of the stack
	void push(x& X)
	{
		try
		{
			// if at capacity; throw
			if (this->full()) throw overflow;
			
			// add new element
			(*stack)[top] = X;

			// increment top
			top++;

		}
		catch (StackOverflow e)
		{
			cout << "- - - - - - - -" << endl << "STACK OVERFLOW" << "- - - - - - - -" << endl;
		};
	};

	// peak at the top of the stack
	x& peak()
	{
		try
		{
			// if there are no elements throw
			if (top == 0) throw underflow;

			// else peak at the top element
			return (*stack)[top - 1];
		}
		catch (StackUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "STACK UNDERFLOW" << "- - - - - - - -" << endl;
		}
	};

	// empty or not
	bool empty()
	{
		return top == 0;
	};

	// full or not
	bool full()
	{
		return top == max;
	};

	// return the size of the stack
	int size()
	{
		return top;
	};

	// return capacity
	int capacity()
	{
		return max;
	};

	// overloaded assignment operator
	Stack& operator= (Stack& stack)
	{
		this->stack = stack.stack;
		top = stack.top;
		max = stack.max;
	};

	// overloaded output operator
	friend ostream& operator<< (ostream& os, Stack& stack)
	{
		// if the stack is empty indicate so
		if (stack.stack == NULL) return os << "EMPTY STACK" << endl;

		return os << (*stack.stack) << endl;

	};

	// default constructor
	Stack()
	{
		stack = new Array<x>;
		top = 0;
		max = 0;
	};

	// initializer
	Stack(int size)
	{
		stack = new Array<x>(size);
		top = 0;
		max = size;
	}

	// copy constructor
	Stack(Stack& stack)
	{
		this->stack = stack.stack;
		top = stack.top;
		max = stack.max;
	};

	// destructor
	~Stack()
	{
		if (stack != NULL)
		{
			delete stack;
			stack = NULL;
		}
	};
};
