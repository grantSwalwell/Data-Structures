#pragma once
#include <iostream>
#include "Min Heap.h"

Array<int>* HeapSort(Array<int>* data)
{
	int size = data->size;

	// make the heap
	Heap<int>* heap = new Heap<int>(size);

	// insert each element of array into heap
	for (int i = 0; i < size; i++)
	{
		heap->Insert((*data)[i]);
	}

	// set each element of array to be min, delete min
	for (int i = 0; i < size; i++)
	{
		(*data)[i] = heap->Min();
		heap->Delete();
	}

	// return array
	return data;

}