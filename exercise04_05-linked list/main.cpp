
//main.cpp

#include "linked_list.h"
#include<stack>
using namespace std;

int main()
{
	linked_list a, b, c;
	
	
	

	//链表基本功能测试
	/*
	linked_list p = linked_list();
	int i, len, element;
	cout << "请输入链表长度：";
	cin >> len;
	for (i = 1; i <= len; i++)
	{
		cout << "请输入链表第" << i << "个" << "元素：";
		cin >> element;
		p.push_back(element);
	}
	cout << "输出当前链表：" << p;
	cout << "判断链表是否以排序：" << (p.sorted() == 0 ? "未排序" : "已排序") << endl;

	cout << "在第一个元素后插入节点0：";
	p.insert_back(1, 0);
	cout << p << endl;

	cout << "在第6个元素后插入元素节点6：";
	p.insert_back(6, 6);
	cout << p << endl;

	cout << "删除第一个节点：";
	p.erase_node(1);
	cout << p << endl;

	cout << "删除第二个节点：";
	p.erase_node(2);
	cout << p << endl;

	cout << "删除第一个值5的节点：";
	p.erase_value(5);
	cout << p << endl;

	Node q = p.getmax();
	cout << "返回链表中的最大值：" << q.data << endl;
	cout << endl;

	cout << "颠倒链表：";
	p.revert();
	cout << p << endl;

	cout << "删除链表的最后一个节点：";
	p.pop_back();
	cout << p << endl;

	cout << "判断链表是否以排序：" << (p.sorted() == 0 ? "未排序" : "已排序") << endl;*/

	//ex05
	//将数组导入链表	
	
	/*
	int A1[5] = {4,2,9,1,6}, B1[5] = {8,2,1,5,7};
	linked_list A2, B2;
	A2.list_in(A1, 5);
	B2.list_in(B1, 5);
	cout << "A1: " << A2 << endl;
	cout << "b1: " << B2 << endl;
	*/

	//将链表进行排序
	/*
	linked_list A3(A2), B3(B2);
	cout << "排序后: " << endl;
	A3.sort();
	cout << "A3: " << A3 << endl;
	B3.sort();
	cout << "B3: " << B3 << endl;
	*/
	
	//合并链表
	/*
	linked_list C;
	cout << "将两个链表合并并排序:" << endl;
	C.unite(A3.getfront(),B3.getfront());
	cout << "C: "<< C;
	*/

}
