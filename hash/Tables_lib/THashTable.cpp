#include "THashTable.h"

int THashTable::HashFunc(TKey key)
{
	int k = 1, R = 0;
	for (int i = 0; i < key.length(); i++)
	{
		R += key[i] * k;
		k *= 2;
	}
	return (coeff1 * R + coeff2) % maxSize;
}

void THashTable::GetHashFunc()
{
	coeff1 = rand() % maxSize;
	coeff2 = rand() % maxSize;
}

void THashTable::CreateNewTable()
{
	TRecord *new_rec = new TRecord[DataCount];
	GetHashFunc();
	int i = 0;
	for (Reset(); !IsEnd(); GoNext())
	{
		new_rec[i++] = pRec[curr];
	}

	delete[] pRec;
	pRec = new TRecord[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		pRec[i].SetKey("");
		pRec[i].SetValue("");
	}

	for (int j = 0; j < DataCount; j++)
	{
		InsRec(new_rec[j]);
	}
	delete[] new_rec;
}

THashTable::THashTable(int _size, int _step)
{
	maxSize = _size;
	step = _step;
	pRec = new TRecord[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		pRec[i].SetKey("");
		pRec[i].SetValue("");
	}
	GetHashFunc();
	curr = -1;
	DataCount = 0;
	Eff = 0;
}

bool THashTable::Find(TKey key)
{
	curr = HashFunc(key);
	free = -1;
	int op = 0;
	while(true)
	{
		Eff++;
		if (op > log(maxSize))
		{
			CreateNewTable();
		}
		if (pRec[curr].GetKey() == key)
			return true;
		if (pRec[curr].GetKey() == "&" && free == -1)
			free = curr;
		if (pRec[curr].GetKey() != "")
		{
			curr = (step + curr) % maxSize;
		}
		else break;
	}
	if (free != -1)
		curr = free;
	return false;
}

void THashTable::InsRec(TRecord rec)
{
	if (IsFull()) return;
	if (!Find(rec.GetKey()))
	{
		pRec[curr] = rec;
		DataCount++;
	}
	/*else
	{
		cout << "Данная запись уже есть в таблице" << endl;
	}*/
}

void THashTable::DelRec(TKey key)
{
	if (IsEmpty()) return;
	if (Find(key))
	{
		pRec[curr].SetKey("&");
		DataCount--;
	}
	/*else
	{
		cout << "Данной записи нет в таблице" << endl;
	}*/
}

void THashTable::Reset()
{
	curr = 0;
	while (curr < maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
		curr++;
}

void THashTable::GoNext()
{
	curr++;
	while (curr<maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
		curr++;
}

