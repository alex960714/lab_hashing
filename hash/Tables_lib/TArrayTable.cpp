#include "TArrayTable.h"

TArrayTable::TArrayTable(int size)
{
	maxSize = size;
	pRec = new TRecord[maxSize];
	curr = -1;
	DataCount = 0;
	Eff = 0;
}