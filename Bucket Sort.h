#include<iostream>
#include "Array.h"

using namespace std;

// bucket sort O(n + m) < O(m log m) if O(n) < O(m log m)
Array<int> bucketSort(Array<int>& data, int max)
{
	// number of operations
	int n = 0;

	// create temporary array with max + 1 spaces
	Array<int> x(max + 1);

	// zero initialize
	for (int i = 0; i < x.size; i++)
	{
		x[i] = 0;
	};

	// i is an index, data[i] is a number, x[data [i]] is a space for a number at index data[i]
	for (int i = 0; i < data.size; i++)
	{
		x[data[i]] = 1;
	};

	// new temporary array
	Array<int> y(data.size);

	// counting index
	int index = 0;

	// if the element is 1 use that i
	for (int i = 0; i < x.size; i++)
	{
		if (x[i] == 1)
		{
			y[index++] = i;
		}
	};

	// return the sorted array
	return y;
};
