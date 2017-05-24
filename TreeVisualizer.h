#include <iostream>
#include "Data-Structures\BinarySearchTree.h"
#include "Data-Structures\Queue - LinkedList.h"

using namespace std;

template <class x> class PrintTree
{

protected: 

	// the tree to print
	BinarySearchTree<x>* tree;

	// Queue for preorder enumeration
	Queue<BinarySearchTree<x>*>* queue = new Queue<BinarySearchTree<x>*>;

	// current level
	int level;

	// number of levels
	int levels;

	// fills the Queue in a preorder enumeration
	void enumerate() 
	{
		Queue<BinarySearchTree<x>*>* preorder = new Queue<BinarySearchTree<x>*>;

		// push the root
		preorder->push(tree);

		// get a pointer to node
		BinarySearchTree<x>* node = tree;

		// get pointers to left and right
		BinarySearchTree<x>* left = node;
		BinarySearchTree<x>* right = node;

		// while preorder is not empty
		while (!preorder->empty())
		{
			node = preorder->dequeue();

			//left = node->Left();

			//right = node->Right();

			//queue->push(left);

			//queue->push(right);

		}


	};

	void print(ostream& os)
	{

		// call enumerate
		enumerate();

		// for each level
		for (int i = 0; i < levels + (levels - 1); i++)
		{
			if (true) {};



		}




		os << *tree << endl;
	};


public:


	friend ostream& operator<<(ostream& os, PrintTree& tree)
	{
		tree.print(os);

		return os;
	};

	// default constructor
	PrintTree() { tree = NULL; queue = NULL; level = -1; levels = -1; };

	// initializer
	PrintTree(BinarySearchTree<x>* tree)
	{
		this->tree = tree;

		queue = new Queue<BinarySearchTree<x>*>;

		level = 0;

		// get height of the tree = levels
		levels = tree->Height();

	};

	// destructor
	~PrintTree()
	{
		if (tree != NULL)
		{
			delete tree;
			tree = NULL;
		}

		if (queue != NULL)
		{
			delete queue;
			queue = NULL;
		};

		
	};


};