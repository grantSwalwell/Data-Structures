#include "Array.h"
#include "Graph - Bit Adjacency Matrix.h"

// Depth First Search recursive helper method
void DFS(Graph& G, int v0, Array<bool>* visited, Array<int>* search, int depth)
{
	// set visited
	(*visited)[v0] = true;

	// set search num
	(*search)[v0] = depth;

	// iterate through neighbors
	for (int i = 0; i < G.nodes(); i++)
	{
		// if i is a neighbor
		if (G.edge(i, v0))
		{
			// if it has not been visited
			if (!(*visited)[i])
			{
				// call DFS
				DFS(G, i, visited, search, depth + 1);
			}
		} // end if
	} // end for

}

// Depth First Search
Array<int>* DFS(Graph& G, int v0)
{
	// visited array
	Array<bool>* visited = new Array<bool>(G.nodes());

	// search number array, order of visitation
	Array<int>* search = new Array<int>(G.nodes());

	// initialize both arrays
	for (int i = 0; i < G.nodes(); i++)
	{
		(*visited)[i] = false;
		(*search)[i] = 1;
	}

	// create depth field
	int depth = 1;

	// call DFS
	DFS(G, v0, visited, search, depth);

	return search;
};
