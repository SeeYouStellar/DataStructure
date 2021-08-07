#pragma once
#include <iostream>
#include "linked_list.h"
using namespace std;

class bigNum
{
private:
	linked_list list;
	int type;
public:

	bigNum()
		:list(), type(10) {}
	~bigNum(){}
	linked_list& getlist() { return list; }

	//operator
	bigNum operator+(const bigNum& a);
	bigNum& operator+=(const bigNum& a);

	bigNum operator-(const bigNum& a);
	bigNum& operator-=(const bigNum& a);

	bigNum operator%(const bigNum& a);
	bigNum& operator%=(const bigNum& a);

	bigNum operator/(const bigNum& a);
	bigNum& operator/=(const bigNum& a);

	bigNum operator=(const bigNum& a);
	bigNum bigexp(const bigNum& a);
	
	void display(ostream& os);
};
ostream& operator<<(ostream& os, const bigNum& a);
bool operator>>(istream& is, const bigNum& a);
