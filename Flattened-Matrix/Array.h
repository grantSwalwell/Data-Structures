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

	// CLEAN ARRAY, DEFAULT FALSE, TRUE WHEN WE WANT RIGHT HAND SIDE OF ASSIGNMENT OP TO GO AWAY
	bool CLEAN;

	// PRINT, OSTREAM HELPER METHOD
	virtual ostream& print(ostream& os) { for (int i = 0; i < this->size; i++) os << data[i] << " "; return os; };

public:

	// GET SIZE
	int Size() { return size; }

	// CONTAINS VALUE
	bool Contains(const X& value);

	// GET INDEX OF VALUE
	int Index(const X& value);

	// GET CLEAN FLAG
	bool Clean() { return CLEAN; }

	// SETS CLEAN FLAG, WILL DELETE ARRAY WHEN USED ON RIGHT SIDE OF ASSIGNMENT STATEMENT, USE CAUTIOUSLY
	void Clean(bool val) { CLEAN = val;	}

	// DEFAULT CONSTRUCTOR
	Array();

	// SIZE INITIALIZER
	Array(int size);

	// VALUE INITIALIZER
	Array(int size, const X& val);

	// ARRAY INITIALIZER
	Array(int size, X* data);

	// COPY CONSTRUCTOR
	Array(Array& old);

	// DESTRUCTOR
	~Array() { if (data != NULL) delete[] data; data = NULL; };

	// ASSIGNMENT OPERATOR
	Array& operator= (Array& right);

	// GET AND SET OPERATOR
	X& operator[] (int index) const throw();

	// OSTREAM OPERATOR
	friend ostream& operator<< (ostream& os, Array& output) { return output.print(os); }
};

//////////////////// CONSTRUCTORS ////////////////////

// DEFAULT CONSTRUCTOR
template <class X> Array<X>::Array()
{
	size = 0;
	data = NULL;
	CLEAN = false;
};

// SIZE INITIALIZER
template <class X> Array<X>::Array(int size)
{
	this->size = size;
	data = new X[size];
	CLEAN = false;
};

// VALUE INITIALIZER
template <class X> Array<X>::Array(int size, const X& val)
{
	this->size = size;
	data = new X[size];
	for (int i = 0; i < size; i++) data[i] = val;
	CLEAN = false;
}

// ARRAY INITIALIZER
template <class X> Array<X>::Array(int size, X* data)
{
	this->size = size;
	this->data = new X[size];
	for (int i = 0; i < size; i++) this->data[i] = data[i];
	CLEAN = false;
};

// COPY CONSTRUCTOR
template <class X> Array<X>::Array(Array& old)
{
	size = old.Size();
	data = new X[size];
	for (int i = 0; i < size; i++) data[i] = old[i];
	CLEAN = old.Clean();
}

//////////////////// ASSIGNMENT OPERATOR ////////////////////
template <class X> Array<X>& Array<X>::operator= (Array& right)
{
	// check if size is equal or data is null
	if (size != right.Size() || data == NULL)
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

	// check flag for cleaning, when we want the right hand array to go away
	if (right.Clean()) delete &right;

	// return this
	return *this;
};

//////////////////// GET AND SET OPERATOR ////////////////////
template <class X> X& Array<X>::operator[] (int index) const throw()
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

//////////////////// CONTAINS AND INDEX ///////////////////
template <class X> bool Array<X>::Contains(const X& value)
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

template <class X> int Array<X>::Index(const X& value)
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

//////////////////// ARRAY MATH OPERATIONS ////////////////////

// ADDITION OPERATOR
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

		// set CLEAN flag to true
		C->Clean(true);

		// dereference and return C
		return *C;
	}
	catch(ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl;}
}

// SUBTRACTION OPERATOR
template <class X> Array<X>& operator-(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch
		if (A.Size() != B.Size()) throw dimensionException;

		// Allocate new array
		Array<X>* C = new Array<X>(A.Size());

		// add up A and B
		for (int i = 0; i < C->Size(); i++) (*C)[i] = A[i] - B[i];

		// set CLEAN flag to true
		C->Clean(true);

		// dereference and return C
		return *C;
	}
	catch (ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl;}
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

		// set CLEAN flag to true
		C->Clean(true);

		// dereference and return C
		return *C;
	}
	catch (ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl; }
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
	catch (ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl; }
}

// MINUS EQUALS OPERATOR
template <class X> Array<X>& operator-=(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch
		if (A.Size() != B.Size()) throw dimensionException;

		// subtract A and B
		for (int i = 0; i < A.Size(); i++) A[i] -= B[i];

		// return A
		return A;
	}
	catch (ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl; }
}

// TIMES EQUALS OPERATOR
template <class X> Array<X>& operator*=(Array<X>& A, Array<X>& B) throw()
{
	try
	{
		// check for dimension mismatch
		if (A.Size() != B.Size()) throw dimensionException;
		
		// multiply A and B
		for (int i = 0; i < A.Size(); i++) A[i] = A[i] * B[i];

		// return A
		return A;
	}
	catch (ArrayDimensionException e) { cout << "DIMENSION MISMATCH" << endl; }
}



