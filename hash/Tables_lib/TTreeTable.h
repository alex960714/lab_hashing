#ifndef _T_TREE_TABLE_H_
#define _T_TREE_TABLE_H_

#include "TTable.h"
#include "TTreeNode.h"
#include "T_Stack.h"

class TTreeTable :public TTable
{
protected:
	TTreeNode *pRoot, *pCurr;
	T_Stack <TTreeNode*> st;
	TTreeNode **pRef;
	int pos;

public:
	TTreeTable() :TTable(), st(100)
	{
		pRoot = NULL;
		pCurr = NULL;
		pRef = NULL;
	}
	virtual ~TTreeTable() {};

	virtual bool IsFull() { return false; };
	virtual bool Find(TKey key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(TKey key);

	virtual void Reset();
	virtual void GoNext();
	virtual bool IsEnd() { return pos == DataCount; };
	virtual TRecord GetCurr() { return pCurr->rec; };

};


#endif