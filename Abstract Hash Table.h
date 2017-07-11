#pragma once
#include <iostream>

using namespace std;

class HashException : public exception { };
class HashOutOfBounds : public HashException { } bounds;
class HashNotFound : public HashException { } notFound;
class HashMemory : public HashException { } memory;


template <class x> class AbstractHashTable
{

protected:

	virtual int hash(const x& element) = NULL
	{
	};

	ostream& print(ostream& os) = NULL
	{
	};

public:

	virtual x Find(const x& element) = NULL
	{
	};

	virtual void Insert(const x& element) = NULL
	{
	};

	virtual void Remove(const x& element) = NULL
	{
	};

	virtual bool Collision(int index) = NULL
	{
	};

	virtual bool Empty() = NULL
	{
	};

	virtual int Capacity()
	{
	};

	virtual int Size()
	{
	};

	virtual x& operator[] (int index) = NULL 
	{
	};
	
	virtual friend ostream& operator<< (ostream& os, AbstractHashTable& table) = NULL
	{
		return table.print(os);
	};

	// destructor
	virtual ~AbstractHashTable()
	{
	};
};