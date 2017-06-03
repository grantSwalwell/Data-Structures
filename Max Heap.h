#pragma once
#include <iostream>
#include "Array.h"
#include "Binary Search.h"

// Implementation of a priority tree with an array
// I would have used array binary tree but I had to make that one
// for a class project so it was off and I would have to do
// a lot of refactoring anyway, array BT uses a node class as well
// which is unnecessary for this data structure

template <class x> class Heap
{

protected:

	// size of the heap
	int size;

	// array holding our data
	Array<x>* heap;


	// Heapify, reheaps the data structure to satisfy ordering properties
	// values descend, root is max, leaves are smallest
	void Heapify(int index)
	{

	};

	// Swap values
	void Swap(int index1, int index2)
	{

	};

	// Remove value helper method
	void Remove(int index)
	{

	};

	// helper method for ostream
	ostream& print(ostream& os)
	{
		os << *heap << endl;

		return os;
	};


public:

	// insert value into heap
	void Insert(x& data)
	{

	};

	// delete max value
	x Delete()
	{

	};

	// ostream operator
	friend ostream& operator<<(ostream& os, Heap<x>& heap)
	{
		return heap.print(os);
	}

	// default constructor
	Heap()
	{
		size = 0;
		heap = NULL;
	};

	// initializer
	Heap(int size)
	{
		this->size = 0;
		heap = new Array<x>(size);
	};

	// array initializer
	Heap(Array<x>& data)
	{
		size = data.size;
		heap = &data;
	};

	// array pointer initializer
	Heap(Array<x>* data)
	{
		size = data->size;
		heap = data;
	}

	~Heap()
	{
		if (heap != NULL)
		{
			delete heap;
			heap = NULL;
		}
	};



};