#pragma once
#include <iostream>
#include "Array.h"
// matrix class

template<class x> class Matrix
{

protected:
	
	// array of arrays, rows
	Array<Array<x>*>* rows;

public:

	// number of rows * number of clumns
	int size;

	// number of rows
	int height;

	// number of columns
	int width;

	// print function for ostream
	ostream& print (ostream& os)
	{
		for (int i = 0; i < rows->size; i++) os << (*(*rows) [i]) << endl;

		return os;
	};

	// ostream output override
	friend ostream& operator<< (ostream& os, Matrix& mat)
	{
		return mat.print (os);
	};


	// [] operator override
	Array<x>& operator[] (int index)
	{
		// retrieve row at index
		if (index >= 0 && index < rows->size) return (*(*rows) [index]);
	};

	// default constructor
	Matrix () { rows = NULL; };

	// initializer
	Matrix (int size)
	{
		// set size
		this->size = size * size;

		// set height and width
		height = size;
		width = size;

		// set rows to be array size of arrays
		rows = new Array<Array<x>*> (size);

		// initialize each row
		for (int i = 0; i < size; i++) (*rows) [i] = new Array<x> (size);
	};

	// initializer
	Matrix (int rows, int columns) 
	{
		// set size
		this->size = rows * columns;

		// set height
		height = rows;

		// set width
		width = columns;

		// initialize rows
		this->rows = new Array<Array<x>*> (rows);

		// initialize each row
		for (int i = 0; i < rows; i++) (*this->rows) [i] = new Array<x> (columns);
	};

	// copy constructor 
	Matrix (Matrix& mat) {};

	// destructor
	~Matrix () { delete rows; };


};
