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
	unsigned short int weight;

	bool inRange()
	{
		return weight > 0 && weight < 65536;
	}

public:

	// increment operator
	int operator++ ()
	{

	};

	// ostream
	friend ostream& operator<< (ostream& os, Edge& edge)
	{
		os << edge.weight;
		return os;
	}

	// assignment operator
	Edge& operator= (Edge& edge)
	{
		this->weight = edge.weight;
	}

	// default constructor
	Edge()
	{
		weight = 0;
	}

	// initializer
	Edge(int weight)
	{
		try
		{
			if (weight < 0 || weight > 65535) throw weightException;
			else this->weight = weight;
		}
		catch (EdgeWeightException e)
		{
			cout << "OUT OF BOUNDS, WEIGHT GOES 0 TO 65,535\n";
		}
	}

	// copy constructor
	Edge(Edge& edge)
	{
		weight = edge.weight;
	}

	// destructor
	~Edge()
	{
	}



};