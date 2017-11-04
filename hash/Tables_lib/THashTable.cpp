#include "THashTable.h"

int THashTable::HashFunc(_int64 key)
{
	return ((coeff1 * key + coeff2) % prime_arr[prime]) % maxSize;
}

void THashTable::GetHashFunc()
{
	coeff1 = rand() % (prime_arr[prime] - 1) + 1;
	coeff2 = rand() % prime_arr[prime];
}

void THashTable::CreateNewTable()
{
	TRecord *new_rec = new TRecord[DataCount];
	int i = 0;
	for (Reset(); !IsEnd(); GoNext())
	{
		new_rec[i++] = pRec[curr];
	}

	delete[] pRec;
	pRec = new TRecord[maxSize];
	prime = ++prime % 5;
	GetHashFunc();
	int dc = DataCount;
	DataCount = 0;
	for (int j = 0; j < dc; j++)
	{
		InsRec(new_rec[j]);
	}
	delete[] new_rec;
}

long int THashTable::PrimeCalc()
{
	return prime_arr[prime];
}

THashTable::THashTable(int _size, int _step)
{
	maxSize = _size;
	step = _step;
	pRec = new TRecord[maxSize];
	prime = 0;
	GetHashFunc();
	curr = -1;
	DataCount = 0;
	Eff = 0;
}

bool THashTable::Find(_int64 key)
{
	curr = HashFunc(key);
	free = -1;
	int op = 0;
	while(true)
	{
		Eff++;
		if (pRec[curr].GetKey() == key)
			return true;
		if (pRec[curr].GetKey() == DELETED_NODE && free == -1)
			free = curr;
		if (pRec[curr].GetKey() != EMPTY_NODE)
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
	int eff1 = Eff;
	if (!Find(rec.GetKey()))
	{
		int eff2 = Eff;
		if (eff2 - eff1 > log(maxSize))
		{
			CreateNewTable();
			InsRec(rec);
		}
		else
		{
			pRec[curr] = rec;
			DataCount++;
		}
	}
}

void THashTable::DelRec(_int64 key)
{
	if (IsEmpty()) return;
	int eff1 = Eff;
	if (Find(key))
	{
		int eff2 = Eff;
		pRec[curr].SetKey(DELETED_NODE);
		DataCount--;
		if (eff2 - eff1 > log(maxSize))
		{
			CreateNewTable();
		}
	}
}

void THashTable::Reset()
{
	curr = 0;
	while (curr < maxSize && (pRec[curr].GetKey() == DELETED_NODE || pRec[curr].GetKey() == EMPTY_NODE))
		curr++;
}

void THashTable::GoNext()
{
	curr++;
	while (curr<maxSize && (pRec[curr].GetKey() == DELETED_NODE || pRec[curr].GetKey() == EMPTY_NODE))
		curr++;
}

