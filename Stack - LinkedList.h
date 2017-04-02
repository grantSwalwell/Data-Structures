#pragma once
#include <iostream>
#include "LinkedList.h"

class StackException : public exception {};
class StackUnderflow : public StackException {} underflow;
class StackOverflow : public StackException {} overflow;

template <class x> class Stack
{

private:


	// the ll we use for the stack
	LinkedList<x>* stack;


public:
	
	// pop off the top of the stack
	x pop()
	{
		try
		{
			// if the stack is empty throw exception
			if (stack->info == NULL) throw underflow;

			// return the first element in the ll
			return stack->remove();
		}
		catch (StackUnderflow e)
		{
			cout << "- - - - - - - -" << endl << "STACK UNDERFLOW" << "- - - - - - - -" << endl;
		};
	};

	// push onto the top of the stack
	void push(x& X)
	{
		// add to beginning of ll
		stack->add(X);
	};

	// peak at the top of the stack
	x& peak()
	{
		return (*stack)[0];
	};

	// overloaded assignment operator
	Stack& operator= (Stack& stack)
	{
		this->stack = stack.stack;
	};

	// overloaded output operator
	friend ostream& operator<< (ostream& os, Stack& stack)
	{
		// if the stack is empty indicate so
		if (stack.stack->info == NULL) return os << "EMPTY STACK" << endl;

		return os << (*stack.stack) << endl;
		
	};

	// default constructor
	Stack()
	{
		stack = new LinkedList<x>;
	};

	// copy constructor
	Stack(Stack& stack) 
	{
		this->stack = stack.stack;
	};

	// destructor
	~Stack() 
	{
		delete stack;
	};
};