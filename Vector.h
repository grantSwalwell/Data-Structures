#pragma once
#include <iostream>
#include "Array.h"

template<class x> class Vector : public Array<x> 
{
private:
		

public:

	// number of elements
	int elements;

	// increment facotr
	int increment;
		
	// insert at index   
	void insert (int index, const x& element)
	{
		try
		{
			// if index is less than 0 or greater than size
			if (index < 0 || index > this->size) throw indexException;

			// if the array is at capacity
			if (elements + 1 >= this->size || this->size == 0) resize (this->size + this->increment);

			// increment the number of elements 
			this->elements++;

			// move over elements to the right of index starting at the highest index to make a space
			for (int i = elements - 1; i > index; i--) this->data [i] = this->data [i - 1];

			// insert the element
			this->data [index] = element;
		}
		catch (ArrayIndexException e) {}
	}

	// add item to end
	void add (const x& element)
	{
		// insert at end
		insert (elements, element);
	}

	// resize to size   
	void resize (int size)
	{
		// current number of elements
		int mag = this->elements;

		// if current size is greater than new size
		if (mag > size) mag = size;

		// temporary array
		x* temp = new x [size];

		// NULL initialize
		//this->initialize (temp, size);

		// if data isn't NULL
		if (this->data != NULL) 
		{
			// copy over the old
			for (int i = 0; i < mag; i++) temp [i] = this->data [i];

			// delete the old
			delete this->data;
		}

		// set data to temp
		this->data = temp;

		// set the new size
		this->size = size;

		// if there are less elements now than ealier
		//if (this->elements > mag) this->elements = mag;

	};
	
	// remove element at index
	x& remove (int index)
	{

		for (int i = index; i < this->size; i++) (*this) [i] = (*this) [i + 1];

		this->resize (this->size - 1);

		elements--;

		return data [index];
	}

	// equality for Vector type // TODO: 
	Vector& operator= (Vector& vec)
	{
		// set size and increment
		this->size = vec.size;
		this->increment = vec.increment;

		// if new size is greater than current
		if (this->size < vec.size) resize (vec.size);

		// copy over elements
		for (int i = 0; i < vec.size; i++) this->data [i] = vec [i];

		return *this;


	};

	// equality operator for primitive array // TODO:
	Vector& operator= (x* data) 
	{
		// we don't know the size so we'll just copy over the elements til it's full
		for (int i = 0; i < this->size; i++) this->data [i] = data [i];

		return *this;
	};

	// bracket operator override
	x& operator[] (int index)
	{
		if (index >= 0 && index < this->size) return this->data [index];
	}

	// default constructor
	Vector () : Array () 
	{
		this->increment = 1;
		this->elements = 0;
	};

	// size initializer
	Vector (int size) : Array (size)
	{
		this->increment = (size + 1) / 2;
		this->elements = 0;
	};

	// data initializer
	Vector (x* data, int size) : Array (data, size)
	{
		this->increment = (size + 1) / 2;
		this->elements = size;
	};

	// copy constructor
	Vector (Vector& vec) : Array (vec)
	{
		this->increment = (this->size + 1) / 2;
	};

	// destructor
	~Vector () { };

	

};