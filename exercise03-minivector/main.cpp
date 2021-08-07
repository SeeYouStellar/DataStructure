
//测试
#include <iostream>
#include "minivector.h"
using namespace std;
int main()
{
	int i;
	//构造函数1
	minivector vec1(10);
	cout << "vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;

	//给vec1赋值
	for (i = 0; i < 10; i++)
		vec1[i] = i;


	//构造函数2
	minivector vec2(vec1), vec3;
	//赋值函数=
	vec3 = vec1; 
	cout << endl;
	
	//vec2和vec3输出情况
	cout << "测试输出运算符:\n";
	cout << "vec1={" << vec1 << '}' << endl;
	cout << "vec2={" << vec2 << '}' << endl;
	cout << "vec3={" << vec3 << '}' << endl;
	cout << endl;

	//下标[]运算符
	cout << "测试下标运算符：\n";
	for (i = 0; i < 10; i++)
		cout << "vec1[" << i << "]:" << vec1[i] << endl;
	cout << endl;
	//检查下标运算符错误输出，程序停止并输出错误提示
	//cout << "vec1[" << i << "]:" << vec1[vec1.size()+1] << endl;  

	//back()
	cout<<"vec1.back()后"<<"vec1的最后一个元素："<<vec1.back()<<endl;
	cout << endl;

	//pop_back()
	vec1.pop_back();
	cout << "vec.pop_back()后"<<"vec1的最后一个元素：" << vec1.back() << endl;
	cout << endl;

	//push_back()
	cout << "此时vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;
	vec1.push_back(10);
	cout << "在vec1末尾增加一个元素后：\n";
	cout << "vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;
	vec1.push_back(11);
	cout << "在vec1末尾增加一个元素后：\n";
	cout << "vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;
	cout << endl;

	//insert()
	vec1.insert(vec1.size(),12);
	cout << "when insert a element in the last,vec1={" << vec1 << '}'<<endl;
	vec1.insert(3, 13);
	cout << "when insert a element in index of 3,vec1={" << vec1 << '}' << endl;
	cout << endl;

	//erase()
	vec1.erase(vec1.size());
	cout << "when erase a element in the last,vec1={" << vec1 << '}' << endl;
	vec1.erase(3);
	cout << "when erase a element in index of 3,vec1={" << vec1 << '}' << endl;
	
}