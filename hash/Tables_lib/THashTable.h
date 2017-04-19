#ifndef _T_HASH_TABLE_H_
#define _T_HASH_TABLE_H_

#define EMPTY_NODE -1
#define DELETED_NODE -2

#include "TTable.h"
#include <math.h>

class THashTable :public TTable
{
protected:
	int HashFunc(int key);
	void GetHashFunc();
	void CreateNewTable();

	int maxSize, curr, step, free;
	int coeff1, coeff2, prime;
	TRecord *pRec;

public:
	THashTable(int _size = 0, int _step = 0);
	virtual ~THashTable() { delete[] pRec; pRec = NULL; };

	virtual bool IsFull() { return maxSize == DataCount; };
	virtual bool Find(int key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(int key);

	virtual void Reset();
	virtual void GoNext();
	virtual bool IsEnd() { return curr == maxSize; };
	virtual TRecord GetCurr() { return pRec[curr]; };
};


#endif
