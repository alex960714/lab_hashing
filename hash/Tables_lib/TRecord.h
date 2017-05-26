#ifndef _T_RECORD_H_
#define _T_RECORD_H_

#define EMPTY_NODE -1
#define DELETED_NODE -2

#include <string.h>
#include <string>
#include <iostream>
using namespace std;

class TRecord
{
private:
	_int64 key;
	int val;

public:
	TRecord(_int64 _k = EMPTY_NODE, int _v = EMPTY_NODE) { key = _k; val = _v; };
	~TRecord() {};

	void SetKey(_int64 _k) { key = _k; };
	_int64 GetKey() { return key; };
	void SetValue(int _v) { val = _v; };
	int GetValue() { return val; };

	bool operator==(const TRecord &rec) { return this->key == rec.key; };
	bool operator<(const TRecord &rec) { return this->key < rec.key; };
	bool operator>(const TRecord &rec) { return this->key > rec.key; };

	TRecord& operator=(const TRecord &rec);

	friend istream& operator>>(istream &is, TRecord &rec);
	friend ostream& operator<<(ostream &os, const TRecord &rec);

};


#endif
