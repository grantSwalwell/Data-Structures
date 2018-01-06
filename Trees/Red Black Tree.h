#pragma once
#include "Abstract Balance Tree.h"

using namespace std;

const short int RED = 0;
const short int BLACK = 1;


template <class x> class RedBlack : public BalanceTree<x>
{

protected:

	// color of tree
	short int color;

	// grow a new tree
	RedBlack<x>* grow()
	{
		RedBlack<x>* tree = new RedBlack<x>;

		tree->subtree = true;

		return tree;
	}

public:
	
	// get color
	int Color()
	{
		return color;
	}

	// get left
	RedBlack<x>* Left()
	{
		return (RedBlack<x>*) left;
	}

	// get right
	RedBlack<x>* Right()
	{
		return (RedBlack<x>*) right;
	}

	// set left
	void Left(RedBlack<x>* left)
	{
		this->left = left;

		try
		{
			if (Root() < left->Root()) throw notBST;
		}
		catch (BinarySearchTreeNOTBST e)
		{
			cout << "\nTREE VIOLATED - NOT A BINARY SEARCH TREE\n\n";
		}
	}

	// set right
	void Right(RedBlack<x>* right)
	{
		this->right = right;

		try
		{
			if (Root() > right->Root()) throw notBST;
		}
		catch (BinarySearchTreeNOTBST e)
		{
			cout << "\nTREE VIOLATED - NOT A BINARY SEARCH TREE\n\n";
		}

	}

	// assignment operator
	RedBlack<x>& operator=(RedBlack<x>& tree)
	{
		this->color = tree->Color();
		(*this->root) = tree->Root();
		this->left = tree->Left();
		this->right = tree->Right();
	}

	// default constructor
	RedBlack() : BalanceTree<x>() { color = BLACK; }

	// initializer
	RedBlack(x& root) : BalanceTree<x>(root) { color = RED; }

	// copy constructor
	RedBlack(RedBlack<x>& tree) : BalanceTree<x>(tree) { this->color = tree->Color(); }

	// destructor
	~RedBlack() { };
};