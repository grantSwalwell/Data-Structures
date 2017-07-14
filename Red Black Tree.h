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

	void insert(const x& element)
	{
		// empty tree reached
		if (Empty())
		{
			root = new x(element);
			color = RED;
			left = grow();
			right = grow();
		}

		// check if this = root
		else if (Root() == element)
		{
			delete root;
			root = new x(element);
		}

		// if this is greater than element go left
		else if (Root() > element) Left()->insert(element);

		// else if this is less than element go right
		else if (Root() < element) Right()->insert(element);

		RedRule();
	}

	// apply red condition
	void RedRule()
	{
		// if empty return
		if (Empty())
		{
			cout << "NODE EMPTY\n";
			return;
		}

		

		// LL violation
		if (Left()->Color() == RED && Left()->Left()->Color() == RED)
		{
			zig();
		}

		// LR violation
		if (Left()->Color() == RED && Left()->Right()->Color() == RED)
		{
			zigzag();
		}

		// RL violation
		if (Right()->Color() == RED && Right()->Left()->Color() == RED)
		{
			zagzig();
		}

		// RR violation
		if (Right()->Color() == RED && Right()->Right()->Color() == RED)
		{
			zag();
		}
		
		
		
		
		/*

		// if red
		if (color == RED)
		{
			// if left or right are red rule violated, switch to black
			if (Left()->Color() == RED || Right()->Color() == RED)
			{
				color = BLACK;

				cout << "CASE 1: ROOT IS RED SO IS CHILD\n";
			}


			// if left is red
			if (Left()->Color() == RED)
			{
				cout << "LEFT IS RED\n";

				// if left left is red
				if (Left()->Left()->Color() == RED)
				{
					cout << "LEFT LEFT VIOLATION\n";

					// fix left left violation
					// if right is also red
					if (Right()->Color() == RED)
					{
						color = RED;
						Left()->Color(BLACK);
						Right()->Color(BLACK);
					}
					else zig();

					return;
				}

				else if (Left()->Right()->Color() == RED) // left right is red
				{
					cout << "LEFT RIGHT VIOLATION\n";

					// fix left right
					if (Right()->Color() == RED)
					{
						color = RED;
						Left()->Color(BLACK);
						Right()->Color(BLACK);
					}
					else zigzag();

					return;
				}
			}

			// if right is red
			if (Right()->Color() == RED)
			{
				cout << "RIGHT IS RED\n";

				if (Right()->Right()->Color() == RED)
				{
					cout << "RIGHT RIGHT VIOLATION\n";

					// fix right right
					if (Left()->Color() == RED)
					{
						color = RED;
						Left()->Color(BLACK);
						Right()->Color(BLACK);
					}
					else zagzig();

					return;
				}

				// if right left is red
				else if (Right()->Left()->Color() == RED)
				{
					cout << "RIGHT LEFT VIOLATION\n";

					// fix right left
					if (Left()->Color() == RED)
					{
						color = RED;
						Left()->Color(BLACK);
						Right()->Color(BLACK);
					}
					else zag();

					return;
				}
			}
		}
		*/
		

		
	}

public:
	
	// get color
	int Color()
	{
		return color;
	}

	// set color
	void Color(int color)
	{
		this->color = color;

		try
		{
			// check for violation
			if (color != RED && color != BLACK) throw notBST;
		}
		catch (BinarySearchTreeNOTBST e)
		{
			cout << "INVALID COLOR\n";
		}
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

	// insert
	void Insert(const x& element)
	{
		insert(element);
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