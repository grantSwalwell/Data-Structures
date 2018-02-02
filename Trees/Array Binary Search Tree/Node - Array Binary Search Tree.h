#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include "Binary Search Tree - Array.h"

using namespace std;

// nodes for use in the Array Binary Tree 
// each node has a pointer to data, and the index position of it's left/right children
// I added the index of parent, its own index, as well as a pointer to the tree it is a part of, but did not give it pointers to it's children outside of the traversal methods

template <class x> class Node
{

public:

	// data field
	x* info;

	// index of node
	int index;

	// left index
	int left;

	// right index
	int right;

	// index of parent
	int parent;

	// pointer to tree vector
	vector<Node<x>*>* tree;

	// inorder helper method
	void inorder(stack<int>* stack)
	{
						
		// call inorder on right
		if (right != -1)
		{
			Node<x>* r = tree->at(right);
			
			r->inorder(stack);
		}


		// push our own index
		stack->push(index);

		// call inorder on left
		if (left != -1)
		{
			Node<x>* l = tree->at(left);

			l->inorder(stack);
		}
	};

	// preorder indexer
	void preorder(stack<int>* stack)
	{
		// it is a stack so we must call preorder on right, then left, then push our own index
		if (right != -1)
		{
			Node<x>* r = tree->at(right);

			r->preorder(stack);
		}

		if (left != -1)
		{
			Node<x>* l = tree->at(left);

			l->preorder(stack);
		}

		stack->push(index);
	}

	// is a empty node
	bool empty() { return info == NULL; };

	// greater than op
	bool operator>(Node& node)
	{
		return (*info > (*node.info));
	};

	// less than op
	bool operator<(Node& node)
	{
		return (*info < (*node.info));
	};

	// equal to op
	bool operator==(Node& node)
	{
		return (*info == (*node.info));
	};

	// greater than or equal to op
	bool operator>=(Node& node)
	{
		return (*info >= (*node.info));
	};

	// less than or equal to op
	bool operator<=(Node& node)
	{
		return (*info <= (*node.info));
	};

	// does not equal op
	bool operator!=(Node& node)
	{
		return (*info != (*node.info));
	};

	// OVERLOADED FOR TYPE x

	// greater than op
	bool operator>(x& data)
	{
		return (*info > data);
	};

	// less than op
	bool operator<(x& data)
	{
		return (*info < data);
	};

	// equal to op
	bool operator==(x& data)
	{
		return (*info == data);
	};

	// greater than or equal to op
	bool operator>=(x& data)
	{
		return (*info >= data);
	};

	// less than or equal to op
	bool operator<=(x& data)
	{
		return (*info <= data);
	};

	// does not equal op
	bool operator!=(x& data)
	{
		return (*info != data);
	};

	// assignment operator
	Node& operator= (Node& node)
	{
		index = node.index;
		info = node.info;
		left = node.left;
		right = node.right;
		parent = node.parent;
		index = node.index;
		tree = node.tree;

		return *this;
	};

	// ostream operator
	friend ostream& operator<< (ostream& os, Node& node)
	{
		return node.print(os);
	};

	// print method for os op
	ostream& print(ostream& os)
	{
		if (info != NULL)	os << *info;
		else os << "NULL";

		return os;
	};

	// default constructor
	Node() { info = NULL; left = -1; right = -1; parent = -1; index = -1; tree = NULL };

	// initializer
	Node(x& data) { info = new x(data); left = -1; right = -1; parent = -1; index = -1; tree = NULL; };

	// initializer with children
	Node(x& data, int left, int right) { info = new x(data); this->left = left; this->right = right; tree = NULL; index = -1; parent = -1; };

	// copy constructor
	Node(Node& data) { info = data.info; left = data.left; right = data.right; parent = data.parent; index = data.index; tree = data.tree; };

	// destructor
	~Node()
	{ 
		if (info != NULL)
		{
			delete info;
			info = NULL;
		}

		if (tree != NULL)
		{
			tree = NULL;
		}
	}

};