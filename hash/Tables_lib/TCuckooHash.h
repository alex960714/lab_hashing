#ifndef _T_CUCKOO_HASH_H_
#define _T_CUCKOO_HASH_H_

#include "THashTable.h"

class TCuckooHash :public THashTable 
{
protected:
	virtual int HashFunc(int key);
	virtual void GetHashFunc();

public:
	TCuckooHash(int _size = 0, int _step = 0) :THashTable(_size, _step) {};
	virtual ~TCuckooHash() {};

	virtual bool Find(int key);
	virtual void InsRec(TRecord rec);
	virtual void DelRec(int key);
};

#endif
