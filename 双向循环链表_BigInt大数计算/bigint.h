#pragma once
#include <iostream>
#include "dlist.h"
class bigint
{
private:
	dlist mydlist;
	int len;
public:
	bigint()
		:len(0),mydlist(){}

	bigint(const bigint& b)
		: len(b.len), mydlist(b.mydlist){}
	~bigint(){}
	bigint& operator=(const bigint& b);

	dlist& getdlist() { return mydlist; }
	dlist getdlist() const { return mydlist; }
	int getlen() { return len; }
	int getlen() const { return len; }

	bool operator!=(bigint& d) { return !((*this) == d); }
	bool operator==(bigint& d);
	bool operator>=(bigint& d);
	bool operator<(bigint& d) { return !((*this) >= d); }
	bool operator<=(bigint& d); 
	bool operator>(bigint& d) { return !((*this) <= d); }

	bigint operator+(bigint& d);
	void operator+=(bigint& d);
	bigint operator++(int);//后++
	bigint& operator++();//前++

	bigint operator-(bigint& d);
	void operator-=(bigint& d);
	bigint operator--(int);//后--
	bigint& operator--();//前--

	bigint operator*(bigint& d);
	void operator*=(bigint& d);

	bigint operator/(bigint& d);
	void operator/=(bigint& d);

	bigint pow(bigint& d);

	friend istream& operator>>(istream& is, bigint& d);
	friend ostream& operator<<(ostream& os, const bigint& d);
};

int getint(string& s, int pos, int len);
bigint max(const bigint& a, const bigint& b);
bigint min(const bigint& a, const bigint& b);

