#include "TTreeTable.h"

bool TTreeTable::Find(TKey key)
{
	pCurr = pRoot;
	pRef = &pRoot;
	while (pCurr != NULL)
	{
		Eff++;
		if (pCurr->rec.GetKey() == key)
			return true;
		if (pCurr->rec.GetKey() < key)
			pRef = &(pCurr->pRight);
		else
			pRef = &(pCurr->pLeft);
		pCurr = *pRef;
	}
	return false;
}

void TTreeTable::InsRec(TRecord rec)
{
	if (!Find(rec.GetKey()))
	{
		TTreeNode *tmp = new TTreeNode(rec);
		*pRef = tmp;
		DataCount++;
	}
	else
	{
		cout << "Данная запись уже есть в таблице" << endl;
	}
}

void TTreeTable::DelRec(TKey key)
{
	if (!Find(key))
	{
		cout << "Данной записи нет в таблице" << endl;
		return;
	}
	TTreeNode *p = *pRef;
	if ((*pRef)->pLeft != NULL || (*pRef)->pRight != NULL)
	{
		if ((*pRef)->pLeft == NULL)
			*pRef = (*pRef)->pRight;
		else if ((*pRef)->pRight == NULL)
			*pRef = (*pRef)->pLeft;
		else
		{
			TTreeNode **tmp = &((*pRef)->pLeft);
			(*pRef)->rec = (*tmp)->rec;
			p = *tmp;
			while ((*tmp)->pRight != NULL)
			{
				tmp = &((*tmp)->pRight);
				Eff++;
				(*pRef)->rec = (*tmp)->rec;
				p = *tmp;
			}
			*tmp = (*tmp)->pLeft;
		}
	}
	else
		*pRef = NULL;
	delete p;
	DataCount--;
}

void TTreeTable::Reset()
{
	pCurr = pRoot;
	st.Clear();
	pos = 0;
	while (pCurr != NULL)
	{
		st.Push(pCurr);
		pCurr = pCurr->pLeft;
	}
	pCurr = st.Pop();
}

void TTreeTable::GoNext()
{
	if (pCurr != NULL)
	{
		pos++;
		pCurr = pCurr->pRight;
		while (pCurr != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		if (!st.IsEmpty())
			pCurr = st.Pop();
	}
}