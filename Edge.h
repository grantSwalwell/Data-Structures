#pragma once
#include <iostream>

using namespace std;

// edge for use by abstract neural net
// has a weight 


class EdgeException : public exception
{
};

class EdgeWeightException : public EdgeException
{
} weightException ;


class Edge
{

protected:

	// weight of the edge
	char weight;


	bool inRange()
	{
		return weight > -129 && weight < 128;
	}

public:

	// increment operator
	int operator++ ()
	{
		if (weight < 127)
		{
			weight = weight | (1 << 1);
		}
	};




	// ostream
	friend ostream& operator<<(ostream& os, Edge& edge)
	{
		os << edge.weight;
		return os;
	};

	// assignment operator
	Edge& operator= (Edge& edge)
	{
		this->weight = edge.weight;
	};

	// default constructor
	Edge()
	{
		weight = 0;
	};

	// initializer
	Edge(char weight)
	{
		try
		{
			if (weight < -128 || weight > 127) throw weightException;
			else this->weight = weight;
		}
		catch (EdgeWeightException e)
		{
			cout << "OUT OF BOUNDS, WEIGHT GOES -128 TO 127\n";
		}
	};

	// copy constructor
	Edge(Edge& edge)
	{
		weight = edge.weight;
	};

	// destructor
	~Edge()
	{
	};



};