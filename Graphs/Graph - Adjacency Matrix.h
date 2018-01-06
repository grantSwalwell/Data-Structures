#pragma once
#include <iostream>
#include "Matrix.h"


class Graph
{
	// nodes
	int n;

	// size
	int size;

	// data structure
	Matrix<bool>* mat;

	// print method for ostream
	ostream& print(ostream& os)
	{
		// unfortunately I think this is n^3 but for a small number.... n * (n / 8) * 8 = n^2???
		for (int i = 0; i < n; i++)
		{
			if (i < 10) os << " ";

			os << i << ": ";

			for (int j = 0; j < size; j++)
			{
				os << (*mat)[i][j];
				os << " ";
			}
			os << endl;
		}
		return os;
	}

	// display method for ostream and edge list format
	ostream& display(ostream& os)
	{
		os << "Nodes" << endl;

		// for each node
		for (int i = 0; i < n; i++)
		{
			os << "[" << i << "]";
			if ((i + 1) % 10 == 0) os << endl;
			else os << " ";
		}

		int counter = 0;

		os << endl << "Edges" << endl;

		// for each edge
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				// if i (row) < j (column) we havent already covered this part of the matrix
				if (edge(i, j) && (i <= j))
				{
					os << "(" << i << ", " << j << ")" << endl;
				}
			}
		}


		return os;
	}

	

public:

	int nodes()
	{
		return n;
	};

	// returns 1 if edge, 0 if not
	bool edge(int  node0, int  node1)
	{
		if ((node0 < n && node1 < n))
			return ((*mat)[node1][node0]) 
			|| ((*mat)[node0][node1]);
		else return false;
	}

	// turns an edge on               <----------------------------------------- TAKES PLACE OF ADD EDGE 
	void on(int  node0, int node1)
	{
		// check to make sure we are adding edges for nodes that exist and edges that do not
		if (edge(node0, node1))
		{
			return;
		}

		// turn on the first edge

		(*mat)[node1][node0] = true;

		// turn on the reverse edge

		(*mat)[node0][node1] = true;
	}

	// turns an edge off
	void off (int  node0, int node1)
	{
		// check to make sure we are removing edges that exist, return if false
		if (!edge (node0, node1))
		{
			return;
		}

		// turn off the first edge

		(*mat)[node1][node0] = false;

		// turn off the reverse edge

		(*mat)[node0][node1] = false;
	};

	// get node, corresponding to a row in the matrix
	Array<bool>& operator[](int index)
	{
		return (*mat)[index];
	}


	// ostream operator
	friend ostream& operator<<(ostream& os, Graph& bit)
	{
		bit.display(os);

		os << endl;

		bit.print(os);

		return os;
	};

	// assignment operator
	Graph& operator=(Graph& graph)
	{
		n = graph.n;
		size = graph.size;
		mat = graph.mat;

		return *this;
	};

	// default constructor
	Graph()
	{
		n = 0;
		size = 0;
		mat = NULL;
	};

	// initializer
	Graph(int nodes)
	{
		n = nodes;

		size = n;

		// initialize mat 
		mat = new Matrix<bool>(n);

		// initialize each element to a null value O(n^2)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < size; j++)
			{
				(*mat)[i][j] = false;
			}
		}
	};

	// copy constructor
	Graph(Graph& graph)
	{
		n = graph.n;
		size = graph.size;
		mat = graph.mat;
	};

	// destructor
	~Graph()
	{
		if (mat != NULL)
		{
			delete mat; 
			mat = NULL;
		};
	};

};