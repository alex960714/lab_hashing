#include <stdio.h>
#include "THashTable.h"
#include "TCuckooHash.h"
#include <iostream>
#include <fstream>
#include <locale.h>
#include <time.h>
#include <map>
#include <Windows.h>
#include "Hash.h"
#include <omp.h>
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
	double s_time, ins_time, del_time;
	double s_time2, ins_time2, del_time2;
	double s_time3, ins_time3, del_time3;
	double s_time_map, ins_time_map, del_time_map;
	_int64 key;
	int val;
	ifstream ifs;
	ofstream ofs;
	TRecord rec;
	map<int, int> *stlTab = new map<int, int>();
	cout << "Введите максимальный размер таблицы:" << endl;
	cin >> maxSize;
	cout << "Введите шаг хэш-функции:" << endl;
	cin >> step;
	cout << "Введите число элементов в таблице:" << endl;
	cin >> el_num;
	THashTable *hash_open = new THashTable(maxSize, step);
	HashMap *hash_chain = new HashMap();
	TCuckooHash *hash_cuck = new TCuckooHash(maxSize);
	int prime = hash_open->PrimeCalc();
	for (int i = 0; i < el_num; i++)
	{

		key = (rand() * rand()) % prime;
		val = (rand() * rand()) % prime;

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
	s_time = s_time2 = s_time3 = s_time_map = 0;
	ins_time = ins_time2 = ins_time3 = ins_time_map = 0;
	del_time = del_time2 = del_time3 = del_time_map = 0;
	cout << "Изначальное число элементов в таблицах: " << hash_open->GetDataCount() << endl;
	ofs.open("values.txt");
	for (int i = 0; i < 4 * op_num; i++)
	{
		ofs << (rand() * rand()) % prime << " ";
	}
	ofs.close();

	double st_time;
	ifs.open("values.txt");
	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //open find
	{
		ifs >> key;
		hash_open->ResetEff();
		hash_open->Find(key);
		s_num += hash_open->GetEff();
	}
	s_time = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //open insert
	{
		ifs >> key >> val;
		rec.SetKey(key);
		rec.SetValue(val);
		hash_open->ResetEff();
		hash_open->InsRec(rec);
		ins_num += hash_open->GetEff();
	}
	ins_time = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //open remove
	{
		ifs >> key;
		hash_open->ResetEff();
		hash_open->DelRec(key);
		del_num += hash_open->GetEff();
	}
	del_time = omp_get_wtime() - st_time;
	ifs.close();

	ifs.open("values.txt");
	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //chain find
	{
		ifs >> key;
		hash_chain->effCount = 0;
		hash_chain->get(key);
		s_num2 += hash_chain->effCount;
	}
	s_time2 = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //chain insert
	{
		ifs >> key >> val;
		rec.SetKey(key);
		rec.SetValue(val);
		hash_chain->effCount = 0;
		hash_chain->put(key, val);
		ins_num2 += hash_chain->effCount;
	}
	ins_time2 = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //chain remove
	{
		ifs >> key;
		hash_chain->effCount = 0;
		hash_chain->remove(key);
		del_num2 += hash_chain->effCount;
	}
	del_time2 = omp_get_wtime() - st_time;
	ifs.close();

	ifs.open("values.txt");
	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //cuckoo find
	{
		ifs >> key;
		hash_cuck->ResetEff();
		hash_cuck->Find(key);
		s_num3 += hash_cuck->GetEff();
	}
	s_time3 = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //cuckoo insert
	{
		ifs >> key >> val;
		rec.SetKey(key);
		rec.SetValue(val);
		hash_cuck->ResetEff();
		hash_cuck->InsRec(rec);
		ins_num3 += hash_cuck->GetEff();
	}
	ins_time3 = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //cuckoo remove
	{
		ifs >> key;
		hash_cuck->ResetEff();
		hash_cuck->DelRec(key);
		del_num3 += hash_cuck->GetEff();
	}
	del_time3 = omp_get_wtime() - st_time;
	ifs.close();

	ifs.open("values.txt");
	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //map find
	{
		ifs >> key;
		stlTab->find(key);
	}
	s_time_map = omp_get_wtime() - st_time;

	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //map insert
	{
		ifs >> key >> val;
		stlTab->insert({ key,val });
	}
	ins_time_map = omp_get_wtime() - st_time;
	
	st_time = omp_get_wtime();
	for (int i = 0; i < op_num; i++)  //map remove
	{
		ifs >> key;
		stlTab->erase(key);
	}
	del_time_map = omp_get_wtime() - st_time;
	ifs.close();

	cout << endl << "Число элементов в таблицах после выполнения операций: " << hash_open->GetDataCount() << endl;
	cout << "Число коллизий в открытой адресации: " << hash_open->GetCollisionNum() << endl;
	cout << "Число пересозданий таблицы в открытой адресации: " << hash_open->GetCreateNum() << endl;
	cout << "Число коллизий в кукушке: " << hash_cuck->GetCollisionNum() << endl;
	cout << "Число пересозданий таблицы в кукушке: " << hash_cuck->GetCreateNum() << endl;

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

	cout << endl << "Время работы:" << endl;
	cout << endl << "Открытая адресация:" << endl;
	cout << "Поиск:" << s_time << endl;
	cout << "Вставка:" << ins_time << endl;
	cout << "Удаление:" << del_time << endl;

	cout << endl << "Цепочки:" << endl;
	cout << "Поиск:" << s_time2 << endl;
	cout << "Вставка:" << ins_time2 << endl;
	cout << "Удаление:" << del_time2 << endl;

	cout << endl << "Кукушка:" << endl;
	cout << "Поиск:" << s_time3 << endl;
	cout << "Вставка:" << ins_time3 << endl;
	cout << "Удаление:" << del_time3 << endl;

	cout << endl << "Map:" << endl;
	cout << "Поиск:" << s_time_map << endl;
	cout << "Вставка:" << ins_time_map << endl;
	cout << "Удаление:" << del_time_map << endl;
	return 0;
}