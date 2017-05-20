#pragma once
#include <iostream>
#include "Matrix.h"

// Representation of an adjacency matrix using unsigned chars to represent bits and my implementation of Matrix

class Graph
{
	// nodes
	int n;

	// size, = n/8 or n/8 + 1
	int size;

	// data structure
	Matrix<unsigned char>* mat;

	// print method for ostream
	ostream& print(ostream& os)
	{
		// unfortunately I think this is n^3 but for a small number.... n * (n / 8) * 8 = n^2???
		for (int i = 0; i < n; i++)
		{ 
			os << i << ": ";

			for (int j = 0; j < size; j++)
			{
				printByte(os, (*mat)[i][j]);
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

	// helper method for print
	ostream& printByte(ostream& os, unsigned char c)
	{
		for (int i = 0; i < 8; i++)
		{
			if (c & (1 << (7 - i))) os << 1;
			else os << 0;
		};

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
		if ((node0 < n && node1 < n)) return ((*mat)[node1][node0 / 8] & (1 << node0 % 8)) || ((*mat)[node0][node1 / 8] & (1 << node1 % 8));
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

		(*mat)[node1][node0 / 8] = (*mat)[node1][node0 / 8] | (1 << node0 % 8);
		
		// turn on the reverse edge

		(*mat)[node0][node1 / 8] = (*mat)[node0][node1 / 8] | (1 << node1 % 8);
	}

	// turns an edge off
	void off(int  node0, int node1)
	{

	}

	// get node, corresponding to a row in the matrix
	Array<unsigned char>& operator[](int index)
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
	Graph() {};

	// initializer
	Graph(int nodes)
	{
		n = nodes;

		if (nodes % 8 == 0) size = n / 8;
		else size = (int)(n / 8) + 1;

		// initialize mat to have a row for each node one column for every 8 nodes
		mat = new Matrix<unsigned char>(n, size);

		// initialize each element to a null value O(n^2)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < size; j++)
			{
				 (*mat)[i][j] = 0x00 << 8;
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

};
