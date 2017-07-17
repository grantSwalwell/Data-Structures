#pragma once
#include "Abstract Balance Tree.h"

using namespace std;

// enumerator for color
enum Color
{
	RED, 
	BLACK,
};


//const short int RED = 0;
//const short int BLACK = 1;

template <class x> class RedBlack : public BalanceTree<x>
{

protected:

	// color of tree
	//short int color;
	Color color;

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

		color = RED;

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

	void remove(bool& blackRule, const x& element)
	{
		// if this is empty return
		if (Empty()) return;

		// if this is greater than element insert left
		else if (*this > element)
		{
			Left()->remove(blackRule, element);
		}

		// else if this is less than element go right
		else if (*this < element)
		{
			Right()->remove(blackRule, element);
		}

		// else this = element
		else if (*this == element)
		{
			// case 1, left and right are empty, destroy this tree
			if (Left()->Empty() && Right()->Empty())
			{
				// if the node is black we are changing the black height and this must be
				// dealt with
				if (color == BLACK) blackRule = false;
				
				// delete and null left, right, and root
				delete root;
				//delete left;
				//delete right;
				
				root = NULL;
				left = NULL;
				right = NULL;
			}

			// case 2, right subtree empty
			else if (!Left()->Empty() && Right()->Empty())
			{
				//if (*this == BLACK && *Left() == RED) Left()->Color(BLACK);

				BlackRule();

				copy(Left());

				
			}

			// case 2, left subtree empty
			else if (Left()->Empty() && !Right()->Empty())
			{
				//if (*this == BLACK && *Right() == RED) Right()->Color(BLACK);

				BlackRule();

				copy(Right());

				
			}

			// case 3, two non empty trees
			else if (!Left()->Empty() && !Right()->Empty())
			{
				RedBlack<x>* succ = Right();

				// get inorder successor
				while (!succ->Left()->Empty())
				{
					succ = succ->Left();
				}

				root = new x(succ->Root());

				Right()->remove(blackRule, succ->Root());

			//	BlackRule();
			}
		}
		else
		{
			cout << "ELEMENT NOT FOUND\n";
		}


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
			if (*parent == grandparent->Left())
			{

				// this equal parent right, left right violation
				if (*this == parent->Right())
				{
					grandparent->zigzag();
				}

				// this equal parent left, left left violation
				else if (*this == parent->Left())
				{
					grandparent->zig();
				}
			}

			// else if we are grandparent right
			else if (*parent == grandparent->Right())
			{
				// this equal parent right, right left violation
				if (*this == parent->Left())
				{
					grandparent->zagzig();
				}

				// this equal parent right,  violation
				else if (*this == parent->Right())
				{
					grandparent->zag();
				}
			}

		} 
		else return;




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


	void BlackRule()
	{
		// get pointer to sibling
		RedBlack<x>* sibling = Sibling();

		// CASE 1: This has one subtree, if this is black and subtree red,
		// set subtree to black
		if (*this == BLACK && *Left() == RED) Left()->Color(BLACK);
		
		// still case 1
		else if (*this == BLACK && *Right() == RED) Right()->Color(BLACK);

		// check for null
		else if (sibling != NULL)
		{			
			// CASE 2: red sibling, switch parent and sibling colors than rotate left or right
			if (*sibling == RED)
			{
				parent->Color(RED);
				sibling->Color(BLACK);

				// if we are left of parent zig, if we are right zag
				if (*this == parent->Left()) parent->zag();
				else parent->zig();
			}

			// check if empty
			else if (sibling->Empty()) return;

			// CASE 3: Black sibling, black parent, black newphews, repaint sibling red
			else if (*sibling == BLACK && *parent == BLACK &&
				*sibling->Left() == BLACK	&& *sibling->Right() == BLACK)
			{
				*sibling = RED;
				parent->BlackRule();
			}

			// CASE 4: Red parent, black sibling, black newphews
			else if (*parent == RED && *sibling == RED && *sibling->Left() == BLACK
				&& *sibling->Right() == BLACK)
			{
				*sibling = RED;
				*parent = BLACK;
			}

			// CASE 5: Black sibling, red newphew, rotate nephew to be where sibling is
			else if (*sibling == BLACK)
			{
				// if this is left
				if (*this == parent->Left() &&
					*sibling->Right() == BLACK &&
					*sibling->Left() == RED)
				{
					// set sibling to red
					sibling->Color(RED);

					// set sibling left to black
					sibling->Left()->Color(BLACK);

					// zig sibling
					sibling->zig();
				}
				else if (*this == parent->Right() &&
					*sibling->Left() == BLACK &&
					*sibling->Right() == RED)
				{
					// same procedure but with zag
					sibling->Color(RED);

					sibling->Right()->Color(BLACK);

					sibling->zag();
				}
			}
		}

	}






	// apply black condition
	void BlackRuleLeft(bool& blackRule)
	{
		// if blackRule is true return
		if (blackRule) return;

		// if left is red color it black
		if (*Left() == RED)
		{
			*Left() = BLACK;
			blackRule = true;
			return;
		}

		// if this is red child must be black
		// switch child/parent colors, if we had red red subtrees zag
		if (*this == RED)
		{
			color = BLACK;

			Right()->Color(RED);

			// If both of rights children are red zag to move one over to left
			if (*Right()->Left() == RED && *Right()->Right() == RED) zag();

			// call red rule
			RedRule();

			blackRule = true;

			return;
		}

		// if right is black and its children red zag after setting right to red
		// call red rule
		if (*Right() == BLACK)
		{
			Right()->Color(RED);

			if (*Right()->Left() == RED && *Right()->Right() == RED)
			{
				zag();
			}

			RedRule();

			if (*this == RED)
			{
				color = BLACK;
				blackRule = true;
			}

			return;
		}
		
		
	}

	void BlackRuleRight(bool& blackRule)
	{
		// if blackRule is true return
		if (blackRule) return;

		// if left is red color it black
		if (*Right() == RED)
		{
			*Right() = BLACK;
			blackRule = true;
			return;
		}
	}

public:

	// get color
	enum Color Color()
	{
		return color;
	}

	// set color
	void Color(enum Color color)
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

	// get sibling
	RedBlack<x>* Sibling()
	{
		if (parent == NULL) return NULL;

		
		if (parent->Left() == this)
		{
			return parent->Right();
		}
		if (parent->Right() == this)
		{
			return parent->Left();
		}

	}

	// insert
	void Insert(const x& element)
	{
		insert(element);
	}

	// remove
	void Remove(const x& element)
	{
		bool blackRule = true;

		remove(blackRule, element);
	}

	// color equality operator
	bool operator== (enum Color color)
	{
		if (this->color == color) return true;
		else return false;
	}

	// test for root equality
	bool operator== (RedBlack<x>* tree)
	{
		if (!Empty() && tree->Empty()) return false;

		if (Empty() && tree->Empty()) return true;
		else if (!Empty() && !tree->Empty() && *root == tree->Root()) return true;
		else return false;
	}

	// test value equality
	bool operator== (const x& data)
	{
		if (!Empty()) return *root == data;
		else return false;
	}

	// assignment operator
	RedBlack<x>& operator=(RedBlack<x>& tree)
	{
		this->color = tree.Color();
		(*this->root) = tree.Root();
		this->left = tree.Left();
		this->right = tree.Right();
		this->parent = tree.Parent();

		return *this;
	}

	// assignment operator for color
	RedBlack<x>& operator=(enum Color color)
	{
		this->color = color;

		return *this;
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
	~RedBlack()
	{
		if (parent != NULL) delete parent;
		parent = NULL;
	};
};