#pragma once
#include <iostream>
using namespace std;
// abstract base class for red black/ AVL trees
// extends binary search tree

template <class x> class BalanceTree : virtual BinarySearchTree<x>
{

protected:

	// zig, clockwise rotation, constant time
	void zig() {};

	// zag, counter clockwise
	void zag() {};

	// zig zag
	void zigzag() {};

	// zag zig
	void zagzig() {};

	// zig zig
	void zigzig() {};

	// zag zag
	void zagzag() {};



public:

	// default constructor
	BalanceTree() : BinarySearchTree() {};

	// initializer
	BalanceTree(x& root) : BinarySearchTree(root) {};

	// second initializer
	BalanceTree(x& root, BalanceTree* left, BalanceTree* right) : BinarySearchTree(root, left, right) {};

	// copy constructor
	BalanceTree(BalanceTree& tree) : BinarySearchTree(tree) {};

	// destructor
	~BalanceTree() { this->~BinarySearchTree(); };
};