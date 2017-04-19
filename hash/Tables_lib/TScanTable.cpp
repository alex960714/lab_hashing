#include "TScanTable.h"

bool TScanTable::Find(TKey key)
{
	for (Reset(); !IsEnd(); GoNext())
	{
		Eff++;
		if (pRec[curr].GetKey() == key)
			return true;
	}
	return false;
}

void TScanTable::InsRec(TRecord rec)
{
	if (IsFull()) return;
	if (!Find(rec.GetKey()))
	{
		pRec[curr] = rec;
		DataCount++;
		Eff++;
	}
	else
	{
		cout << "Данная запись уже есть в таблице" << endl;
	}
}

void TScanTable::DelRec(TKey key)
{
	if (IsEmpty()) return;
	if (Find(key))
	{
		pRec[curr] = pRec[DataCount - 1];
		DataCount--;
		Eff++;
	}
	else
	{
		cout << "Данной записи нет в таблице" << endl;
	}
}