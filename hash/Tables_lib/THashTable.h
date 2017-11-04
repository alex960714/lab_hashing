#ifndef _T_HASH_TABLE_H_
#define _T_HASH_TABLE_H_


#include "TTable.h"
#include <math.h>

class THashTable :public TTable
{
protected:
	virtual int HashFunc(_int64 key);
	virtual void GetHashFunc();
	void CreateNewTable();
	
	int maxSize, curr, step, free;
	_int64 coeff1, coeff2, prime;
	TRecord *pRec;
	int prime_arr[5] = {7000003, 15485867, 49979687, 32452867, 32452843};

public:
	THashTable(int _size = 0, int _step = 0);
	virtual ~THashTable() { delete[] pRec; pRec = NULL; };

	virtual bool IsFull() { return maxSize == DataCount; };
	virtual bool Find(_int64 key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(_int64 key);

	virtual void Reset();
	virtual void GoNext();
	virtual bool IsEnd() { return curr == maxSize; };
	virtual TRecord GetCurr() { return pRec[curr]; };
	long int PrimeCalc();
};


#endif
