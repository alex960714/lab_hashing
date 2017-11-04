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





class HashMap {
private:
	LinkedHashEntry **table;
	int curr;
	_int64 coeff1, coeff2, prime;
	int prime_arr[5] = { 7000003, 15485867, 49979687, 32452867, 32452843 };
	int TABLE_SIZE;

	int HashFunc(_int64 key)
	{
		return ((coeff1 * key + coeff2) % prime_arr[prime]) % TABLE_SIZE;
	}

	void GetHashFunc()
	{
		coeff1 = rand() % (prime_arr[prime] - 1) + 1;
		coeff2 = rand() % prime_arr[prime];
	}

	void CreateNewTable()
	{
		LinkedHashEntry *curr_rec, *new_rec = *table;
		prime = ++prime % 5;
		GetHashFunc();
		dataCount = 0;
		int i = -1;
		while (table[++i] == NULL)
		{
		}
		curr_rec = table[i];
		while (i < TABLE_SIZE - 1)
		{
			while (curr_rec->getNext() != NULL)
			{
				curr_rec = curr_rec->getNext();
			}
			curr_rec->setNext(table[++i]);
		}

		for (i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
		curr_rec = new_rec;
		while (curr_rec != NULL) {
			put(curr_rec->getKey(), curr_rec->getValue());
			new_rec = curr_rec;
			curr_rec = curr_rec->getNext();
			delete new_rec;
			}
	}

public:
	int effCount;
	int dataCount;
	HashMap(int size = 1000) {
		effCount = 0;
		dataCount = 0;
		TABLE_SIZE = size;
		prime = 0;
		table = new LinkedHashEntry*[TABLE_SIZE];
		GetHashFunc();
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	}

	int get(_int64 key) {
		int hash = HashFunc(key);
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

	void put(_int64 key, int value) {
		//cout << key << " | " << value << endl;
		int hash = HashFunc(key);
		effCount++;
		if (table[hash] == NULL) {
			table[hash] = new LinkedHashEntry(key, value);
			dataCount++;
		}
		else {
			LinkedHashEntry *entry = table[hash];
			int count = 0;
			while (entry->getKey() != key && entry->getNext() != NULL) {
				count++;
				entry = entry->getNext();
			}
			effCount += count;
			if (count > log(TABLE_SIZE)) {
				CreateNewTable();
				put(key, value);
			}
			else {
				if (entry->getKey() == key)
					entry->setValue(value);
				else
				{
					entry->setNext(new LinkedHashEntry(key, value));
					dataCount++;
				}
			}
			
		}
	}

	void PrintMap() {
		LinkedHashEntry *curr = *table;
		cout << "Key" << " | " << "Value" << endl<< endl;
		for (int i = 0; i < TABLE_SIZE; i++) {
			curr = table[i];
			while (curr != NULL) {
				cout << curr->getKey() << " | ";
				cout << curr->getValue() << endl;
				curr = curr->getNext();
			}
		}
	}

	void remove(_int64 key) {
		int hash = HashFunc(key);
		effCount++;
		if (table[hash] != NULL) {
			LinkedHashEntry *prevEntry = NULL;
			LinkedHashEntry *entry = table[hash];
			while (entry->getNext() != NULL && entry->getKey() != key) {
				prevEntry = entry;
				entry = entry->getNext();
				effCount++;
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
				dataCount--;
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