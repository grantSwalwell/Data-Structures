#pragma once
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;
// abstract base class for red black/ AVL trees
// extends binary search tree

template <class x> class BalanceTree : public BinarySearchTree<x>
{

protected:

	// zig, clockwise rotation, constant time
	virtual void zig()
	{
		// nothing to rotate in an empty tree
		if (this->Empty()) return;

		// can't rotate an empty tree to root
		if (this->left->Empty()) return;

		// get pointer to left child
		BinarySearchTree<x>* leftChild = this->left;

		// set left to leftChild left
		this->Left(leftChild->Left());

		// set left child right to left child left
		leftChild->Left(leftChild->Right());

		// set right to left child right
		leftChild->Right(this->Right());

		// set left child to right
		this->Right(leftChild);

		// swap root and right
		this->swap(leftChild);
	};

	// zag, counter clockwise
	virtual void zag() 
	{
		// nothing to rotate in an empty tree
		if (this->Empty()) return;

		// can't rotate an empty right tree to root
		if (this->right->Empty()) return;

		// get pointer to right child and left child
		BinarySearchTree<x>* rightChild = this->right;
		
		// set right to right child right
		this->Right(rightChild->Right());

		// set rightchild right to rightchild left
		rightChild->Right(rightChild->Left());

		// set rightchild left to this left
		rightChild->Left(this->Left());
		
		// set left to rightchild
		this->Left(rightChild);

		// swap root with new left root
		this->swap(rightChild);
	};

	// zig zag
	virtual void zigzag()
	{	
		// can't rotate null to root
		if (this->Empty()) return;

		//call zig on right
		((BalanceTree<x>*) left)->zag();

		// call zag
		zig();

	};

	// zag zig
	virtual void zagzig()
	{
		// can't rotate null to root
		if (this->Empty()) return;

		//call zig on right
		((BalanceTree<x>*) right)->zig();

		// call zag
		zag();
	};

	// zig zig
	virtual void zigzig()
	{
		zig();
		zig();
	};

	// zag zag
	virtual void zagzag() 
	{
		zag();
		zag();
	};

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
		//zag();
		zig();
		zig();
		zag();
		zag();
		//zig();
		//zig();
		//zag();

		//zagzag();
		zigzig();
		zagzag();
		
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