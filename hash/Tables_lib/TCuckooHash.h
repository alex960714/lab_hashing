#ifndef _T_CUCKOO_HASH_H_
#define _T_CUCKOO_HASH_H_

#include "THashTable.h"

class TCuckooHash :public THashTable 
{
protected:
	virtual int HashFunc1(_int64 key);
	virtual int HashFunc2(_int64 key);
	virtual void GetHashFunc();
	bool FindEmpty(int hash_last, int hash_curr, int iter);

	int coeff[4];
public:
	TCuckooHash(int _size = 0, int _step = 0) :THashTable(_size, _step) { GetHashFunc(); };
	virtual ~TCuckooHash() {};

	virtual bool Find(_int64 key);
	virtual void InsRec(TRecord rec);
};

#endif
