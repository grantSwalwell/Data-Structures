#pragma once
#include <iostream>
#include "BinaryTree.h"

using namespace std;

class BinarySearchTreeException : public exception {};
class BinarySearchTreeNotFound : public BinarySearchTreeException {} notFound;
class BinarySearchTreeEmpty : public BinarySearchTreeException {} emptyTree;

template <class x> class BinarySearchTree 
{

protected:

	// root data
	x* root;

	// left child
	BinarySearchTree<x>* left;

	// right child
	BinarySearchTree<x>* right;

	// is-a subtree or not
	bool subtree;

	// internal find O(n)
	BinarySearchTree* find(x& data)
	{
		// get this
		BinarySearchTree<x>* tree = this;

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

	// make tree NULL
	void null()
	{
		root = NULL;
		left = NULL;
		right = NULL;
	};

	// copy a tree
	void copy(BinarySearchTree* tree)
	{ 
		root = tree->root;
		cout << "64" << endl;
		if (left != NULL) left->empty();
		cout << "66" << endl;
		left = tree->left;
		cout << "68" << endl;
		if (right != NULL) right->empty();
		cout << "70" << endl;
		right = tree->right; cout << "72" << endl;
	};

	// empty out a tree
	void empty()
	{
		cout << "77" << endl;
		if (root != NULL) delete root;
		cout << "79" << endl;
		root = NULL;

		if (left != NULL) delete left;

		left = NULL;

		if (right != NULL) delete right;

		right = NULL;
	};

	// grow a subtree node
	BinarySearchTree* grow()
	{
		// grow a new tree
		BinarySearchTree<x>* tree = new BinarySearchTree<x>;

		// specify it as a subtree
		tree->subtree = true;

		// return the tree
		return tree;
	};

	// print method
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

public:

	// Fine node in the tree O(n) where n is the height of the tree, worst case # of nodes in the tree
	x Find(x& data)
	{
		
		// find the right node
		BinarySearchTree<x>* tree = find(data);

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
		catch (BinarySearchTreeNotFound e)
		{
			cout << "NODE NOT FOUND" << endl;
		};
		
	};

	// insert node into the tree worst case n nodes to inser x O(n) for find = O(n^2)    
	void Insert(x& data)
	{
		// get the tree to insert into
		BinarySearchTree<x>* tree = find(data);

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
	void Remove(x& data)
	{
		// get the node to remove
		BinarySearchTree<x>* tree = find(data);

		// left and right pointers
		BinarySearchTree<x>* treeL;
		BinarySearchTree<x>* treeR;

		cout << "DATA: " << data << ", THE TREE: " << *tree << endl;

		// case 1: tree is empty, throw exception
		try
		{
			if (tree->Empty()) throw emptyTree;
		}
		catch (BinarySearchTreeEmpty e)
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
			treeR->null();

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
			treeL->null();

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
			tree->root = treeR->root;

			// remove old node on the right side
			tree->right->Remove(*(tree->root));

			
		}

		
		
	};

	// contains node or not
	bool Contains(x& data)
	{
		// call internal find
		BinarySearchTree<int>* tree = find(data);

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
	friend ostream& operator<<(ostream& os, BinarySearchTree& tree)
	{
		tree.print(os);

		return os;
	};

	// assignment operator
	BinarySearchTree& operator=(BinarySearchTree& tree)
	{
		// delete old data to prevent memory leaks
		if (root != NULL)
		{
			delete root;
			root = NULL;
		};

		if (left != NULL)
		{
			delete left;
			left = NULL;
		};

		if (right != NULL)
		{
			delete right;
			right = NULL;
		};

		// assign new data
		root = tree.root;
		left = tree.left;
		right = tree.right;

		return *this;
	};

	// default constructor
	BinarySearchTree() 
	{
		root = NULL;
		left = NULL;
		right = NULL;
		subtree = false;
	};

	// initializer 1
	BinarySearchTree(x root, BinarySearchTree* left, BinarySearchTree* right) 
	{
		this->root = new x(root);
		
		// if left is null create an empty tree
		if (left == NULL) this->left = grow();
		else this->left = left;

		// same for right
		if (right == NULL) this->right = grow();
		this->right = right;
		
		subtree = false;
	};

	// initializer 2
	BinarySearchTree(x root)
	{
		this->root = new x(root);
		left = grow();
		right = grow();
		subtree = false;
	};

	// copy constructor
	BinarySearchTree(BinarySearchTree& tree)
	{
		root = tree.root;
		left = tree.left;
		right = tree.right;
		subtree = tree.subtree;
	};

	// destructor
	~BinarySearchTree()
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