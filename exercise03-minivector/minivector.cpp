// minivector.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "minivector.h"
using namespace std;
/*reverse()成员函数的作用是：1）创造capacity大小的内存块(which newarr point at),把capacity赋给vcapacity成员变量，并使varr指向新内存
							 2）当copy为真时，把原内存块的数据复制过去
							 3）不会更新vsize的值
							其中：1）在构造函数中调用reverse()都是为了获取一块新内存，都不需要复制
								  2）在push_back()中因为要在动态数组现有vsize上增加item，所以要判断vsize==vcapacity来调用reverse()
									如果vsize==vcapacity说明初始创建的内存已满，则自动调用reverse()并且把原数据复制
									(这里就是vector能自由扩大空间而不需要在外部进行申请的原因，因为vector对象的push_back()会自己判断是否内存已满)
*/
void minivector::reverse(int capacity, bool copy)
{
	int* newarr = new int[capacity];//在没有delete newarr之前一直存在
	if (newarr == NULL)
	{
		cerr << "minivector reserve(): memory allocation failure" << endl;
		exit(1);
	}
	if (copy)
		for (int i = 0; i < (vsize>capacity?capacity:vsize); i++) newarr[i] = varr[i];//structure function do not copy,赋值函数copy
	if (varr != NULL) delete[]varr;//just delete place which varr 指向，not delete varible varr;
	vcapacity = capacity;
	varr = newarr;
}
minivector::minivector(int capacity)
	:vsize(0),vcapacity(0),varr(NULL)
{
	if (!capacity)
	{
		cerr << "minivector reserve(): illegal capacity" << endl;
		exit(1);
	}
	reverse(capacity, false);
	vsize = capacity;
	for (int i = 0; i < capacity; i++) varr[i] = 0;
}
minivector::minivector(const minivector& vec)
	:vsize(0), vcapacity(0), varr(NULL)
{
	if (!vec.vsize) 
	{
		cerr << "minivector operator=: formal parammeter is null" << endl;
		exit(1);
	}
	reverse(vec.vcapacity, false); 
	vsize = vec.vsize;
	for (int i = 0; i < vec.vsize; i++) varr[i] = vec.varr[i];
	
}
minivector::~minivector()
{
	if(varr!=nullptr)
		delete[]varr;
}
minivector& minivector::operator=(const minivector& vec)
{
	if (!vec.vsize)
	{
		cerr << "minivector operator=: vector is empty" << endl;
		exit(1);
	}
	reverse(vec.vcapacity, false); 
	vsize = vec.vsize;
	for (int i = 0; i < vec.vsize; i++) varr[i] = vec.varr[i];
	return *this;
}

int& minivector::operator[](int n)
{
	if (n<0 || n>vsize)
	{
		cerr << "minivector operator[]: index range error" << endl;
		exit(1);
	}
	return varr[n];
}
const int& minivector::operator[](int n)const
{
	if (n<0 || n>vsize)
	{
		cerr << "minivector operator[]: index range error" << endl;
		exit(1);
	}
	return varr[n];
}
int& minivector::back()
{
	if (vsize == 0)
	{
		cerr << "minivector back(): vector empty" << endl;
		exit(1);
	}
	return varr[vsize - 1];
}
const int& minivector::back()const
{
	if (vsize == 0)
	{
		cerr << "minivector back(): vector empty" << endl;
		exit(1);
	}
	return varr[vsize - 1];
}
void minivector::pop_back()//thrown the last element
{
	if (vsize == 0)
	{
		cerr << "minivector back(): vector empty" << endl;
		exit(1);
	}
	vsize--;
}
void minivector::push_back(const int& item)
{
	if (vsize == vcapacity)
	{
		if (vcapacity == 0) reverse(1, false);//if old buffer is null
		else reverse(2 * vsize, true);
	}
	varr[vsize++] = item;
}
void minivector::insert(int index, const int& item)//insert before iter
{
	int* p;
	if (index<0 || index>vcapacity)
	{
		cerr<< "minivector insert: illegal index" << endl; 
		exit(1);
	}
	if (vsize == vcapacity)
	{
		if (vcapacity == 0) reverse(1, false);
		else reverse(2 * vsize, true);
	}
	if (index == vsize)
		varr[vsize] = item;
	else
	{
		int i;
		for (i = vsize; i > index; i++)
			varr[i] = varr[i - 1];
		varr[i] = item;
		/*
		for (p = varr+vsize; p != varr+index; p--)
			*p = *(p - 1);
		*(varr+index) = item;
		*/
	}
	vsize++;
}
void minivector::erase(int index)
{
	int* p;
	if (index<0 || index>vcapacity)
	{
		cerr << "minivector erase(): illegal index" << endl;
		exit(1);
	}
	else if (vsize == 0)
	{
		cerr << "minivector erase():vector is empty" << endl;
		exit(1);
	}
	if (index == vsize)
		vsize--;
	else
	{
		for (p = varr+index; p!=varr+vsize-1; p++)
			*p = *(p + 1);
		vsize--;
	}
}
ostream& operator<<(ostream & os,const minivector & vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if(i==vec.size()-1) os << vec[i];
		else os << vec[i] << ',';
	}
	return os;
}



