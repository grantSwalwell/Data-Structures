#pragma once
#include <iostream>
#include <string>
#include "Array.h"

// string object class
class String : Array<char>
{

protected:




public:



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
	String(String& string) : Array<char> (str)
	{
	};

	// destructor
	~String()
	{
	};

};