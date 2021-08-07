
//����
#include <iostream>
#include "minivector.h"
using namespace std;
int main()
{
	int i;
	//���캯��1
	minivector vec1(10);
	cout << "vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;

	//��vec1��ֵ
	for (i = 0; i < 10; i++)
		vec1[i] = i;


	//���캯��2
	minivector vec2(vec1), vec3;
	//��ֵ����=
	vec3 = vec1; 
	cout << endl;
	
	//vec2��vec3������
	cout << "������������:\n";
	cout << "vec1={" << vec1 << '}' << endl;
	cout << "vec2={" << vec2 << '}' << endl;
	cout << "vec3={" << vec3 << '}' << endl;
	cout << endl;

	//�±�[]�����
	cout << "�����±��������\n";
	for (i = 0; i < 10; i++)
		cout << "vec1[" << i << "]:" << vec1[i] << endl;
	cout << endl;
	//����±�������������������ֹͣ�����������ʾ
	//cout << "vec1[" << i << "]:" << vec1[vec1.size()+1] << endl;  

	//back()
	cout<<"vec1.back()��"<<"vec1�����һ��Ԫ�أ�"<<vec1.back()<<endl;
	cout << endl;

	//pop_back()
	vec1.pop_back();
	cout << "vec.pop_back()��"<<"vec1�����һ��Ԫ�أ�" << vec1.back() << endl;
	cout << endl;

	//push_back()
	cout << "��ʱvec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;
	vec1.push_back(10);
	cout << "��vec1ĩβ����һ��Ԫ�غ�\n";
	cout << "vec1's capacity:" << vec1.capacity() << " vec1's size:" << vec1.size() << endl;
	vec1.push_back(11);
	cout << "��vec1ĩβ����һ��Ԫ�غ�\n";
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