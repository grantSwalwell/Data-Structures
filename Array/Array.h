#pragma once
#include <iostream>
using namespace std;

// array exception base class
class ArrayException : public exception {};
// array bounds exception
class ArrayIndexException : public ArrayException {} indexException;
// array size mismatch
class ArrayDimensionException : public ArrayException {} dimensionException;

// Array data structure, template of class type X
template<class X> class Array
{

protected:

	// ARRAY SIZE

	int size;

	// ARRAY DATA

	X* data;

	// PRINT, OSTREAM HELPER METHOD

	virtual ostream& print(ostream& os)
	{
		// for each element
		for (int i = 0; i < this->size; i++)
		{
			os << data[i] << " ";
		}

		return os;
	};

public:

	// GET SIZE

	int Size() { return size; }

	// CONTAINS VALUE

	bool Contains(const X& value)
	{
		// scan array

		for (int i = 0; i < size; i++)
		{
			// if found return true

			if (data[i] == value) return true;
		}

		// else return false

		return false;
	};

	// GET INDEX OF VALUE

	int Index(const X& value)
	{
		// check if we contain this value

		if (Contains(value))
		{
			// scan array

			for (int i = 0; i < size; i++)
			{
				// return index

				if (data[i] == value) return i;
			}
		}
		else return -1; // else return -1
	}

	// INDEX OPERATOR

	X& operator[] (int index) const throw()
	{
		try
		{
			// if index less than 0 or greater than size
			if (index >= size || index < 0) throw indexException;

			// return data at index
			return data[index];

		}
		catch (ArrayIndexException e) { cout << "INDEX OUT OF BOUNDS" << endl; };
	};

	// ASSIGNMENT OPERATOR

	Array& operator= (Array& right)
	{
		if (size != right.Size())
		{
			// copy over the new size

			size = right.Size();

			// if the old array is allocated delete it

			if (data != NULL) delete[] data;

			// allocate new size

			data = new X[size];
		}

		// copy over new array

		for (int i = 0; i < size; i++) data[i] = right[i];

		// return this

		return *this;
	};

	// OSTREAM OPERATOR

	friend ostream& operator<< (ostream& os, Array& output)
	{
		// return ostream, call print
		return output.print(os);
	};

	// DEFAULT CONSTRUCTOR

	Array()
	{ 
		size = 0; 
		data = NULL;
	};

	// SIZE INITIALIZER

	Array(int size) 
	{ 
		this->size = size; 
		this->data = new X[size];
	};

	// VALUE INITIALIZER

	Array(int size, const X& val)
	{
		this->size = size;

		data = new X[size];

		for (int i = 0; i < size; i++) data[i] = val;
	}

	// ARRAY INITIALIZER

	Array(int size, X* data)
	{
		this->size = size;

		this->data = new X[size];

		for (int i = 0; i < size; i++) this->data[i] = data[i];
	};

	// COPY CONSTRUCTOR

	Array(Array& old)
	{
		size = old.Size();
		
		data = new X[size];

		for (int i = 0; i < size; i++) data[i] = old[i];
	}

	// DESTRUCTOR

	~Array()
	{
		if (data != NULL) delete[] data; 
		
		data = NULL;
	};
};


// ARRAY ADDITION OPERATOR

template <class X> Array<X>& operator+(Array<X>& A, Array<X>& B) throw()
{
	try 
	{
		// check for dimension mismatch

		if (A.Size() != B.Size()) throw dimensionException;

		// Allocate new array

		Array<X>* C = new Array<X>(A.Size());

		// add up A and B

		for (int i = 0; i < C->Size(); i++) (*C)[i] = A[i] + B[i];

		// dereference and return C

		return *C;
	}
	catch(ArrayDimensionException e)
	{
		cout << "DIMENSION MISMATCH" << endl;
	}
}

// PLUS EQUALS OPERATOR

template <class X> Array<X>& operator+=(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch

		if (A.Size() != B.Size()) throw dimensionException;

		// add up A and B

		for (int i = 0; i < A.Size(); i++) A[i] += B[i];

		// return A

		return A;
	}
	catch (ArrayDimensionException e)
	{
		cout << "DIMENSION MISMATCH" << endl;
	}
}

// MULTIPLICATION ELEMENT WISE OEPRATOR

template <class X> Array<X>& operator*(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch

		if (A.Size() != B.Size()) throw dimensionException;

		// Allocate new array

		Array<X>* C = new Array<X>(A.Size());

		// multiply A and B

		for (int i = 0; i < C->Size(); i++) (*C)[i] = A[i] * B[i];

		// dereference and return C

		return *C;
	}
	catch (ArrayDimensionException e)
	{
		cout << "DIMENSION MISMATCH" << endl;
	}
}

// TIMES EQUALS OPERATOR

template <class X> Array<X>& operator*=(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch

		if (A.Size() != B.Size()) throw dimensionException;

		// add up A and B

		for (int i = 0; i < A.Size(); i++) A[i] = A[i] * B[i];

		// dereference and return C

		return A;
	}
	catch (ArrayDimensionException e)
	{
		cout << "DIMENSION MISMATCH" << endl;
	}
}



