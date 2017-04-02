#include <iostream>
#include "Array.h"

// selection sort O(n^2)
Array<int> selectionSort(Array<int>& data)
{
	// first index
	int i = 0;

	// second index
	int j = 1;

	// min value index
	int min = i;

	// temporary value
	int temp = 0;

	// for each i
	for (i; i < data.size - 1; i++)
	{
		// set min to current position
		min = i;

		// for each j, check if data[j] is less than data[i], if so set min to j
		for (j = i + 1; j < data.size; j++) if (data[min] > data[j]) min = j;

		// if i is not the min a new min has been found
		// switch data [i] and data [min]
		if (min != i)
		{
			temp = data[i];
			data[i] = data[min];
			data[min] = temp;
		}
	}



	// return sorted array
	return data;
};