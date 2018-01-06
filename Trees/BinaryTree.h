#pragma once
#include <iostream>

using namespace std;

template <class x> class BinaryTree
{

protected:

	// the node's data
	x* root;
		
	// left child
	BinaryTree<x>* left;

	// right child
	BinaryTree<x>* right;

public:

	// access root
	x& Root()
	{
		return root;
	};

	// access left child
	BinaryTree& Left()
	{
		return left;
	};

	// access right child
	BinaryTree& Right()
	{
		return right;
	};

	// empty or not
	bool Empty()
	{
		return (root == NULL);
	};

	// height of the tree
	int Height()
	{
		// counter
		int n = 0;

		// left counter
		int nleft = 0;

		// right counter
		int nright = 0;

		// if the tree isn't empty
		if (!this->Empty())
		{
			// get left height
			nleft = left->Height();

			// get right height
			nright = right->Height();

			// get n
			if (nleft > nright) n = 1 + nleft;
			else n = 1 + nright;
		}

		// n = 2
		return n;
	};

	// size of the tree
	int Size()
	{
		// counter
		int n = 0;

		// left size
		int nleft = 0;

		// right size
		int nright = 0;

		// if the tree isn't empty
		if (!this->Empty())
		{
			// get left size
			nleft = left->Size();

			// get right size
			nright = right->Size();

			// set n to 1 + both
			n = 1 + nleft + nright;
		};

		return n;
	};

	// print method inorder
	void print(ostream& os)
	{
		// print left
		if (left != NULL) left->print(os);
		
		// if root is not null output it
		if (root == NULL) return;
		else os << *root << endl;

		// print right
		if (right != NULL) right->print(os);
	};


	// assignment operator
	BinaryTree& operator=(BinaryTree& tree)
	{
		// delete and null out to prevent memory leaks
		if (root != NULL)
		{
			delete root;
			root = NULL;
		}
		if (left != NULL)
		{
			delete left;
			left = NULL;
		}
		if (right != NULL)
		{
			delete right;
			right = NULL;
		}

		root = tree.root;
		left = tree.left;
		right = tree.right;
	};

	// output operator
	friend ostream& operator<<(ostream& os, BinaryTree& tree)
	{
		tree.print(os);

		return os;
	};

	// default constructor
	BinaryTree()
	{
		root = NULL;
		left = NULL;
		right = NULL;
	};

	// initializer
	BinaryTree(x root, BinaryTree* left, BinaryTree* right)
	{
		// set root
		this->root = new x(root);

		// if left is null create an empty tree
		if (left == NULL) this->left = new BinaryTree<x>;
		else this->left = left;
		
		// same for right
		if (right == NULL) this->right = new BinaryTree<x>;
		this->right = right;
	};

	// secondary initializer
	BinaryTree(x root)
	{
		this->root = new x(root);
		this->left = new BinaryTree<x>;
		this->right = new BinaryTree<x>;
	};

	// copy constructor
	BinaryTree(BinaryTree& tree)
	{
		root = tree.root;
		left = tree.right;
		right = tree.right;
	};

	// destructor
	~BinaryTree()
	{
		if (root != NULL)
		{
			delete root;
			root = NULL;
		};

		if (left->root != NULL)
		{
			delete left;
			left = NULL;
		};

		if (right->root != NULL)
		{
			delete right;
			right = NULL;
		};
	};

};