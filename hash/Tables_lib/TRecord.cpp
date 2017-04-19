#include "TRecord.h"

TRecord& TRecord::operator=(const TRecord &rec)
{
	this->key = rec.key;
	this->val = rec.val;
	return *this;
}


istream& operator>>(istream &is, TRecord &rec)
{
	string _key, _val;
	is >> _key;
	is >> _val;
	rec.key = _key;
	rec.val = _val;
	return is;
}

ostream& operator<<(ostream &os, const TRecord &rec)
{
	string _key = rec.key;
	string _val = rec.val;
	os << " " << _key << " | " << _val << " " << endl;
	return os;
}