#include <iostream>
#include "bigNum.h"
using namespace std;

//operator
bigNum bigNum::operator+(const bigNum& a)
{

}

bigNum& bigNum::operator+=(const bigNum& a)
{

}

bigNum bigNum::operator-(const bigNum& a)
{

}

bigNum& bigNum::operator-=(const bigNum& a)
{

}

bigNum bigNum::operator%(const bigNum& a)
{

}
bigNum& bigNum::operator%=(const bigNum& a)
{

}

bigNum bigNum::operator/(const bigNum& a)
{

}

bigNum& bigNum::operator/=(const bigNum& a)
{

}

bigNum bigNum::operator=(const bigNum& a)
{

}
bigNum bigNum::bigexp(const bigNum& a)
{

}

void bigNum::display(ostream& os)
{

}

ostream& operator<<(ostream& os, const bigNum& a)
{

}

bool operator>>(istream& is, bigNum& a)
{
	int i;
	string s;
	cin >> s;
	for (i = 0; i < s.size(); i += 8)
	{

		a.getlist().push_back(int(s.substr(i, 8)));
	}
}