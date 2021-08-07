#include "bigint.h"
#include <vector>
using namespace std;

bigint& bigint::operator=(const bigint& d)//bigint 的=
{
	len = d.len;
	this->mydlist = d.mydlist;
	return *this;
}

ostream& operator<<(ostream& os, const bigint& d)
{
	os << d.mydlist;
	return os;
}

istream& operator>>(istream& is, bigint& d)
{
	int i, num, len;
	string s;
	is >> s;

	len = s.length();
	d.len = len;

	if (len % 3 != 0)//如果大数位数不是3的倍数，则要将前面2位或1位拿出，即将len%3拿出放入第一个节点中
	{
		num = getint(s, 0, len % 3);
		d.mydlist.insert(1, num);
	}
	for (i = 0; i < len / 3; i++)
	{
		num = getint(s, len % 3 + i * 3, 3);
		d.mydlist.insert((len % 3 ? 2 + i : 1 + i), num);//如果大数位数正好是3的倍数，则直接从第一个节点开始插入，若不是则第一个节点已经有数
	}
	return is;
}

bool bigint::operator==(bigint& d)
{
	if (this->mydlist.getsize() == d.mydlist.getsize())
	{
		int i;
		Node* curr_ = this->mydlist.getfront()->prev, * curr_d = d.mydlist.getfront()->prev;
		for (i = 1; i <= this->mydlist.getsize(); i++)
		{
			if (curr_->data != curr_d->data)
				return false;
			curr_ = curr_->prev;
			curr_d = curr_d->prev;
		}
		return true;
	}
	else {
		return false;
	}
}

bigint bigint::operator+(bigint& d)
{
	bigint out;
	Node* curr1 = mydlist.getfront()->prev, * curr2 = d.mydlist.getfront()->prev;
	int num1, num2, temp = 0;
	while (curr1 != mydlist.getfront() || curr2 != d.mydlist.getfront())
	{
		num1 = curr1 != mydlist.getfront() ? curr1->data : 0;
		num2 = curr2 != d.mydlist.getfront() ? curr2->data : 0;
		if (num1 + num2 + temp > 999)
		{
			out.mydlist.push_front( temp + num1 + num2 - 1000);
			//out.mydlist.insert(1, temp + num1 + num2 - 1000);
			temp = 1;
		}
		else 
		{
			out.mydlist.push_front(num1 + num2 + temp);
			temp = 0;
		}
			//out.mydlist.insert(1, num1 + num2 + temp);
		if(curr1!=mydlist.getfront()) 
			curr1 = curr1->prev;
		if(curr2!=d.mydlist.getfront())
			curr2 = curr2->prev;
	}
	if (temp != 0) out.mydlist.push_front(temp);//out.mydlist.insert(1, temp);
	return out;
}

void bigint::operator+=(bigint& d)
{
	(*this) = (*this).operator+(d);
}

bigint& bigint::operator++()//前++
{
	Node* curr = this->mydlist.getfront()->prev;
	int flag = 0;
	while (curr != this->mydlist.getfront())
	{
		if (curr->data + 1 <= 999)
		{
			curr->data++;
			flag = 1;
			break;
		}
		else
			curr->data = 0;
		curr = curr->prev;
	}
	if (!flag) this->mydlist.push_front(1);//this->mydlist.insert(1, 1);
	return *this;
}

bigint bigint::operator++(int)//后++
{
	bigint temp = *this;
	Node* curr = this->mydlist.getfront()->prev;
	int flag = 0;
	while (curr != this->mydlist.getfront())
	{
		if (curr->data + 1 <= 999)
		{
			curr->data++;
			flag = 1;
			break;
		}
		else
			curr->data = 0;
		curr = curr->prev;
	}
	if (!flag) this->mydlist.push_front(1);//this->mydlist.insert(1, 1);
	return temp;
}

