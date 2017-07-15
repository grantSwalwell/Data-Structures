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

	// parent of the tree
	RedBlack<x>* parent;

	// zig, clockwise rotation, needs to adjust colors
	void zig()
	{
		BalanceTree<x>::zig();
	}

	// zag, counter clockwise rotation, needs to adjust colors
	void zag()
	{
		BalanceTree<x>::zag();
	}

	void zigzag()
	{
		if (Empty()) return;

		Left()->zag();

		Color(RED);

		Left()->Color(BLACK);

		zig();
	}

	void zagzig()
	{
		if (Empty()) return;

		Right()->zig();

		Color(RED);

		Right()->Color(BLACK);

		zag();
	}


	// grow a new tree
	RedBlack<x>* grow()
	{
		RedBlack<x>* tree = new RedBlack<x>(this);

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

		// pointers to left and right
		RedBlack<x>* LEFT = Left();
		RedBlack<x>* RIGHT = Right();

		// pointer to uncle and grandparent
		RedBlack<x>* uncle = Uncle();
		RedBlack<x>* grandparent = Grandparent();
		
		// CASE 1: parent is null, we are at the root, set it black 
		if (parent == NULL) color = BLACK;

		// CASE 2: parent is black
		else if (*parent == BLACK) return;

		// CASE 3: uncle is red, color parent and uncle black, grandparent to red
		if (uncle != NULL && *uncle == RED && *parent == RED)
		{
			parent->Color(BLACK);
			
			uncle->Color(BLACK);
			
			grandparent->Color(RED);
			
			grandparent->RedRule();
		}

		// CASE 4: red parent black uncle, black grandparent 
		if (uncle != NULL && *uncle == BLACK && *parent == RED)
		{

			//  grandparent left = parent
			if (!grandparent->Left()->Empty() && *parent == grandparent->Left())
			{

				// this equal parent left, left left violation
				if (!parent->Left()->Empty() && *this == parent->Left())
				{
					//parent->Color(BLACK);
					//grandparent->Color(RED);
					grandparent->zig();
				}

				// this equal parent right, left right violation
				else if (!parent->Right()->Empty() && *this == parent->Right())
				{
					grandparent->zigzag();
				}

			}

			// else if we are grandparent right
			else if (!grandparent->Right()->Empty() && *parent == grandparent->Right())
			{
				// this equal parent right, right left violation
				if (!parent->Left()->Empty() && *this == parent->Left())
				{
					grandparent->zagzig();
				}

				// this equal parent right,  violation
				else if (!parent->Right()->Empty() && *this == parent->Right())
				{
					//parent->Color(BLACK);
					//grandparent->Color(RED);
					grandparent->zag();
				}


			}

		}

		// CASE 5: 




		/*
		// if red
		if (color == RED)
		{
			// if left or right are red rule violated, switch to black
			if (*Left() == RED || *Right() == RED)
			{
				color = BLACK;

				//cout << "CASE 1: ROOT IS RED SO IS CHILD\n";
			}
		}


		if (*Left() == RED && *Right() == BLACK)
		{
			//cout << "LEFT RED RIGHT BLACK\n";

			if (*LEFT->Right() == RED)
			{
				cout << "LEFT RIGHT IS RED\n";

				zigzag();
			}
			else if (*LEFT->Left() == RED)
			{
				cout << "LEFT LEFT IS RED\n";

				zig();
			}
		}
		else if (*Left() == BLACK && *Right() == RED)
		{
			//cout << "LEFT BLACK RIGHT RED\n";

			if (*RIGHT->Right() == RED)
			{
				zagzig();
			}
			else if (*RIGHT->Left() == RED)
			{
				zag();
			}
		}
		else if (*Left() == RED && *Right() == RED)
		{
			cout << "LEFT RED RIGHT RED\n";

			LEFT->Color(BLACK);
			RIGHT->Color(BLACK);
			color = RED;
		}
		*/

		/*
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

	// get parent
	RedBlack<x>* Parent()
	{
		return parent;
	}

	// get grandparent
	RedBlack<x>* Grandparent()
	{
		if (parent != NULL) return parent->Parent();
		else return NULL;
	}

	// get uncle
	RedBlack<x>* Uncle()
	{
		RedBlack<x>* grand = Grandparent();
		
		// if grandparent is null there is no uncle
		if (grand == NULL) return NULL;
		else
		{
			if (!grand->Left()->Empty() && grand->Left()->Root() == parent->Root())
			{
				return grand->Right();
			}
			else return grand->Left();
		}
	}


	// insert
	void Insert(const x& element)
	{
		insert(element);
	}

	// color equality operator
	bool operator== (int color)
	{
		if (this->color == color) return true;
		else return false;
	}

	// test for root equality
	bool operator== (RedBlack<x>* tree)
	{
		if (Root() == tree->Root()) return true;
		else return false;
	}

	// assignment operator
	RedBlack<x>& operator=(RedBlack<x>& tree)
	{
		this->color = tree->Color();
		(*this->root) = tree->Root();
		this->left = tree->Left();
		this->right = tree->Right();
		this->parent = tree->Parent();
	}

	// default constructor
	RedBlack() : BalanceTree<x>()
	{
		color = BLACK;
		parent = NULL;
	}

	// parent initializer
	RedBlack(RedBlack<x>* parent) : BalanceTree<x>()
	{
		color = BLACK;
		this->parent = parent;
	}

	// initializer
	RedBlack(const x& root) : BalanceTree<x>(root)
	{
		color = RED;
		parent = NULL;
	}

	// copy constructor
	RedBlack(RedBlack<x>& tree) : BalanceTree<x>(tree)
	{
		this->color = tree->Color();
		parent = tree.Parent();
	}

	// destructor
	~RedBlack() { };
};