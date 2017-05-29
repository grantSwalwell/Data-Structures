#pragma once
#include <iostream>
#include "Binary Tree - Array.h"

using namespace std;

// this is an array implementation of a Binary Search Tree

template <class x> class BiSearchTree : public BiTree<x>
{
private:




public: 

	// keep track of max number of searches done by search
	int max;

	// number of searches done in search method
	int searches;

	// methods

	// get element at vector position
	Node<x>* at(int index)
	{
		return tree->at(index);
	}

	// search, returns vector index of node, uses a binary search
	int search(x& data)
	{
		// search index
		int index = root;

		// if root is null bail out
		if (tree->at(root) == NULL) return index;

		// search counter to know when to give up
		searches = 0;

		// pointer to node being checked
		Node<x>* node;

		// while searches < nodes
		while (searches <= max + 1)
		{
			// increment searches
			searches++;

			// get node at index
			node = tree->at(index);

			// if this node is equal return index
			if (*node == data) return index;

			// going left
			if (*node > data)
			{
				// has a left
				if (node->left != -1) index = node->left;
				
				// if data > node and node does not have a right child just return index
				if (node->left == -1) return index;
			}
		
			// going right
			if (*node < data)
			{
				// has a right
				if (node->right != -1) index = node->right;

				// if data > node and node does not have a right child just return index for use in insert
				if (node->right == -1) return index;
			}
	
		}





	};

	// insert element, uses add from BT to simplify process
	void insert(x& data)
	{
		// if we have space, else return 
		if (nodes < size)
		{
			// position the new node will be at
			int pos = free->top();

			// call add
			this->add(data);

			// lets get a pointer to it
			Node<x>* node = tree->at(pos);

			// set child index
			node->index = pos;

			// set node pointer
			node->tree = this->tree;

			// that may have been the first element to go making the rest unnecessary
			if (pos != root)
			{
				// use search to get the index position of what should be its parent
				int index = search(data);

				// set parent index
				node->parent = index;

				// the node at this position has an empty left or right subtree, we will grab a pointer to it
				Node<x>* parent = tree->at(index);

				// if the elements are the same just return
				if (*parent == data) return;

				// both trees could be empty so we need to make comparison and put it in the correct subtree

				// if parent is greater than parent it is left, else it is right, but I played it safe and made sure were not using a taken spot
				if (*parent < *node && parent->right == -1) parent->right = pos;
			
				else if(*parent > *node && parent->left == -1) parent->left = pos;
			
			}

			// Now we check if we reached a new search max, meaning we searched to the bottom of the tree for a position to insert into
			if (searches > max)
			{
				max = searches;

				// we are inserting a new element at the bottom so we are increasing the height, therefore height equal max + 1
				// we double checking that the new height is greater
				if (max + 1 > height) height = max + 1;
			}

		}
		else return;
	
	};

	// remove element, uses search to find index, BT remove to remove element
	void remove(x& data)
	{
		// 4 cases
		// 1, data is not in the vector
		// 2, data has no subtrees, just call remove index
		// 3, data has 1 subtree, replace with that subtree
		// 4, data has two subtrees, replace with smallest element in right subtree
		

		// search for it's position
		int index = search(data);

		// get pointer to node
		Node<x>* node = tree->at(index);

		// case 1, make sure node = data, if not return
		if (*node != data)
		{
			return;
			
		}
		// case 2, left and right == -1 we can just remove this index
		else if (node->left == -1 && node->right == -1)
		{
			// we have set the parent index appropriately
			// get parent of min so we can alert it to it no longer having a subtree
			if (node->parent != -1)
			{
				// get pointer to parent
				Node<x>* parent = tree->at(node->parent);
				
				if (parent->left == index) parent->left = -1;
				if (parent->right == index) parent->right = -1;
			}

			this->BiTree::remove(index); 

			return;
		}
		// case 3, empty right subtree, replace with left subtree
		else if (node->right == -1 && node->left != -1)
		{
			// get left index
			int l = node->left;
			
			// get left node
			Node<x>* left = tree->at(l);

			// get left info
			node->info = left->info;

			// set left info to null
			left->info = NULL;

			// set node right to left right
			node->right = left->right;
			
			// and node left to left left
			node->left = left->left;
						
			// remove node at left
			this->BiTree::remove(l);

			return;
		}
		// case 3 and 4, if the left subtree is empty or if it has two subtrees we must replace it with the smallest in the right subtree
		else if (node->right != -1)
		{


			// find the min, go right then left
			Node<x>* min = tree->at(node->right);

			// while min left isn't negative one keep going left
			while (min->left != -1) min = tree->at(min->left);

			// hold a copy of min info to remove min
			x* minfo = new x(*min->info);

			// get parent of min so we can alert it to it no longer having a subtree
			int minparent = -1;

			if (min->parent != -1) minparent = min->parent;

			// get pointer to parent
			Node<x>* parent = NULL;
			if (minparent != -1)
			{
				parent = tree->at(minparent);

				// min SHOULD always be a left child but I am going to check just in case

				if (parent->left == min->index) parent->left = -1;
				if (parent->right == min->index) parent->right = -1;
			}
			
			// remove min
			this->BiTree::remove(min->index);

			// now set node to info
			node->info = minfo;

			return;
		}


		return;
	};

	// recursive inorder solution

	// inorder traversal of the tree, returns a stack of indexes in order
	stack<int>* inorder()
	{
		// index stack
		stack<int>* order = new stack<int>;

		// root node
		Node<x>* r00t = tree->at(root);

		// call inorder on root, pass it the stack
		r00t->inorder(order);

		// return stack
		return order;
	};

	// preorder traversal of the tree
	stack<int>* preorder()
	{
		// index stack
		stack<int>* order = new stack<int>;

		// get root
		Node<x>* r00t = tree->at(root);

		// call preorder on root
		r00t->preorder(order);

		// return stack
		return order;
	};
	
	// operators
	
	// output operator, prints out the inorder and preorder traversal 
	friend ostream& operator<< (ostream& os, BiSearchTree& tree)
	{
		// for inorder traversal
		stack<int>* inorder = tree.inorder();

		// for preorder traversal
		stack<int>* preorder = tree.preorder();

		//cout << "start" << endl;
		
		// lets borrow the vector to make life easier
		vector<Node<x>*>* vec = tree.tree;

		// index for output format
		int index = 0;

		// starting index
		int n = tree.root;

		// starting node
		Node<x>* node = vec->at(n);

		cout << "Inorder: ";

		while (!inorder->empty())
		{
			// if index is divisible by 20 we could use an inline
			if (index % 20 == 0) cout << endl;

			// get the top index
			int n = inorder->top();

			// set node
			node = vec->at(n);

			// output node
			cout << *node << " ";

			// pop inorder
			inorder->pop();

			// increment index
			index++;
		}

		// toss in an endl
		cout << endl << endl;

		index = 0;

		// now for preorder
		cout << "Preorder: ";

		// while the stack isn't empty
		while (!preorder->empty())
		{
			// if index is divisible by 20 we could use an inline
			if (index % 20 == 0) cout << endl;

			// get the top index
			int n = preorder->top();

			// set node
			node = vec->at(n);

			// output node
			cout << *node << " ";

			// pop inorder
			preorder->pop();

			// increment index
			index++;
		}

		// toss in an endl
		cout << endl << endl;

		// return ostream
		return os;
	};


	// assignment operator
	BiSearchTree& operator= (BiSearchTree& tree)
	{
		this->tree = tree.tree;
		this->root = tree.root;
		this->nodes = tree.nodes;
		this->size = tree.size;
		this->height = tree.height;
		this->free = tree.free;
		this->max = tree.max;
		this->searches = tree.searches;

		return *this
	}

	// constructors

	// default constructor
	BiSearchTree() : BiTree() { max = 0; searches = 0; };

	// initializer 
	BiSearchTree(int size) : BiTree(size) { max = 0; searches = 0; };

	// copy constructor
	BiSearchTree(BiSearchTree& tree) : BiTree(tree)
	{ 
		max = tree.max; 
		searches = tree.searches;
	};

	// destructor
	~BiSearchTree() {  };



};