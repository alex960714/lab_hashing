#include "THashTable.h"

int THashTable::HashFunc(_int64 key)
{
	/*int k = 1, R = 0;
	for (int i = 0; i < key.length(); i++)
	{
		R += key[i] * k;
		k *= 2;
	}*/
	return ((coeff1 * key + coeff2) % prime) % maxSize;
}

void THashTable::GetHashFunc()
{
	coeff1 = rand() % (prime - 1) + 1;
	coeff2 = rand() % prime;
}

void THashTable::CreateNewTable()
{
	create_num++;
	TRecord *new_rec = new TRecord[DataCount];
	int i = 0;
	for (Reset(); !IsEnd(); GoNext())
	{
		new_rec[i++] = pRec[curr];
	}

	delete[] pRec;
	/*if (DataCount > 0.75*maxSize)
		maxSize *= 1.5;*/
	pRec = new TRecord[maxSize];
	/*for (int i = 0; i < maxSize; i++)
	{
		pRec[i].SetKey(EMPTY_NODE);
		pRec[i].SetValue(EMPTY_NODE);
	}*/

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
	int curr_num = 7000001;
	/*bool fl = false;
	while (!fl)
	{
		curr_num++;
		for (int d = 2; d*d <= curr_num; d++)
		{
			if (curr_num % d == 0)
			{
				fl = false;
				break;
			}
		}
	}
	prime = curr_num;*/
	return curr_num;
}

THashTable::THashTable(int _size, int _step)
{
	maxSize = _size;
	step = _step;
	pRec = new TRecord[maxSize];
	/*for (int i = 0; i < maxSize; i++)
	{
		pRec[i].SetKey(EMPTY_NODE);
		pRec[i].SetValue(EMPTY_NODE);
	}*/
	//PrimeCalc();
	prime = 7000001;
	GetHashFunc();
	curr = -1;
	DataCount = 0;
	Eff = 0;
	col_num = 0;
	create_num = 0;
}

bool THashTable::Find(_int64 key)
{
	curr = HashFunc(key);
	free = -1;
	int op = 0;
	while(true)
	{
		Eff++;
		/*if (op > log(maxSize))
		{
			CreateNewTable();
		}*/
		if (pRec[curr].GetKey() == key)
			return true;
		if (pRec[curr].GetKey() == DELETED_NODE && free == -1)
			free = curr;
		if (pRec[curr].GetKey() != EMPTY_NODE)
		{
			col_num++;
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
	//cout << rec.GetKey() << " | " << rec.GetValue() << endl;
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
	/*else
	{
		cout << "Данная запись уже есть в таблице" << endl;
	}*/
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
	/*else
	{
		cout << "Данной записи нет в таблице" << endl;
	}*/
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

