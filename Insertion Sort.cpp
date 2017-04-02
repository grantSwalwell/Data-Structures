#include <iostream>
#include "Array.h"

using namespace std;

// insertion sort O(n^2)
Array<int> insertionSort(Array<int>& data)
{
	// first index
	int i = 0;

	// second index
	int j = 0;

	// temp value 
	int temp = 0;

	for (i; i < data.size; i++)
	{
		// set j to i
		j = i;

		// while j is > 0 and the element to the left is greater
		while (j > 0 && data[j] < data[j - 1])
		{
			temp = data[j];

			data[j] = data[j - 1];

			data[j - 1] = temp;

			j--;
		} // switch j and j - 1
	}

	return data;
}