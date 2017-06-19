#pragma once
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;
// abstract base class for red black/ AVL trees
// extends binary search tree

template <class x> class BalanceTree : virtual public BinarySearchTree<x>
{

protected:

	// zig, clockwise rotation, constant time
	void zig() {};

	// zag, counter clockwise
	virtual void zag() 
	{
		// nothing to rotate in an empty tree
		if (this->Empty()) return;

		// can't rotate an empty right tree to root
		if (this->right->Empty()) return;

		// get pointer to right child and left child
		BalanceTree<x>* rightChild = dynamic_cast<BalanceTree<x>*>(this->right);
		BalanceTree<x>* leftChild = dynamic_cast<BalanceTree<x>*>(this->left);

		cout << "HERE" << endl;

		// set right to right right
		this->right = rightChild->Right();

		cout << "HERE" << endl;

		// set rightchild right to rightchild left
		rightChild->Right(rightChild->Left());

		cout << "HERE" << endl;

		// set rightchild left to this left
		rightChild->Left(this->Left());

		cout << "HERE" << endl;
		
		// set left to rightchild
		this->Left(rightChild);
		
		
		cout << "HERE" << endl;


		// swap root with new left root
		x* leftRoot = rightChild->root;
		rightChild->root = this->root;
		this->root = leftRoot;

	};

	// zig zag
	void zigzag() {};

	// zag zig
	void zagzig() {};

	// zig zig
	void zigzig() {};

	// zag zag
	void zagzag() {};

	// override of grow
	BinarySearchTree<x>* grow()
	{
		// grow a new tree
		BinarySearchTree<x>* tree = new BalanceTree<x>;

		// specify it as a subtree
		((BalanceTree<x>*)tree)->subtree = true;

		// return the tree
		return tree;
	}

public:

	void Balance()
	{
		zag();
	}

	BalanceTree& operator=(BalanceTree& tree)
	{
		this->root = tree.root;
		this->left = tree.left;
		this->right = tree.right;

		return *this;
	}

	BalanceTree& operator=(BinarySearchTree& tree)
	{
		this->root = tree.root;
		this->left = tree.left;
		this->right = tree.right;

		return *this;
	}

	// default constructor
	BalanceTree() : BinarySearchTree() {};

	// initializer
	BalanceTree(x& root) : BinarySearchTree(root) {};

	// second initializer
	BalanceTree(x& root, BalanceTree* left, BalanceTree* right) : BinarySearchTree(root, left, right) {};

	// copy constructor
	BalanceTree(BalanceTree& tree) : BinarySearchTree(tree) {};

	// destructor
	virtual ~BalanceTree() 
	{
		if (root != NULL)
		{
			delete root;
		};

		root = NULL;

		if (left != NULL)
		{
			delete left;
		};

		left = NULL;

		if (right != NULL)
		{
			delete right;
		};

		right = NULL;
	};
};