bigint max(const bigint& a, const bigint& b)
{
	int lena = a.getdlist().getsize(), lenb = b.getdlist().getsize();
	bigint c;
	if (lena > lenb)
		return (c = a);
	else if (lena < lenb)
		return (c = b);
	else {
		Node* pa = a.getdlist().getfront()->next, * pb = b.getdlist().getfront()->next;
		int i;
		for (i = 0; i < lena; i++)
		{
			int valuea_pernode = pa->data, valueb_pernode = pb->data;
			if (valuea_pernode != valueb_pernode)
				return valuea_pernode > valueb_pernode ? (c = a) : (c = b);
			pa = pa->next;
			pb = pb->next;
		}
	}
}

bigint min(const bigint& a, const bigint& b)
{
	int lena = a.getdlist().getsize(), lenb = b.getdlist().getsize();
	bigint c;
	if (lena > lenb)
		return (c = b);
	else if (lena < lenb)
		return (c = a);
	else {
		Node* pa = a.getdlist().getfront()->next, * pb = b.getdlist().getfront()->next;
		int i;
		for (i = 0; i < lena; i++)
		{
			int valuea_pernode = pa->data, valueb_pernode = pb->data;
			if (valuea_pernode != valueb_pernode)
				return valuea_pernode > valueb_pernode ? (c = b) : (c = a);
			pa = pa->next;
			pb = pb->next;
		}
	}
}

int getint(string& s, int pos, int len)
{
	int i, sum = 0;
	for (i = 0; i < len; i++)
		sum = sum * 10 + s[pos + i] - '0';
	return sum;
}

bigint bigint::operator-(bigint& d)
{

	Node* curr_max = mydlist.getfront()->prev, * curr_min = d.mydlist.getfront()->prev;
	while (curr_min != d.mydlist.getfront())
	{
		if (curr_max->data >= curr_min->data)
			curr_max->data -= curr_min->data;
		else
		{
			Node* prev_max;
			curr_max->data -= curr_min->data - 1000;//借来1000
			for (prev_max = curr_max->prev; prev_max != mydlist.getfront(); prev_max = prev_max->prev)
			{
				if (prev_max->data != 0) {
					prev_max->data--;//借出去1000
					break;
				}
				else
					prev_max->data = 999;
			}
		}
		curr_max = curr_max->prev;
		curr_min = curr_min->prev;
	}
	//若有剩余的max_的节点未遍历，也不需要去遍历了
	Node* curr = mydlist.getfront()->next;
	while (curr->data == 0)
		mydlist.pop_front();
	return *this;
}

void bigint::operator-=(bigint& d)
{
	*this = (*this).operator-(d);
	/*

	dlist max_ = max(*this, d), min_ = min(*this, d);

	Node* curr_max = this->front->prev, * curr_min = d.front->prev;

	while (curr_min != d.front)
	{
		if (curr_max->data >= curr_min->data)
			curr_max->data -= curr_min->data;
		else
		{
			Node* prev_max;
			curr_max->data -= curr_min->data - 1000;//借来1000
			for (prev_max = curr_max->prev; prev_max != max_.front; prev_max = prev_max->prev)
			{
				if (prev_max->data != 0) {
					prev_max->data--;//借出去1000
					break;
				}
				else
					prev_max->data = 999;
			}
		}
		curr_max = curr_max->prev;
		curr_min = curr_min->prev;
	}
	//若有剩余的max_的节点未遍历，也不需要去遍历了
	*/
}

bigint bigint::operator--(int)//后--
{
	bigint temp = *this;
	Node* curr;
	for (curr = this->mydlist.getfront()->prev; curr != this->mydlist.getfront(); curr = curr->prev)
	{
		if (curr->data != 0)
		{
			curr->data--;
			break;
		}
		else
			curr->data = 999;
	}
	return temp;
}

