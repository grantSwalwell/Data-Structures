#include <iostream>
#include "BinarySearchTree.h"
#include "Queue - LinkedList.h"

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
		BinarySearchTree<x>* left;
		BinarySearchTree<x>* right;

		// while preorder is not empty
		while (!preorder->empty())
		{
			// dequeue next node
			node = preorder->dequeue();

			// push onto queue
			queue->push(node);

			// if left subtree is not empty add it to queue
			if (!node->Left()->Empty())
			{
				left = node->Left();

				preorder->push(left);
			}

			// same for right
			if (!node->Right()->Empty())
			{
				right = node->Right();

				preorder->push(right);
			}
		}


	};

	void print(ostream& os)
	{

		// call enumerate
		enumerate();

		// set level
		level = 0;

		BinarySearchTree<int>* node = queue->front();

		while (!queue->empty())
		{
			cout << (*queue->front()) << endl;

			queue->dequeue();
		};


		return;

		// for each level
		for (int i = 0; i < levels; i++)
		{
			node = queue->front();

			while (node->Height() == levels - i)
			{
				os << node->Root() << " ";

				queue->dequeue();

				node = queue->front();
			};



			

			os << endl;
		}

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