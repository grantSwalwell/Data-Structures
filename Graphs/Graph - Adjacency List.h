#pragma once
#include "LinkedList.h"
#include "Array.h"

// unweighted undirected graph list

class Graph
{

protected:

	// number of nodes
	int n;

	// data structure, array of linked lists of type int
	// where int is the node with which it has an edge
	Array<LinkedList<int>*>* list;

	// display method for ostream
	ostream& display(ostream& os)
	{
		// display each row of array
		for (int i = 0; i < n; i++)
		{
			// if i < 10 add a space to make the index look nice
			if (i < 10)
			{
				os << " ";
			}

			os << i << ": ";

			// output row
			os << (*(*list)[i]) << endl;
		}

		return os;
	};

public:

	// is an edge method
	bool edge(int v1, int v2)
	{
		return (*list)[v1]->contains(v2) || (*list)[v2]->contains(v1);
	};

	// add an edge method
	void on(int v1, int v2)
	{
		// check if edge
		if (edge(v1, v2)) return;

		// add edges
		(*list)[v1]->add(v2);
		(*list)[v2]->add(v1);
	};

	//remove edge method
	void off(int v1, int v2)
	{
		if (!edge(v1, v2)) return;

		// find edges
		int pos1 = (*list)[v1]->index(v2, 0);
		int pos2 = (*list)[v2]->index(v1, 0);

		// remove edges
		(*list)[v1]->remove(pos1);
		(*list)[v2]->remove(pos2);

	};

	// get number of nodes
	int nodes()
	{
		return n;
	};

	// assignment operator

	// ostream operator
	friend ostream& operator<<(ostream& os, Graph& G)
	{
		return G.display(os);
	};

	// default constructor 
	Graph()
	{
		n = 0;
		list = NULL;
	};

	// initializer
	Graph(int nodes)
	{
		this->n = nodes;
		
		list = new Array<LinkedList<int>*>(nodes);

		for (int i = 0; i < nodes; i++)
		{
			(*list)[i] = new LinkedList<int>;
		}
	};

	// copy constructor
	Graph(Graph& G)
	{

	};

	// destructor
	~Graph()
	{
		if (list != NULL)
		{
			delete list;
			list = NULL;
		}
	};


};