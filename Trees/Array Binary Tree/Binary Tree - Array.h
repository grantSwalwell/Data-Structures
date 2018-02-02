#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Node.h"

// technically a vector implementation because for some reason I have to use a crummy stl vector instead
// of my wonderful custom array or vector

using namespace std;

template <class x> class BiTree 
{

public:

	// fields

	// the vector serving as our binary tree, of type Node of type x
	vector<Node<x>*>* tree;

	// iterator for vector, I don't even know why this is necessary 
	typename vector<Node<x>*>::iterator I;

	// root index
	int root;

	// number of nodes
	int nodes;

	// size of the vector
	int size;

	// stack of integers that are free index positions
	stack<int>* free;

	// methods

	// add method for use by BinarySearchTree 
	void add(x& data)
	{
		// index position
		int pos = 0;

		// if the free stack is not empty look at the top element and pop it off
		if (!free->empty())
		{
			pos = free->top();
			free->pop();
		}
		else cout << "TREE FULL";

		// insert the new node at that position
		tree->at(pos) = new Node<x>(data);

		// increment nodes
		nodes++;
	};

	// removes the node at that index in the vector, for use by search Tree
	void remove(int index)
	{
		// delete and null out element at index
		if (tree->at(index) != NULL)
		{
			delete tree->at(index);
			tree->at(index) = NULL;
		}

		// push the now free space onto the stack
		free->push(index);

		// decrement nodes
		nodes--;
	};

	// return height of the tree
	int Height() {};

	// return size of the tree
	int Size() {};

	// output methods

	// inorder traversal of the tree

	// preorder traversal of the tree

	// display raw data

	// display free spaces
	ostream& printFree(ostream& os)
	{

	};

	// char representation of the tree
	ostream& print(ostream& os)
	{

	};

	// operators

	// assignment operator
	BiTree& operator=(BiTree& tree)
	{

	};

	// output operator, prints out the inorder and preorder traversal 
	friend ostream& operator<< (ostream& os, BiTree tree)
	{


	};

	// constructors

	// default constructor
	BiTree() 
	{
		tree = NULL;
		root = 0;
		nodes = 0;
		size = 0;
		free = NULL;
	};

	// initializer
	BiTree(int size)
	{
		// create the new vector serving as our tree
		tree = new vector<Node<x>*>(size);

		// using an int counter for the index so I can practice using the iterators
		int index = 0;

		// OLD: I'm going to assume I need to initialize each node
		// Now I'm going to try initializing each element to NULL
		for (I = tree->begin(); I != tree->end(); I++)
		{
			//tree->at(i) = new Node<x>;
			tree->at(index) = NULL;
			index++;
		};

		// 0 nodes initially
		nodes = 0;
		 
		// size of vector
		this->size = size;

		// create new stack
		free = new stack<int>;

		// push all the free positions onto the stack
		for (int i = 0; i < size; i++)
		{
			free->push(i);
		};

		// the root should start at the top of the stack so set it to the top element
		root = free->top();

	};

	// copy constructor
	BiTree(BiTree& tree)
	{

	};

	// destructor
	~BiTree()
	{

	};

};