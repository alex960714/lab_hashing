#ifndef _T_TREE_NODE_H_
#define _T_TREE_NODE_H_

#include "TRecord.h"

class TTreeNode
{
public:
	TRecord rec;
	TTreeNode *pLeft, *pRight;

	TTreeNode(TRecord _rec, TTreeNode *pL = NULL, TTreeNode *pR = NULL)
	{
		rec = _rec;
		pLeft = pL;
		pRight = pR;
	};
	~TTreeNode() {};
};


#endif