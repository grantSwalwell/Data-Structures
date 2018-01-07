#pragma once
#include "Graphs\Graph - Adjacency Matrix.h"
#include "Heap\Min Heap.h"

// node for search
class Node
{

public:

	int node;
	int cost;

	bool operator< (Node& node)
	{
		return cost < node.cost;
	}

	bool operator> (Node& node)
	{
		return cost > node.cost;
	}

	bool operator<= (Node& node)
	{
		return cost <= node.cost;
	}

	bool operator>= (Node& node)
	{
		return cost >= node.cost;
	}

	bool operator== (Node& node)
	{
		return cost == node.cost;
	}

	Node& operator= (Node& node)
	{
		this->node = node.node;
		this->cost = node.cost;
		return *this;
	}

	friend ostream& operator<< (ostream& os, Node& node)
	{
		os << " Cost: " << node.cost << " Node: " << node.node << endl;
		return os;
	}

	Node()
	{
		node = 0;
		cost = 0;
	}

	Node(int node, int cost)
	{
		this->node = node;
		this->cost = cost;
	}
};

// uniform cost search, pass the graph, the root node, and the goal
int UCS(Graph& G, int root, int goal)
{
	int size = G.nodes();
	Node node = Node(root, 0);
	int cost = 0;

	// priority queue
	Heap<Node>* pq = new Heap<Node>(size * size);
	
	// enqueue the root
	pq->Insert(node);

	// start algorithm, while heap isn't empty...
	while (!pq->Empty())
	{
		// get node at front
		node = pq->Min();

		// delete it
		pq->Delete();

		// if node is the goal we are done
		if (node.node == goal) return node.cost;

		// now we check the neighbors
		for (int i = 0; i < size; i++)
		{
			// check if an edge
			if (G.edge(node.node, i))
			{
				pq->Insert(Node(i, node.cost + 1));
			}
		}
	}


}

