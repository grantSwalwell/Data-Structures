#pragma once
#include <iostream>
#include "C:\Users\Grant\VS\Data-Structures\Array\Array.h"
// matrix class

template<class X> class Matrix
{

protected:
	
	// array of arrays, rows
	Array<Array<X>*>* mat;

	// number of rows
	int height;

	// number of columns
	int width;

	// print function for ostream
	ostream& print (ostream& os)
	{
		for (int i = 0; i < height; i++) os << (*(*mat)[i]) << endl;

		return os;
	};

public:

	int Height() { return height; };

	int Width() { return width; };

	// ostream output override
	friend ostream& operator<< (ostream& os, Matrix& mat)
	{
		return mat.print(os);
	};

	// [] operator override
	Array<X>& operator[] (int index)
	{
		return (*(*mat)[index]);
	};

	Matrix& operator=(Matrix& mat)
	{
		height = mat.Height();
		width = mat.Width();

		if (this->mat != NULL) delete this->mat;

		this->mat = new Array<Array<X>*>(height);

		for (int i = 0; i < height; i++)
		{
			(*this->mat)[i] = new Array<X>(width);

			for (int j = 0; j < width; j++)
			{
				(*(*this->mat)[i])[j] = mat[i][j];
			}
		}

		return *this;
	}

	// default constructor
	Matrix () 
	{ 
		height = 0;
		width = 0;
		mat = NULL;
	};

	// initializer
	Matrix (int size)
	{
		// set height and width
		height = size;
		width = size;

		// set rows to be array size of arrays
		mat = new Array<Array<X>*> (size);

		// initialize each row
		for (int i = 0; i < size; i++) (*mat)[i] = new Array<X> (size);
	};

	// initializer
	Matrix (int rows, int columns) 
	{
		// set height
		height = rows;

		// set width
		width = columns;

		// initialize rows
		this->mat = new Array<Array<X>*> (rows);

		// initialize each row
		for (int i = 0; i < rows; i++) (*this->mat) [i] = new Array<X> (columns);
	};

	// initializer
	Matrix (int rows, int columns, const X& val)
	{
		// set height
		height = rows;

		// set width
		width = columns;

		// initialize rows
		this->mat = new Array<Array<X>*> (rows);

		// initialize each row
		for (int i = 0; i < rows; i++) (*this->mat)[i] = new Array<X>(columns, val);
	};

	// copy constructor 
	Matrix (Matrix& mat)
	{
		height = mat.Height();
		width = mat.Width();

		this->mat = new Array<Array<X>*>(height);

		for (int i = 0; i < height; i++)
		{
			(*this->mat)[i] = new Array<X>(width);

			for (int j = 0; j < width; j++)
			{
				(*(*this->mat)[i])[j] = mat[i][j];
			}
		}
	};

	// destructor
	~Matrix ()
	{
		if (mat != NULL)
		{
			delete mat;
		}
	};

};
