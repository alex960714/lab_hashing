#ifndef _T_ARRAY_TABLE_H_
#define _T_ARRAY_TABLE_H_

#include "TTable.h"

class TArrayTable :public TTable
{
protected:
	TRecord *pRec;
	int curr, maxSize;

public:
	TArrayTable(int size);
	virtual ~TArrayTable() {};

	virtual bool IsFull() { return maxSize == DataCount; };
	virtual TRecord GetCurr() { return pRec[curr]; };
	virtual void Reset() { curr = 0; }
	virtual void GoNext() { curr++; }
	virtual bool IsEnd() { return curr == DataCount; };

	int GetMaxSize() const { return maxSize; };
};


#endif
