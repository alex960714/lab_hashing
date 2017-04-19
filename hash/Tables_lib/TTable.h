#ifndef _T_TABLE_H_
#define _T_TABLE_H_

#include "TRecord.h"

class TTable
{
protected:
	int DataCount, Eff;

public:
	TTable() { DataCount = 0; Eff = 0; };
	virtual ~TTable() {};

	int GetDataCount() const { return DataCount; };
	int GetEff() const { return Eff; };
	void ResetEff() { Eff = 0; };

	bool IsEmpty() { return DataCount == 0; };
	virtual bool IsFull() = 0;

	virtual bool Find(TKey key) = 0;
	virtual void DelRec(TKey key) = 0;
	virtual void InsRec(TRecord rec) = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	virtual TRecord GetCurr() = 0;
	void Print();
};

	

#endif


