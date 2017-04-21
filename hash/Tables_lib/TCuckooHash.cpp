#include "TCuckooHash.h"

int TCuckooHash::HashFunc1(int key)
{
	return (coeff[0] * key*key*key + coeff[1] * key*key + coeff[2]*key + coeff[3]) % maxSize;
}

int TCuckooHash::HashFunc2(int key)
{
	return (coeff[4] * key*key*key + coeff[5] * key*key + coeff[6]*key + coeff[7]) % maxSize;
}

void TCuckooHash::GetHashFunc()
{
	for (int i = 0; i < 8; i++)
		coeff[i] = rand() % maxSize;
}

bool TCuckooHash::Find(int key)
{
	return false;
}

void TCuckooHash::InsRec(TRecord rec)
{
}

void TCuckooHash::DelRec(int key)
{
}
