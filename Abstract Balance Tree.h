#pragma once
#include <iostream>
#include "Binary Search Tree.h"

using namespace std;
// abstract base class for red black/ AVL trees

/*
class BalanceTreeException : public exception {};
class BalanceTreeNotFound : public BalanceTreeException {} notFound;
class BalanceTreeEmpty : public BalanceTreeException {} emptyTree;
*/


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

		// get pointer to right child
		BalanceTree<x>* rightChild = Right();

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

		//call zag on left
		this->Left()->zag();

		// call zig
		zig();
	};

	// zag zig
	virtual void zagzig()
	{
		// can't rotate null to root
		if (this->Empty()) return;

		//call zig on right
		this->Right()->zig();

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

	

public:

	// get left
	virtual BalanceTree* Left()
	{
		return ((BalanceTree<x>*) left);
	};

	// get right
	virtual BalanceTree* Right()
	{
		return ((BalanceTree<x>*) right);
	};

	// set left
	virtual void Left(BalanceTree* left)
	{
		this->left = left;
	};

	// set right
	virtual void Right(BalanceTree* right)
	{
		this->right = right;
	};

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
	};

	// initializer
	BalanceTree(const x& root) : BinarySearchTree<x>(root)
	{
	};

	// copy constructor
	BalanceTree(BalanceTree& tree) : BinarySearchTree<x>(tree)
	{
	};

	// destructor
	virtual ~BalanceTree()
	{
	};


};