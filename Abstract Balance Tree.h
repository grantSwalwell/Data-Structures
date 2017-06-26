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

	/*

	// root data
	x* root;

	// left child
	BalanceTree<x>* left;

	// right child
	BalanceTree<x>* right;

	// is-a subtree or not
	bool subtree;
	
	*/

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
		BalanceTree<x>* rightChild = (BalanceTree<x>*) this->right;

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

		// call zag
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

	/*

	// internal find O(n)
	BalanceTree* find(x& data)
	{
		// get this
		BalanceTree<x>* tree = this;

		// traverse this, left, right
		while (true)
		{
			// if tree is empty return
			if (tree->Empty()) return tree;

			// if tree.root < data return tree.right
			if (*(tree->root) < data) tree = tree->right;

			// or left
			else if (*(tree->root) > data) tree = tree->left;

			// else tree = data
			else return tree;

		}
	};

	// swap root with other root
	void swap(BalanceTree* tree)
	{
		x temp = tree->Root();

		tree->Root(Root());

		Root(temp);
	}

	// override of grow
	virtual BalanceTree* grow()
	{
		// grow a new tree
		BalanceTree<x>* tree = new BalanceTree<x>();

		// specify it as a subtree
		tree->subtree = true;

		// return the tree
		return tree;
	}

	// print method, inorder
	void print(ostream& os)
	{
		// print left
		if (left != NULL) left->print(os);

		// if root is not null output it
		if (root == NULL) return;
		else os << *root << " ";

		// print right
		if (right != NULL) right->print(os);
	};

	*/

public:

	/*

	// get root
	x Root()
	{
		return *root;
	};

	// get root
	x Root(x root)
	{
		(*this->root) = root;

		return (*this->root);
	};

	*/

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

	/*

	// Find node in the tree O(n) where n is the height of the tree, worst case # of nodes in the tree
	x Find(x& data)
	{
		// find the right node
		BalanceTree<x>* tree = find(data);

		try
		{
			// output if node is empty 
			if (tree->Empty())
			{
				throw notFound;
			};

			// return tree data
			return *(tree->root);
		}
		catch (BalanceTreeNotFound e)
		{
			cout << "NODE NOT FOUND" << endl;
		};

	};

	// insert node into the tree worst case n nodes to insert times O(n) for find = O(n^2)    
	virtual void Insert(x& data)
	{
		// get the tree to insert into
		BalanceTree<x>* tree = find(data);

		// if tree is empty insert it, else override it
		if (tree->Empty())
		{
			// set root
			tree->root = new x(data);

			// grow new subtrees
			tree->left = grow();
			tree->right = grow();
		}
		else
		{
			// delete root
			delete tree->root;

			// set root
			tree->root = new x(data);
		}
	};

	// remove this node, 4 cases, O(n)
	virtual void Remove(x& data)
	{
		// get the node to remove
		BalanceTree<x>* tree = find(data);

		// left and right pointers
		BalanceTree<x>* treeL;
		BalanceTree<x>* treeR;

		// case 1: tree is empty, throw exception
		try
		{
			if (tree->Empty()) throw emptyTree;
		}
		catch (BalanceTreeEmpty e)
		{
			cout << "TREE EMPTY, NOTHING TO REMOVE" << endl;
		};

		// case 3: two empty subtrees
		if (tree->left->Empty() && tree->right->Empty())
		{

			// delete root
			delete tree->root;

			// set to null
			tree->root = NULL;

			// delete left
			delete tree->left;

			// null left
			tree->left = NULL;

			// delete right
			delete tree->right;

			// null right
			tree->right = NULL;

			// return
			return;
		}

		// case 2: tree has data + 1 empty tree + 1 tree with data, replace this tree with the tree containing data
		if (tree->left->Empty())
		{

			// set tree root to right root
			tree->root = tree->right->root;

			// set right root to null
			tree->right->root = NULL;

			// get right right
			treeR = tree->right;

			// set tree.right to tree right right
			tree->right = tree->right->right;

			// make treeR null
			//treeR->null();

			// delete right
			delete treeR;

			// return
			return;
		}

		// case 2:
		else if (tree->right->Empty())
		{

			// get pointer to left
			treeL = tree->left;

			// copy left root to tree root
			tree->root = tree->left->root;

			// null out root
			tree->left->root = NULL;

			// set tree left to be tree left left
			tree->left = tree->left->left;

			// null left
			//treeL->null();

			// delete pointer to left	
			delete treeL;

			return;
		}

		// case 4: two non empty subtrees
		else
		{

			// get pointer to right to go right, treeR = tree.right
			treeR = tree->right;

			// get pointer to left
			treeL = tree->left;

			// then go as left as possible treeR = treeR.left.left.left...
			while (!treeR->left->Empty())
			{
				treeR = treeR->left;
			}

			// override tree root with treeR root
			tree->Root(treeR->Root());

			// remove old node on the right side
			tree->right->Remove(*(tree->root));
		}



	};

	// contains node or not
	bool Contains(x& data)
	{
		// call internal find
		BalanceTree<int>* tree = find(data);

		// return empty or not
		return !tree->Empty();
	};

	// empty or not
	bool Empty()
	{
		return root == NULL;
	}

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

	// output operator
	friend ostream& operator<<(ostream& os, BalanceTree& tree)
	{
		tree.print(os);

		return os;
	};
	*/

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
		//root = NULL;
		//left = NULL;
		//right = NULL;
		//subtree = false;
	};

	// initializer
	BalanceTree(x& root) : BinarySearchTree<x>(root)
	{
		//this->root = new x(root);
		//left = grow();
		//right = grow();
	};

	// copy constructor
	BalanceTree(BalanceTree& tree) : BinarySearchTree<x>(tree)
	{
		//root = new x(tree.root);
		//left = new BalanceTree<x>(tree.left);
		//right = new BalanceTree<x>(tree.right);
		//subtree = tree.subtree;
	};


	// destructor
	virtual ~BalanceTree()
	{
		/*
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

		*/
	};


};