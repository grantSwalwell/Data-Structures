#include "Array.h"
#include <queue>
#include "Graph - Bit Adjacency Matrix.h"

// Breadth First Search
Array<int>* BFS(Graph& G, int node)
{
	// BFS queue
	queue<int>* que = new queue<int>;

	// visited array
	Array<bool> visited(G.nodes());

	// bfs VAL ARRAY
	Array<int>* BFSvals = new Array<int>(G.nodes());

	// initialize both
	for (int i = 0; i < G.nodes(); i++)
	{
		visited[i] = false;
		(*BFSvals)[i] = 0;
	}

	// declare bfs number
	int BFSval = 0;

	// enqueue start vertex,
	que->push(node);

	// set initial vertex to visited
	visited[node] = true;

	// while the queue is not empty
	while (!que->empty())
	{
		// get front 
		int v = que->front();

		// pop front
		que->pop();

		// for each neighbor 
		for (int i = 0; i < G.nodes(); i++)
		{
			// if i is a neighbor
			if (G.edge(i, v))
			{
				// if we have not visited it
				if (!visited[i])
				{
					// set visited to true
					visited[i] = true;

					// increment val
					BFSval++;

					// set vals[i] to num
					(*BFSvals)[i] = BFSval;

					// push i
					que->push(i);

				} // end if
			} // end if
		} // end for
	} // end while



	return BFSvals;
};v