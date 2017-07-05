#pragma once
#include <iostream>
#include <string>
#include "Array.h"

// string object class
class String : public Array<char>
{

protected:



	// get index helper method
	int index(char& character, int start)
	{
		return Array<char>::index(character);
	}


	// print method
	virtual ostream& print(ostream& os)
	{
		// for each element
		for (int i = 0; i < this->size; i++)
		{
			os << (*this)[i];
		}

		return os;
	};

public:


	// concatenate string
	void concatenate(String& string)
	{
		int leng = length();
		
		int max = string.length();

		bool overflow = false;

		if (size - 1 < max + leng)
		{
			overflow = true;
			max = size - 1 - leng;
		}


		strncpy(data + leng, string.data, max);
		

		// null terminate last char
		data[max + leng] = '\0';

	}

	// get length of string
	int length() const
	{
		return strlen(data);
	}

	// index position of char
	int index(char& character)
	{
		return index(character, 0);
	}

	// contains char
	bool contains(char& character)
	{
		return Array<char>::contains(character);
	}

	// insert character 

	// remove character

	// get substring

	// addition operator
	String operator+ (String& string)
	{
		String temp(length() + string.length());
		temp = *this;
		temp.concatenate(string);
		return temp;

		//concatenate(string);
	}

	// subtraction operator

	// equality operator

	// less than operator

	// greater than operator

	// bracket operator
	char& operator[](int index)
	{
		return Array<char>::operator[](index);
	}

	// assignment operator
	void operator= (const String& string)
	{

		// if we have a default string call parent operator
		if (size - 1 == 0)
		{
			Array<char>::operator= (string);
			return;
		}

		// get max size
		int max = string.length();

		// overflow variable
		bool overflow = false;

		// if size is less than max we have overflow
		if (size - 1 < max)
		{
			overflow = true;

			max = size - 1;
		}

		strncpy(data, string.data, max);

		data[max] = '\0';
	}

	// default constructor
	String() : Array<char>(1, '\0')
	{
	};

	// size initializer
	String(int size) : Array<char>(size + 1, '\0')
	{
	};

	// char array initializer
	String(char* data) : Array<char>(strlen(data) + 1)
	{
		strcpy(this->data, data);
	}

	// copy constructor
	String(String& string) : Array<char> (string)
	{
	};

	// destructor
	virtual ~String()
	{
	};

};