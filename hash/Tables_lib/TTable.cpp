#include "TTable.h"

void TTable::Print()
{
	cout << "-----+------------" << endl;
	for (Reset(); !IsEnd(); GoNext())
	{
		cout << GetCurr();
	}
	cout << "-----+------------" << endl;
}