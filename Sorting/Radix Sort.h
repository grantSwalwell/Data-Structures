#pragma once
#include "Array.h"
#include "Queue - LinkedList.h"
#include <string>

using namespace std;

// pass array to be sorted and the magnitude of the largest number
// operaters in O(n)
Array<int>* RadixSort(Array<int>* data, int mag)
{
	// temporary sorted array
	Array<int>* temp = new Array<int>(data->size);

	// Array of queue data structure for sorting
	Array<Queue<int>*>* radix = new Array<Queue<int>*>(10);

	// initialize the radix
	for (int i = 0; i < 10; i++)
	{
		(*radix)[i] = new Queue<int>;
	}

	// divisor variable
	int k = 1;

	// for the magnitude
	for (int i = 0; i < mag; i++)
	{
		// for each element in the array
		for (int j = 0; j < data->size; j++)
		{
			// element at position j divided by divisor k =
			// place in iteration, the remainder divided by 10
			// is the last digit in the element, corresponding to queues 0-9
			// enqueue the element at that position
			(*radix)[((*data)[j] / k) % 10]->push((*data)[j]);
		}

		// increment divisor for next place
		k = k * 10;

		// index for while loop
		int x = 0;

		// for each queue in the array
		for (int j = 0; j < 10; j++)
		{
			// while queue j is not empty
			while (!(*radix)[j]->empty())
			{
				// element at x = dequeue of queue j
				(*temp)[x++] = (*radix)[j]->dequeue();
			}
		}

		// set data to temp
		data = temp;
	}
	

	return temp;

};

