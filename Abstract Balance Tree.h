#pragma once
#include <iostream>
#include "BinarySearchTree.h"

#include <typeinfo>

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
		BalanceTree<x>* leftChild = (BalanceTree<x>*) this->left;

		cout << typeid(*leftChild).name() << endl;

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
		//BinarySearchTree<x>* rightChild = this->right;
		BalanceTree<x>* rightChild = (BalanceTree<x>*) this->right;

		cout << typeid(*rightChild).name() << endl;
		
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
		//((BalanceTree<x>*) left)->zag();

		// call zag
		zig();

	};

	// zag zig
	virtual void zagzig()
	{
		// can't rotate null to root
		if (this->Empty()) return;

		//call zig on right
		//((BalanceTree<x>*) this->right)->zig();
		BalanceTree<x>* tree = (BalanceTree<x>*) this->right;
		if (tree == NULL) cout << "INVALID" << endl;
		//cout << *tree << endl << endl;

		//cout << typeid(*tree).name() << endl;

		//tree->zig();
		//((BalanceTree<x>*) this->right)->zig();

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
	BalanceTree* grow()
	{
		// grow a new tree
		BalanceTree<x>* tree = new BalanceTree<x>();

		// specify it as a subtree
		tree->subtree = true;

		cout << "BALANCE TREE GROW" << endl;

		// return the tree
		return tree;
	}

public:


	void Balance()
	{
		zig();
		zag();
		//zag();
		//zig();
		zigzig();
		zagzag();

		//zagzig();
		//zigzag();		
	}

	BalanceTree& operator=(BalanceTree& tree)
	{
		this->root = new x(tree.root);
		this->left = new BalanceTree<x>(*tree.left);
		this->right = new BalanceTree<x>(*tree.right);

		return *this;
	}

	// default constructor
	BalanceTree() : BinarySearchTree<x>()
	{
		cout << typeid(*this).name() << endl;
	};

	// initializer
	BalanceTree(x& root) : BinarySearchTree<x>(root)
	{
		cout << typeid(*this).name() << endl;
	};

	// second initializer
	BalanceTree(x& root, BalanceTree* left, BalanceTree* right) : BinarySearchTree<x>(root, left, right) {};

	// copy constructor
	BalanceTree(BalanceTree& tree) : BinarySearchTree<x>(tree) {};

	// destructor
	virtual ~BalanceTree() 
	{
		
	};
};