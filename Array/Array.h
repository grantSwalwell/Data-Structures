#pragma once
#include <iostream>
using namespace std;

// array exception base class
class ArrayException : public exception {};
// array bounds exception
class ArrayIndexException : public ArrayException {} indexException;
// array memory exception
class ArrayMemoryException : public ArrayException {};

// Array data structure, template of class type x
template<class x> class Array
{

protected:

	// data of the array
	x* data;

	// array size
	int size;

	// print method
	virtual ostream& print(ostream& os)
	{
		// for each element
		for (int i = 0; i < this->size; i++)
		{
			os << (*this)[i] << " ";
		}

		return os;
	};

public:

	// return size
	int Size()
	{
		return size;
	}

	// find an element in a sorted array
	int binarySearch(x find, int left, int right)
	{
		// the result
		int result = 0;

		// middle index value
		int mid;

		// middle value
		x midval;

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
				return binarySearch(find, mid + 1, right);
			}
			else return binarySearch(find, left, mid); // else search lower half
		}
		else // base case
		{
			// if left and right are the same and if data[left] < find, it's position after left, else it is left
			if (left == right && data[left] < find) result = left + 1;
			else result = left;
		}

		return result;
	}

	// contains method                  
	bool contains(const x& value)
	{
		bool result = false;

		for (int i = 0; i < size; i++)
		{
			if (data[i] == value) result = true;
		}

		return result;
	};

	// get the index for this value  
	int index(const x& value)
	{
		if (contains(value))
		{
			for (int i = 0; i < size; i++)
			{
				if (data[i] == value) return i;
			}
		}
		else return -1;
	}


	// square bracket operator override, takes place of get and set
	x& operator[] (int index) const throw()
	{
		try
		{
			// if index less than 0 or greater than size
			if (index >= size || index < 0) throw indexException;

			// return data at index
			return data[index];

		}
		catch (ArrayIndexException e) {};
	};

	// overloaded = operator for Array type
	Array& operator= (const Array& data)
	{
		this->size = data.size;

		for (int i = 0; i < this->size; i++) this->data[i] = data[i];

		return *this;
	};

	// output ostream override
	friend ostream& operator<< (ostream& os, Array& output)
	{
		// return ostream, call print
		return output.print(os);
	};

	// default constructor
	Array() { size = 0; this->data = NULL; };

	// initializer 
	Array(int size)
	{
		this->size = size;
		this->data = new x[size];
	};

	// initializer
	Array(x* data, int size)
	{
		this->size = size;
		this->data = new x[size];

		for (int i = 0; i < size; i++) this->data[i] = data[i];
	};

	// initializer 2
	Array(int size, const x& val)
	{
		this->size = size;

		data = new x[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = val;
		}
	}

	// copy constructor
	Array(Array& old)
	{
		size = old.size;
		
		data = new x[size];

		for (int i = 0; i < size; i++) this->data[i] = old.data[i];
	}

	// destructor
	~Array()
	{
		if (data != NULL) delete data; 
		data = NULL;
	};
};

