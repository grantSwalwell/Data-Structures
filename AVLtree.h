#pragma once
#include <iostream>
#include "Abstract Balance Tree.h"

template <class x> class  AVLtree : public BalanceTree<x>
{

protected:

	// the balance factor
	int bf;

	// grow a tree
	AVLtree* grow()
	{
		AVLtree<x>* tree = new AVLtree<x>;

		tree->subtree = true;

		return tree;
	};

	// is balanced
	bool balanced()
	{
		return (-1 <= bf && bf <= 1);
	};

	// recursive insert helper method
	void insert(x& data)
	{
		// first case, reached an empty sub tree
		if (Empty())
		{
			root = new x(data);
			left = grow();
			right = grow();
			bf = 0;
			return;
		}

		// second case, data matches root
		if (Root() == data)
		{
			delete root;
			root = new x(data);
			return;
		}

		int oldbf;

		//  third case, root is greater than data
		if (Root() > data)
		{
			// if left is empty simply insery
			if (Left()->Empty())
			{
				Left()->Insert(data);
				bf--;
			}
			else
			{
				// get old bf
				oldbf = Left()->BalanceFactor();

				// insert left
				Left()->Insert(data);

				// check if bf changed
				if (oldbf != Left()->BalanceFactor() && Left()->BalanceFactor() != 0)
				{
					// if the lef subtree got longer decrement bf
					bf--;
				}
			}
			
		}
		else // root < data
		{
			// if right is empty
			if (Right()->Empty())
			{
				// insert right
				Right()->Insert(data);
				
				// right subtree got longer, increment bf
				bf++;
			}
			else
			{
				// get old bf
				oldbf = Right()->BalanceFactor();

				// insert right
				Right()->Insert(data);

				// if bf changed and is not 0 increment bf
				if (oldbf != Right()->BalanceFactor() && Right()->BalanceFactor() != 0)
				{
					bf++;
				}
			}
		}

		// call rebalance
		rebalance();
	};

	// restores AVL invariant
	void rebalance()
	{
		if (bf < -1)
		{
			if (Left()->BalanceFactor() <= 0) zig(); // left left
			
			else if (Left()->BalanceFactor() > 0) zigzag(); // left right
		}
		else if (bf > 1)
		{
			if (Right()->BalanceFactor() >= 0) zag(); // right right

			else if (Right()->BalanceFactor() < 0) zagzig(); // right left
		}
	}

	void zig()
	{
		// check if empty
		if (Empty()) return;

		// check if left is empty
		if (left->Empty()) return;

		// get bf for this and left
		int bfA = bf;
		int bfB = Left()->BalanceFactor();

		// call zig
		BalanceTree<x>::zig();

		// update bf
		if (bfA < 0)
		{
			Right()->BalanceFactor(bfA - bfB + 1);
			bf = bfA + 2;
		}
		else
		{
			bf = 1 + bfB;
			Right()->BalanceFactor(1 + bfB);
		}

	};

	void zag()
	{
		// check if empty
		if (Empty()) return;

		// check if left is empty
		if (right->Empty()) return;

		// get bf for this and left
		int bfA = bf;
		int bfB = Right()->BalanceFactor();

		// call zig
		BalanceTree<x>::zag();

		// update bf
		if (bfA < 0)
		{
			Left()->BalanceFactor(bfA + bfB - 1);
			bf = bfA - 2;
		}
		else
		{
			bf = 1 - bfB;
			Left()->BalanceFactor(1 - bfB);
		}

	};

	void remove(x data)
	{
		try
		{
			if (Empty()) throw notFound;
		}
		catch (BinarySearchTreeNotFound e)
		{
			cout << "NOT FOUND" << endl;
			return;
		}

		// get old bf
		int oldbf = 0;

		// if root is greater than data go left
		if (Root() > data)
		{
			oldbf = Left()->BalanceFactor();
			Left()->Remove(data);

			// check if left is now empty or if the height changed
			if (Left()->Empty() || (Left()->BalanceFactor() != oldbf && Left()->BalanceFactor() == 0))
			{
				bf++;
			}
		}

		else if (Root() < data)
		{
			oldbf = Right()->BalanceFactor();
			Right()->Remove(data);

			// if right is empty or if the height changed
			if (Right()->Empty() || (Right()->BalanceFactor() != oldbf && Right()->BalanceFactor() == 0))
			{
				bf--;
			}
		}
		else // there is a match
		{
			cout << "225\n";

			if (Right()->Empty())
			{
				cout << "229\n";

				// get old left
				AVLtree<x>* oldLeft = Left();
				delete right; // delete right
				delete root; // delete root

				cout << "236\n";

				// copy over left into this tree
				copy(left);

				cout << "243\n";

				// null old left
				oldLeft->null();

				cout << "246\n";

				// delete old left
				delete oldLeft;
				
				// set bf
				bf = 0;
			}

			else if (Left()->Empty())
			{
				cout << "253\n";

				// get old right
				AVLtree<x>* oldRight = Right();
				delete left;
				delete root;		

				// copy over right
				copy(right);

				// null old right
				oldRight->null();

				// delete old right
				delete oldRight;

				// set bf
				bf = 0;
			}
			else
			{
				cout << "272\n";

				// find inorder successor
				AVLtree<x>* successor = Right();

				while (!successor->Right()->Empty()) successor = successor->Left();

				// delete root
				delete root;

				// copy over successor root
				Root(successor->Root());

				// get old bf
				oldbf = Right()->BalanceFactor();

				// delete inorder successor
				Right()->Remove(successor->Root());

				// if right is empty the height changed
				if (Right()->Empty() || (Right()->BalanceFactor() != oldbf && Right()->BalanceFactor() == 0)) bf--;

			}
		
			cout << "294\n";
		}

		rebalance();

	}

	void null()
	{
		BalanceTree<x>::null();
		bf = 0;
	}

	void empty()
	{
		cout << "317\n";

		if (root != NULL) delete root;

		cout << "321\n";

		root = NULL;

		cout << "325\n";

		if (left != NULL) delete left;

		cout << "329\n";

		left = NULL;

		cout << "333\n";

		if (right != NULL) delete right;

		cout << "337\n";

		right = NULL;

		cout << "341\n";
	}

public:

	AVLtree* Left()
	{
		return ((AVLtree<x>*) left);
	}

	AVLtree* Right()
	{
		return ((AVLtree<x>*) right);
	}

	void Left(AVLtree* left)
	{
		this->left = left;
	}

	void Right(AVLtree* right)
	{
		this->right = right;
	}

	int BalanceFactor()
	{
		return bf;
	}

	void BalanceFactor(int bf)
	{
		this->bf = bf;
	}

	// insert, log base 2 n
	void Insert(x& data)
	{
		insert(data);
	};

	// remove, log base 2 n
	void Remove(x data)
	{
		remove(data);
	};

	// default constructor
	AVLtree() : BalanceTree<x>()
	{
		bf = 0;
	};

	// initializer 
	AVLtree(x root)
	{
		bf = 0;
		this->root = new x(root);
		left = grow();
		right = grow();
	}

	// destructor
	~AVLtree()
	{
	};


};