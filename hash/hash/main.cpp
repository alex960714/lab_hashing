#include <stdio.h>
#include "THashTable.h"
#include "TCuckooHash.h"
#include <iostream>
#include <locale.h>
#include <time.h>
#include <map>
#include <Windows.h>
#include "Hash.h"
using namespace std;

int main(int argc, char **argv)
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "Russian");
	int maxSize, step, el_num;
	int k;
	int op_num;
	int s_num, ins_num, del_num;
	int s_num2, ins_num2, del_num2;
	int s_num3, ins_num3, del_num3;
	double s_av, ins_av, del_av;
	double s_av2, ins_av2, del_av2;
	double s_av3, ins_av3, del_av3;
	int key;
	int val;
	TRecord rec;
	map<int, int> *stlTab=new map<int,int>();
	cout << "Введите максимальный размер таблицы:" << endl;
	cin >> maxSize;
	cout << "Введите шаг хэш-функции:" << endl;
	cin >> step;
	cout << "Введите число элементов в таблице:" << endl;
	cin >> el_num;
	THashTable *hash_open = new THashTable(maxSize, step);
	HashMap *hash_chain = new HashMap();
	TCuckooHash *hash_cuck = new TCuckooHash(maxSize);
	for (int i = 0; i < el_num; i++)
	{

		key = rand() % 10000;
		val = rand() % 10000;

		rec.SetKey(key);
		rec.SetValue(val);

		hash_open->InsRec(rec);
		hash_chain->put(key, val);
		hash_cuck->InsRec(rec);

		stlTab->insert({ key,val });
	}
	cout << "Введите количество операций: " << endl;
	cin >> op_num;
	s_num = s_num2 = s_num3 = 0;
	ins_num = ins_num2 = ins_num3 = 0;
	del_num = del_num2 = del_num3 = 0;
	cout << "Число элементов в таблице c открытой адресацией: " << hash_open->GetDataCount() << endl;
	cout << "Число элементов в таблице с цепочками: " << hash_chain->dataCount << endl;
	cout << "Число элементов в таблице с кукушкой: " << hash_cuck->GetDataCount() << endl;
	cout << "Число элементов в map: " << stlTab->size() << endl;
	for (int i = 0; i < op_num; i++)
	{
		key = rand() % 10000;
		val = rand() % 10000;

		hash_open->ResetEff();
		hash_open->Find(key);
		s_num += hash_open->GetEff();

		hash_chain->effCount = 0;
		hash_chain->get(key);
		s_num2 += hash_chain->effCount;

		hash_cuck->ResetEff();
		hash_cuck->Find(key);
		s_num3 += hash_cuck->GetEff();

		stlTab->find(key);

		key = rand() % 10000;
		val = rand() % 10000;
		rec.SetKey(key);
		rec.SetValue(val);

		hash_open->ResetEff();
		hash_open->InsRec(rec);
		ins_num += hash_open->GetEff();

		hash_chain->effCount = 0;
		hash_chain->put(key, val);
		ins_num2 += hash_chain->effCount;

		hash_cuck->ResetEff();
		hash_cuck->InsRec(rec);
		ins_num3 += hash_cuck->GetEff();

		stlTab->insert({ key,val });

		key = rand() % 10000;
		val = rand() % 10000;

		hash_open->ResetEff();
		hash_open->DelRec(key);
		del_num += hash_open->GetEff();

		hash_chain->effCount = 0;
		hash_chain->remove(key);
		del_num2 += hash_chain->effCount;

		hash_cuck->ResetEff();
		hash_cuck->DelRec(key);
		del_num3 += hash_cuck->GetEff();

		stlTab->erase(key);
	}

	cout << endl << "Число элементов в таблице c открытой адресацией: " << hash_open->GetDataCount() << endl;
	cout << "Число элементов в таблице с цепочками: " << hash_chain->dataCount << endl;
	cout << "Число элементов в таблице с кукушкой: " << hash_cuck->GetDataCount() << endl;
	cout << "Число элементов в map: " << stlTab->size() << endl;

	s_av = (double)(s_num) / op_num;
	ins_av = (double)(ins_num) / op_num;
	del_av = (double)(del_num) / op_num;

	cout << endl << "Открытая адресация:" << endl;
	cout << "Поиск: " << s_av << endl;
	cout << "Вставка: " << ins_av << endl;
	cout << "Удаление: " << del_av << endl << endl;

	s_av2 = (double)(s_num2) / op_num;
	ins_av2 = (double)(ins_num2) / op_num;
	del_av2 = (double)(del_num2) / op_num;

	cout << "Метод цепочек:" << endl;
	cout << "Поиск: " << s_av2 << endl;
	cout << "Вставка: " << ins_av2 << endl;
	cout << "Удаление: " << del_av2 << endl << endl;

	s_av3 = (double)(s_num3) / op_num;
	ins_av3 = (double)(ins_num3) / op_num;
	del_av3 = (double)(del_num3) / op_num;

	cout << "Метод кукушки:" << endl;
	cout << "Поиск: " << s_av3 << endl;
	cout << "Вставка: " << ins_av3 << endl;
	cout << "Удаление: " << del_av3 << endl << endl;

	return 0;
}