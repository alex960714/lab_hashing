#pragma once
#include <stdlib.h>
#include <math.h>
using namespace std;

class LinkedHashEntry {
private:
	int key;
	int value;
	LinkedHashEntry *next;
public:
	LinkedHashEntry(int key, int value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}

	int getKey() {
		return key;
	}

	int getValue() {
		return value;
	}

	void setValue(int value) {
		this->value = value;
	}

	LinkedHashEntry *getNext() {
		return next;
	} 


	void setNext(LinkedHashEntry *next) {
		this->next = next;
	}
};





const int TABLE_SIZE = 1280;

class HashMap {
private:
	LinkedHashEntry **table;
	int curr;
	int coeff1, coeff2;

	int HashFunc(int key)
	{
		/*int k = 1, R = 0;
		for (int i = 0; i < key.length(); i++)
		{
		R += key[i] * k;
		k *= 2;
		}*/
		return (coeff1 * key + coeff2) % TABLE_SIZE;
	}

	void GetHashFunc()
	{
		coeff1 = rand() % TABLE_SIZE;
		coeff2 = rand() % TABLE_SIZE;
	}

	/*void Reset() {
		LinkedHashEntry **begin = **table;
		curr = 0;
		while (*begin == NULL) {
			curr++;
			*begin->getNext();
		}
	}*/

	/*bool IsEnd() {
		return (curr == TABLE_SIZE);
	}*/

	void CreateNewTable()
	{
		LinkedHashEntry *curr_rec, *new_rec;
		GetHashFunc();
		int i = 0;
		while (table[i++] == NULL)
		{}
		new_rec = table[i];
		for (; i < TABLE_SIZE;i++)
		{
			curr_rec->setNext(table[i]);
			while (curr_rec->getNext() != NULL)
			{
				curr_rec = curr_rec->getNext();
			}
		}

		for (i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
		//pRec = new TRecord[maxSize];
		/*for (int i = 0; i < maxSize; i++)
		{
		pRec[i].SetKey(EMPTY_NODE);
		pRec[i].SetValue(EMPTY_NODE);
		}*/
		//Перенести заново в таблицу
		curr_rec = new_rec;
		while (curr_rec != NULL)
		{
			put(curr_rec->getKey(), curr_rec->getValue());
			new_rec = curr_rec;
			curr_rec = curr_rec->getNext();
			delete new_rec;
		}
	}

public:
	int effCount;
	HashMap() {
		effCount = 0;
		table = new LinkedHashEntry*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	}

	int get(int key) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] == NULL) {
			effCount++;
			return -1;
		}
		else {
			LinkedHashEntry *entry = table[hash];
			while (entry != NULL && entry->getKey() != key) {
				effCount++;
				entry = entry->getNext();
			}
			if (entry == NULL)
				return -1;
			else
				effCount++;
			return entry->getValue();
		}
	}

	void put(int key, int value) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] == NULL)
			table[hash] = new LinkedHashEntry(key, value);
		else {
			LinkedHashEntry *entry = table[hash];
			int count = 0;
			while (entry->getNext() != NULL) {
				count++;
				entry = entry->getNext();
			}
			if (count > log(TABLE_SIZE))
			if (entry->getKey() == key)
				entry->setValue(value);
			else
				entry->setNext(new LinkedHashEntry(key, value));
		}
	}

	void remove(int key) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] != NULL) {
			LinkedHashEntry *prevEntry = NULL;
			LinkedHashEntry *entry = table[hash];
			while (entry->getNext() != NULL && entry->getKey() != key) {
				prevEntry = entry;
				entry = entry->getNext();
			}
			if (entry->getKey() == key) {
				if (prevEntry == NULL) {
					LinkedHashEntry *nextEntry = entry->getNext();
					delete entry;
					table[hash] = nextEntry;
				}
				else {
					LinkedHashEntry *next = entry->getNext();
					delete entry;
					prevEntry->setNext(next);
				}
			}
		}
	}

	~HashMap() {
		for (int i = 0; i < TABLE_SIZE; i++)
			if (table[i] != NULL) {
				LinkedHashEntry *prevEntry = NULL;
				LinkedHashEntry *entry = table[i];
				while (entry != NULL) {
					prevEntry = entry;
					entry = entry->getNext();
					delete prevEntry;
				}
			}
		delete[] table;
	}
};