#include "TCuckooHash.h"

int TCuckooHash::HashFunc1(int key)
{
	return (coeff[0] * ((((key*key) % maxSize) * key) % maxSize) + coeff[1] * ((key*key) % maxSize) + coeff[2]*key + coeff[3]) % maxSize;
}

int TCuckooHash::HashFunc2(int key)
{
	return (coeff[4] * ((((key*key) % maxSize) * key) % maxSize) + coeff[5] * ((key*key) % maxSize) + coeff[6]*key + coeff[7]) % maxSize;
}

void TCuckooHash::GetHashFunc()
{
	for (int i = 0; i < 8; i++)
		coeff[i] = rand() % (maxSize - 1) + 1;
}

bool TCuckooHash::FindEmpty(int hash_last, int hash_curr, int iter)
{
	int hash_next = HashFunc2(pRec[hash_curr].GetKey());
	if (hash_next == hash_curr)
		hash_next = HashFunc1(pRec[hash_curr].GetKey());
	Eff++;

	if (pRec[hash_curr].GetKey() == EMPTY_NODE || pRec[hash_curr].GetKey() == DELETED_NODE || 
		(iter < log(maxSize) && FindEmpty(hash_curr, hash_next, ++iter)))
	{
		pRec[hash_curr].SetKey(pRec[hash_last].GetKey());
		pRec[hash_curr].SetValue(pRec[hash_last].GetValue());
		curr = hash_last;
		return true;
	}
	
	return false;
}

bool TCuckooHash::Find(int key)
{
	int val1 = HashFunc1(key), val2 = HashFunc2(key);
	Eff++;
	if (pRec[val1].GetKey() == key)
	{
		curr = val1;
		return true;
	}
	Eff++;
	if (pRec[val2].GetKey() == key)
	{
		curr = val2;
		return true;
	}

	return false;
}

void TCuckooHash::InsRec(TRecord rec)
{
	if (IsFull()) return;
	if (!Find(rec.GetKey()))
	{
		int val1 = HashFunc1(rec.GetKey()), val2 = HashFunc2(rec.GetKey());
		int free = -1;

		if (pRec[val1].GetKey() == EMPTY_NODE || pRec[val1].GetKey() == DELETED_NODE)
			free = val1;
		else if (pRec[val2].GetKey() == EMPTY_NODE || pRec[val2].GetKey() == DELETED_NODE)
			free = val2;
		if (free != -1)
		{
			curr = free;
			pRec[curr] = rec;
			DataCount++;
			return;
		}

		int hash_next1 = HashFunc2(pRec[val1].GetKey());
		if (hash_next1 == val1)
			hash_next1 = HashFunc1(pRec[val1].GetKey());

		int hash_next2 = HashFunc2(pRec[val2].GetKey());
		if (hash_next2 == val2)
			hash_next2 = HashFunc1(pRec[val2].GetKey());

		if (!FindEmpty(val1, hash_next1, 0) && !FindEmpty(val2, hash_next2, 0))
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
