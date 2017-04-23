#include <stdio.h>
#include "THashTable.h"
#include "TCuckooHash.h"
#include <iostream>
#include <locale.h>
#include <time.h>
using namespace std;

int main(int argc, char **argv)
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "Russian");
	int maxSize, step, el_num;
	int k;
	int op_num, s_num, ins_num, del_num;
	double s_av, ins_av, del_av;
	int key;
	int val;
	TRecord rec;
	cout << "¬ведите максимальный размер таблицы:" << endl;
	cin >> maxSize;
	cout << "¬ведите шаг хэш-функции:" << endl;
	cin >> step;
	cout << "¬ведите число элементов в таблице:" << endl;
	cin >> el_num;
	THashTable *hash = new TCuckooHash(maxSize, step);
	for (int i = 0; i < el_num; i++)
	{

		key = rand() % 10000;
		val = rand() % 10000;

		rec.SetKey(key);
		rec.SetValue(val);
		hash->InsRec(rec);
	}
	cout << "¬ведите количество операций: " << endl;
	cin >> op_num;
	s_num = 0;
	ins_num = 0;
	del_num = 0;
	cout << "„исло элементов в таблице: " << hash->GetDataCount() << endl;
	for (int i = 0; i < op_num; i++)
	{
		key = rand() % 10000;
		val = rand() % 10000;

		hash->ResetEff();
		hash->Find(key);
		s_num += hash->GetEff();

		rec.SetKey(rand() % 10000);
		rec.SetValue(rand() % 10000);

		hash->ResetEff();
		hash->InsRec(rec);
		ins_num += hash->GetEff();

		key = rand() % 10000;
		val = rand() % 10000;

		hash->ResetEff();
		hash->DelRec(key);
		del_num += hash->GetEff();
	}
	s_av = (double)(s_num) / op_num;
	ins_av = (double)(ins_num) / op_num;
	del_av = (double)(del_num) / op_num;
	cout << "—редн€€ эффективность поиска: " << s_av << endl;
	cout << "—редн€€ эффективность вставки: " << ins_av << endl;
	cout << "—редн€€ эффективность удалени€: " << del_av << endl;


	return 0;
}