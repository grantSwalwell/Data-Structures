#pragma once
#include "Abstract Heap.h"

// Implementation of a priority tree with an array
// I would have used array binary tree but I had to make that one
// for a class project so it was off and I would have to do
// a lot of refactoring anyway, array BT uses a node class as well
// which is unnecessary for this data structure


template <class x> class Heap : public AbstractHeap<x>
{

protected:


public:

	// get size
	int Size()
	{
		return this->size;
	}

	// get max
	int Max()
	{
		return this->max;
	}

	// insert value into heap
	void Insert(x& data)
	{
		// for a max heap pass true to insert
		insert(data, false);
	};

	// heapify
	void Heapify(int index)
	{
		heapify(index, false);
	};

	// get max value
	x Min()
	{
		return (*heap)[0];
	};

	// default constructor
	Heap() : AbstractHeap()
	{
	};

	// initializer
	Heap(int size) : AbstractHeap(size)
	{
	};

	// deconstructor
	~Heap()
	{
		~AbstractHeap();
	};

};