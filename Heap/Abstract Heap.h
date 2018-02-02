#pragma once
#include <iostream>
#include "Array.h"

// Implementation of a priority tree with an array
// I would have used array binary tree but I had to make that one
// for a class project so it was off and I would have to do
// a lot of refactoring anyway, array BT uses a node class as well
// which is unnecessary for this data structure

class HeapException : public exception{};

class HeapOverflow : public HeapException{} overflow;

class HeapUnderflow : public HeapException{} underflow;


template <class x> class AbstractHeap
{

protected:

	// size of the heap, number of elements not size of the array
	int size;

	// max size of the heap
	int max;

	// array holding our data
	Array<x>* heap;

	// Heapify, reheaps the data structure to satisfy ordering properties
	// values descend, root is max, leaves are smallest
	// bool is a flag to keep reheaping
	void heapify(int index, bool reheap)
	{
		// get left child
		int l = left(index);
		
		// get right child
		int r = right(index);

		// get top
		int top = index;

		// if left is less than size
		// and if heap[top] < heap[left] == flag
		// set top to left
		if (l < size && ((*heap)[top] < (*heap)[l]) == reheap) top = l;

		// if right is less than size 
		// and if heap[top] < heap[right] == flag
		// set top to right
		if (r < size && ((*heap)[top] < (*heap)[r]) == reheap) top = r;

		// if top does not equal index
		// swap heap at index with heap at top and heapify
		if (top != index)
		{
			swap(index, top);
			heapify(top, reheap);
		};
	};

	// insert helper method, order is a flag to keep reheaping up til
	// order is established
	void insert(x& element, bool order)
	{
		// check it we are at capacity
		try
		{
			if (Full()) throw overflow;
		}
		catch (HeapOverflow e)
		{
			cout << "HEAP FULL" << endl;
			return;
		}

		// get index
		int pos = size;

		// get parent index
		int par = parent(pos);

		// increment size
		size++;

		// while position is greater than 0 
		// and while parent is less than element
		// swap child with element
		// swap position with child position
		while (pos > 0 && ((*heap)[par] < element) == order)
		{
			// set heap at position to heap to parent of position
			(*heap)[pos] = (*heap)[parent(pos)];

			// set position to parent of position
			pos = parent(pos);

			// set parent to parent of position
			par = parent(pos);
		}

		// set heap at position to element
		(*heap)[pos] = element;
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
	void Delete()
	{
		// check for underflow
		try
		{
			if (Empty()) throw underflow;

		}
		catch (HeapUnderflow e)
		{
			cout << "HEAP EMPTY" << endl;

			return;
		}

		// decrement size
		size--;

		// set heap[0] to heap[size]
		if (size > 0) (*heap)[0] = (*heap)[size];

		Heapify(0);		
	};

	virtual void Heapify(int index)
	{

	};

	// heap empty
	bool Empty()
	{
		return size == 0;
	};

	// heap full
	bool Full()
	{
		return size == max;
	};

	// ostream operator
	friend ostream& operator<<(ostream& os, AbstractHeap& heap)
	{
		return heap.print(os);
	};

	// default constructor
	AbstractHeap()
	{
		size = 0;
		max = 0;
		heap = NULL;
	};

	// initializer
	AbstractHeap(int size)
	{
		this->size = 0;
		max = size;
		heap = new Array<x>(size);
	};

	~AbstractHeap()
	{
		if (heap != NULL)
		{
			delete heap;
			heap = NULL;
		}
	};



};