#ifndef _T_SCAN_TABLE_H_
#define _T_SCAN_TABLE_H_

#include "TArrayTable.h"

class TScanTable :public TArrayTable
{
public:
	TScanTable(int size = 0) :TArrayTable(size) {};
	virtual ~TScanTable() {};

	virtual bool Find(TKey key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(TKey key);
};


#endif
