
//main.cpp

#include "linked_list.h"
#include<stack>
using namespace std;

int main()
{
	linked_list a, b, c;
	
	
	

	//����������ܲ���
	/*
	linked_list p = linked_list();
	int i, len, element;
	cout << "�����������ȣ�";
	cin >> len;
	for (i = 1; i <= len; i++)
	{
		cout << "�����������" << i << "��" << "Ԫ�أ�";
		cin >> element;
		p.push_back(element);
	}
	cout << "�����ǰ����" << p;
	cout << "�ж������Ƿ�������" << (p.sorted() == 0 ? "δ����" : "������") << endl;

	cout << "�ڵ�һ��Ԫ�غ����ڵ�0��";
	p.insert_back(1, 0);
	cout << p << endl;

	cout << "�ڵ�6��Ԫ�غ����Ԫ�ؽڵ�6��";
	p.insert_back(6, 6);
	cout << p << endl;

	cout << "ɾ����һ���ڵ㣺";
	p.erase_node(1);
	cout << p << endl;

	cout << "ɾ���ڶ����ڵ㣺";
	p.erase_node(2);
	cout << p << endl;

	cout << "ɾ����һ��ֵ5�Ľڵ㣺";
	p.erase_value(5);
	cout << p << endl;

	Node q = p.getmax();
	cout << "���������е����ֵ��" << q.data << endl;
	cout << endl;

	cout << "�ߵ�����";
	p.revert();
	cout << p << endl;

	cout << "ɾ����������һ���ڵ㣺";
	p.pop_back();
	cout << p << endl;

	cout << "�ж������Ƿ�������" << (p.sorted() == 0 ? "δ����" : "������") << endl;*/

	//ex05
	//�����鵼������	
	
	/*
	int A1[5] = {4,2,9,1,6}, B1[5] = {8,2,1,5,7};
	linked_list A2, B2;
	A2.list_in(A1, 5);
	B2.list_in(B1, 5);
	cout << "A1: " << A2 << endl;
	cout << "b1: " << B2 << endl;
	*/

	//�������������
	/*
	linked_list A3(A2), B3(B2);
	cout << "�����: " << endl;
	A3.sort();
	cout << "A3: " << A3 << endl;
	B3.sort();
	cout << "B3: " << B3 << endl;
	*/
	
	//�ϲ�����
	/*
	linked_list C;
	cout << "����������ϲ�������:" << endl;
	C.unite(A3.getfront(),B3.getfront());
	cout << "C: "<< C;
	*/

}
