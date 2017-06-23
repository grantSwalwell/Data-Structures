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

	int BalanceFactor()
	{
		return bf;
	}

	// insert, log base 2 n
	void Insert(x& data)
	{
		insert(data);
	};

	// remove, log base 2 n
	void Remove(x& data)
	{

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