bigint& bigint::operator--()//前--
{
	Node* curr;
	for (curr = this->mydlist.getfront()->prev; curr != this->mydlist.getfront(); curr = curr->prev)
	{
		if (curr->data != 0)
		{
			curr->data--;
			break;
		}
		else
			curr->data = 999;
	}
	return *this;
}

bigint bigint::operator*(bigint& d)
{
	int i,tmp;
	bigint out;
	Node* curr = mydlist.getfront()->prev, * curr_d = d.mydlist.getfront()->prev;

	while (curr_d != d.mydlist.getfront())
	{

		bigint temp;

		for (i = 1; i < d.mydlist.getsize()-d.mydlist.getpos(curr_d)+1; i++)
			temp.mydlist.push_front(0);

		tmp = 0;

		while (curr != mydlist.getfront())
		{
			temp.mydlist.push_front((curr->data * curr_d->data + tmp) % 1000);
			tmp = (curr->data * curr_d->data + tmp) / 1000;
			curr = curr->prev;
		}
		if (tmp != 0)
			temp.mydlist.push_front(tmp);
		out += temp;

		curr_d = curr_d->prev;
		curr = curr->prev;
	}
	return out;
}

/*

*/
void bigint::operator*=(bigint& d)
{
	*this = (*this).operator*(d);
}

bigint bigint::operator/(bigint& d)
{
	bigint out,copy_d;
	out.mydlist.push_back(0);
	while (d <= *this)
	{
		int i, count = 0;
		copy_d = d;
		bigint temp;
		for (i = 0; i < mydlist.getsize() - d.mydlist.getsize(); i++)
		{
			copy_d.mydlist.push_back(0);
			temp.mydlist.push_back(0);
		}
		if (*this < copy_d)
		{
			copy_d.mydlist.pop_back();
			temp.mydlist.pop_back();
		}
		do
		{
			(*this) -= copy_d;
			count++;
		} while (*this >= copy_d);
		temp.mydlist.push_front(count);
		out += temp;
	}
	return out;
}

void bigint::operator/=(bigint& d)
{
	*this = (*this) / d;
}

bool bigint::operator>=(bigint& d)
{
	if (this->mydlist.getsize() == d.mydlist.getsize())
	{
		int i;
		Node* curr_ = this->mydlist.getfront()->next, * curr_d = d.mydlist.getfront()->next;
		for (i = 1; i <= this->mydlist.getsize(); i++)
		{
			if (curr_->data > curr_d->data)
				return true;
			else if (curr_->data < curr_d->data)
				return false;
			curr_ = curr_->next;
			curr_d = curr_d->next;
		}
		return true;
	}
	else if (this->mydlist.getsize() > d.mydlist.getsize())
		return true;
	else
		return false;
}

bool bigint::operator<=(bigint& d)
{
	if (this->mydlist.getsize() == d.mydlist.getsize())
	{
		int i;
		Node* curr_ = this->mydlist.getfront()->next, * curr_d = d.mydlist.getfront()->next;
		for (i = 1; i <= this->mydlist.getsize(); i++)
		{
			if (curr_->data < curr_d->data)
				return true;
			else if (curr_->data > curr_d->data)
				return false;
			curr_ = curr_->next;
			curr_d = curr_d->next;
		}
		return true;
	}
	else if (this->mydlist.getsize() > d.mydlist.getsize())
		return false;
	else
		return true;
}


bigint bigint::pow(bigint& power)
{
	Node* back = power.mydlist.getfront()->prev;
	bigint temp_2,base(*this),result,temp_0;
	temp_2.mydlist.push_back(2);//用来进行除2操作的2
	temp_0.mydlist.push_back(0);
	result.mydlist.push_back(1);//用来承载结果的对象
	while (power > temp_0)
	{
		if (back->data % 2 == 0)
		{
			power /= temp_2;
			base = base * base;
		}
		else
		{
			power /= temp_2;
			result = result * base;
			base = base * base;
		}
		back = power.mydlist.getfront()->prev;
	}
	
	return result;
}