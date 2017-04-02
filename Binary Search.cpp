#include <iostream>
#include "Vector.h"

using namespace std;

// binary search, uses a Vector, because that's how it was in the book
int binarySearch(Vector<int>& data, int find, int left, int right)
{
	// the result
	int result = 0;

	// middle index value
	int mid;

	// middle value
	int midval;

	// recursive case
	if (left < right)
	{
		// mid = left + right /2
		mid = (left + right) / 2;

		// middle value is data[mid]
		midval = data[mid];

		// if find == midval we are done return mid + 1
		if (find == midval) return mid + 1;
		else if (midval < find) // if midval < find search upper half
		{
			return binarySearch(data, find, mid + 1, right);
		}
		else return binarySearch(data, find, left, mid); // else search lower half
	}
	else // base case
	{
		// if left and right are the same and if data[left] < find, it's position after left, else it is left
		if (left == right && data[left] < find) result = left + 1;
		else result = left;
	}

	return result;
};