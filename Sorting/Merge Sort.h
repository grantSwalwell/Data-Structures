#include <iostream>
#include "Array.h"

using namespace std;

// merge O(a + b), merges two sorted arrays into one larger sorted array
Array<int> merge(Array<int>& a, Array<int>& b)
{
	Array<int> c(a.Size() + b.Size()); // temporary combined array

	int i = 0;
	int j = 0;
	int k = 0;

	// pick smaller of a0 b0 assign to c0
	// pick smaller of a0/a1 and b0/b1 to c1

	// while a and b arent fully copied
	while (i < a.Size() && i < b.Size())
	{
		if (a[i] < b[j]) c[k++] = a[i++];
		else c[k++] = b[j++];
	}

	// while a isn't fully copied
	while (i < a.Size())
	{
		c[k++] = a[i++];
	}

	// while b isn't fully copied
	while (j < b.Size())
	{
		c[k++] = b[j++];
	}

	return c;
} //  

// merge for merge sort
void merge(Array<int>& data, int left, int mid, int right)
{
	// sorted array
	Array<int>* sorted = new Array<int>(data.Size()); // temporary combined array

													// indexes
	int i = left;
	int j = mid + 1;
	int k = left;

	// while a and b arent fully copied
	while (i <= mid && j <= right)
	{
		if (data[i] < data[j]) (*sorted)[k++] = data[i++];
		else (*sorted)[k++] = data[j++];
	}

	// while a isn't fully copied
	while (i <= mid)
	{
		(*sorted)[k++] = data[i++];
	}

	// while b isn't fully copied
	while (j <= right)
	{
		(*sorted)[k++] = data[j++];
	}

	// copy over the elements to data
	for (i = left; i < k; i++) data[i] = (*sorted)[i];

	return;
}

// merge sort 
void mergeSort(Array<int>& data, int left, int right)
{
	// middle value
	int mid;

	// if left < right
	if (left < right)
	{
		// mid value = (left + right) / 2
		mid = (left + right) / 2;

		// merge sort from left to mid
		mergeSort(data, left, mid);

		// merge sort from mid + 1 to right
		mergeSort(data, mid + 1, right);

		// merge
		merge(data, left, mid, right);
	}

	return;
}
