#pragma once
#include <iostream>
#include "Abstract Balance Tree.h"

template <class x> class  AVLtree : public BalanceTree<x>
{

protected:

	// the balance factor
	int bf;


public:



	AVLtree() : BalanceTree<x>()
	{
		bf = 0;
	};


};