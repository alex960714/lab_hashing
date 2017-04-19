#ifndef _T_SORT_TABLE_H_
#define _T_SORT_TABLE_H_

#include "TArrayTable.h"
#include "TScanTable.h"

class TSortTable :public TArrayTable
{
private:
	void SortInsert();
	void SortHoar(int start, int end, TKey mid);

public:
	TSortTable(int size = 0) :TArrayTable(size) {};
	TSortTable(TScanTable &sc_tab);
	virtual ~TSortTable() {};

	virtual bool Find(TKey key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(TKey key);

};


#endif