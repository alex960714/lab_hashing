#ifndef _T_RECORD_H_
#define _T_RECORD_H_

#include <string.h>
#include <string>
#include <iostream>
using namespace std;

typedef string TKey;
typedef string TValue;

class TRecord
{
private:
	TKey key;
	TValue val;

public:
	TRecord(TKey _k = "", TValue _v = "") { key = _k; val = _v; };
	~TRecord() {};

	void SetKey(TKey _k) { key = _k; };
	TKey GetKey() { return key; };
	void SetValue(TValue _v) { val = _v; };
	TValue GetValue() { return val; };

	bool operator==(const TRecord &rec) { return this->key == rec.key; };
	bool operator<(const TRecord &rec) { return this->key < rec.key; };
	bool operator>(const TRecord &rec) { return this->key > rec.key; };

	TRecord& operator=(const TRecord &rec);

	friend istream& operator>>(istream &is, TRecord &rec);
	friend ostream& operator<<(ostream &os, const TRecord &rec);

};


#endif
