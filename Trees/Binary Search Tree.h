#pragma once
#include <iostream>

using namespace std;

class BinarySearchTreeException : public exception {};
class BinarySearchTreeNotFound : public BinarySearchTreeException {} notFound;
class BinarySearchTreeEmpty : public BinarySearchTreeException {} emptyTree;
class BinarySearchTreeNOTBST :public BinarySearchTreeException {} notBST;
class BinarySearchTreeChangedSubtree : public BinarySearchTreeException {} changedSubtree;

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
	BinarySearchTree<x>* find(x& data)
	{
		// get this
		BinarySearchTree<x>* tree = this;

		// traverse this, left, right
		while (true)
		{
			// if tree is empty return
			if (tree->Empty()) return tree;

			// if tree.root < data return tree.right
			if (tree->Root() < data) { tree = tree->Right(); }

			// or left
			else if (tree->Root() > data) {	tree = tree->Left();}

			// else tree = data
			else return tree; 
		}
	};

	// swap root with other root
	void swap(BinarySearchTree<x>* tree)
	{

		x temp = tree->Root();

		*(tree->root) = *root;

		*root = temp;
	}

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

	// make tree NULL
	virtual void null()
	{
		root = NULL;
		left = NULL;
		right = NULL;
	};

	// copy a tree
	virtual void copy(BinarySearchTree<x>* tree)
	{
		root = tree->root;

		left = tree->Left();

		right = tree->Right();
	};

	// empty out a tree
	virtual void empty()
	{
		if (root != NULL) delete root;

		root = NULL;

		if (left != NULL) delete left;

		left = NULL;

		if (right != NULL) delete right;

		right = NULL;
	};

	// print method, inorder
	virtual void print(ostream& os)
	{
		// print left
		if (left != NULL) left->print(os);

		// if root is not null output it
		if (root == NULL) return;
		else os << *root << " ";

		// print right
		if (right != NULL) right->print(os);
	};

	// prints tree structure
	virtual void printTree(ostream& os, int level)
	{
		// check if empty
		if (Empty()) return;

		// print right
		right->printTree(os, level + 1);

		// output spaces per level
		for (int i = 0; i < level + 1; i++) os << " ";

		// print this
		os << " /" << endl;
		
		// output spaces per level
		for (int i = 0; i < level; i++) os << " ";

		os << Root() << endl;

		// output spaces per level
		for (int i = 0; i < level + 1; i++) os << " ";

		os << " \\" << endl;

		// print left
		left->printTree(os, level + 1);
	}

public:

	// get root
	x Root() { return *root; };

	// get root
	void Root(x root)
	{
		this->root = new x(root);

		// see if the user messed up and violated the BST

		try
		{
			if (Root() < left->Root() || Root() > right->Root()) throw notBST;
		}
		catch (BinarySearchTreeNOTBST e)
		{
			cout << "\nTREE VIOLATED - NOT A BINARY SEARCH TREE\n\n";
		}
	};

	// get left
	virtual BinarySearchTree* Left() { return left; };

	// get right
	virtual BinarySearchTree* Right() { return right; };

	// set left
	virtual void Left(BinarySearchTree* left)
	{
		this->left = left;
		// see if the user messed up and violated the BST

		try
		{
			if (Root() < left->Root()) throw notBST;
		}
		catch (BinarySearchTreeNOTBST e)
		{
			cout << "\nTREE VIOLATED - NOT A BINARY SEARCH TREE\n\n";
		}
	};

	// set right
	virtual void Right(BinarySearchTree* right)
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

	};

	// Find node in the tree O(n) where n is the height of the tree, worst case # of nodes in the tree
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

	// insert node into the tree worst case n nodes to insert times O(n) for find = O(n^2)    
	virtual void Insert(x& data)
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
	virtual void Remove(x& data)
	{
		// get the node to remove
		BinarySearchTree<x>* tree = find(data);

		// left and right pointers
		BinarySearchTree<x>* treeL;
		BinarySearchTree<x>* treeR;

		// case 1: tree is empty, throw exception
		try
		{
			if (tree->Empty()) throw emptyTree;
		}
		catch (BinarySearchTreeEmpty e)
		{
			cout << "TREE EMPTY, NOTHING TO REMOVE" << endl;
			return;
		};

		// case 2: two empty subtrees
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

		// case 3: tree has data + 1 empty tree + 1 tree with data, replace 
		// this tree with the tree containing data
		if (tree->Left()->Empty() && !tree->Right()->Empty())
		{
			treeR = tree->Right();

			tree->copy(treeR);

			treeR->null();

			//delete treeR;

			return;
		}

		// case 2:
		else if (tree->right->Empty() && !tree->Left()->Empty())
		{
			treeL = tree->Left();

			tree->copy(treeL);

			treeL->null();

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
			while (!treeR->Left()->Empty())
			{
				treeR = treeR->Left();
			}

			// override tree root with treeR root
			tree->Root(treeR->Root());

			//delete treeL;
			
			Right()->Remove((*treeR->root));

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

	// greater than operator
	bool operator> (BinarySearchTree<x>* tree)
	{
		if (!Empty() && !tree->Empty()) return *root > tree->Root();
		else if (!Empty() && tree->Empty()) return true;
		else if (Empty() && !tree->Empty()) return false;
	}

	// less than operator
	bool operator< (BinarySearchTree<x>* tree)
	{
		if (!Empty() && !tree->Empty()) return *root < tree->Root();
		else if (!Empty() && tree->Empty()) return true;
		else if (Empty() && !tree->Empty()) return false;
	}

	// equal to operator
	bool operator== (BinarySearchTree<x>* tree)
	{
		if (Empty() && tree->Empty()) return true;
		else if (!Empty() && !tree->Empty()) return *root == tree->Root();
		else return false;
	}

	// greater than operator
	bool operator> (const x& data)
	{
		if (!Empty()) return *root > data;
		else return false;
	}

	// less than operator
	bool operator< (const x& data)
	{
		if (!Empty()) return *root < data;
		else  return false;
	}

	// equal to operator
	bool operator== (const x& data)
	{
		if (!Empty()) return *root == data;
		else return false;
	}

	// output operator
	friend ostream& operator<<(ostream& os, BinarySearchTree& tree)
	{
		tree.print(os);

		return os;
	};

	// assignment operator
	BinarySearchTree& operator=(BinarySearchTree& tree)
	{

		// assign new data
		root = new x(*tree.root);
		left = new BinarySearchTree<x>(*tree.left);
		right = new BinarySearchTree<x>(*tree.right);

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
	BinarySearchTree(const x& root)
	{

		this->root = new x(root);
		left = grow();
		right = grow();
		subtree = false;
	};

	// copy constructor
	BinarySearchTree(BinarySearchTree& tree)
	{
		root = new x(*tree.root);
		left = new BinarySearchTree<x>(*tree.left);
		right = new BinarySearchTree<x>(*tree.right);
		subtree = tree.subtree;
	};

	// destructor
	virtual ~BinarySearchTree()
	{
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

		
	};
};