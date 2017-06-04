#pragma once
#include <iostream>
#include "Array.h"
#include "Binary Search.h"

// Implementation of a priority tree with an array
// I would have used array binary tree but I had to make that one
// for a class project so it was off and I would have to do
// a lot of refactoring anyway, array BT uses a node class as well
// which is unnecessary for this data structure

template <class x> class AbstractHeap
{

protected:

	// size of the heap, number of elements not size of the array
	int size;

	// array holding our data
	Array<x>* heap;

	// Heapify, reheaps the data structure to satisfy ordering properties
	// values descend, root is max, leaves are smallest
	// bool is a flag to keep reheaping
	void heapify(int index, bool reheap)
	{

	};

	// insert helper method, order is a flag to keep reheaping up til
	// order is established
	void insert(x& element, bool order)
	{
		// increment size
		size++;

		// get index
		int pos = size;

		// while position is greater than 0 
		// and while parent is less than element
		// swap child with element
		// swap position with child position
		while (pos > 0 && (*heap)[(pos - 1) / 2] < data)
		{
			// set heap at position to heap to parent of position
			//(*heap)[pos] = (*heap)[(pos - 1) / 2];

			// set position to parent of position
			//pos = (pos - 1) / 2;
		}

		// set heap at position to element
		//(*heap)[pos] = data;
	}

	// position of left child of index
	int left(int index)
	{
		return (2 * index) + 1;
	};

	// position of right child of index
	int right(int index)
	{
		return (2 * index) + 2;
	};

	int parent(int index)
	{
		return (index - 1) / 2;
	};

	// Swap values
	void swap(int index1, int index2)
	{
		// hold index 1
		x temp = (*heap)[index1];

		// set index 1 to index 2
		(*heap)[index1] = (*heap)[index2];

		// set index 2 to temp
		(*heap)[index2] = temp;
	};

	// helper method for ostream
	ostream& print(ostream& os)
	{
		os << *heap << endl;

		return os;
	};

public:

	// insert value into heap
	virtual void Insert(x& data)
	{
	};

	// delete max value
	virtual x Delete()
	{
	};

	// ostream operator
	friend ostream& operator<<(ostream& os, Heap<x>& heap)
	{
		return heap.print(os);
	}

	// default constructor
	AbstractHeap()
	{
		size = 0;
		heap = NULL;
	};

	// initializer
	AbstractHeap(int size)
	{
		this->size = 0;
		heap = new Array<x>(size);
	};

	// array initializer
	AbstractHeap(Array<x>& data)
	{
		size = data.size;
		heap = &data;
	};

	// array pointer initializer
	AbstractHeap(Array<x>* data)
	{
		size = data->size;
		heap = data;
	}

	~AbstractHeap()
	{
		if (heap != NULL)
		{
			delete heap;
			heap = NULL;
		}
	};



};