#pragma once

//linked_list.h
#include<iostream>
using namespace std;

class Node
{
public:
	int data;
	Node* next;
	Node() :next(NULL) {}
	Node(const int& item, Node* p = NULL) : data(item), next(p) {}
};

class linked_list
{
private:

	//有链尾以及链首指针，所以在后续的成员方法中，需要调整链首和链尾的都需要单独列出
	Node* front;
	Node* back;
	int size;
	int getpos(Node* p);//只有成员函数才会调用Node* 类型数据

public:

	linked_list()
		:front(NULL),back(NULL),size(0){}
	linked_list(const linked_list& copy);
	linked_list(Node* copy);//完善
	~linked_list();

	bool empty() { return size == 0; }
	int getsize() { return size; }

	Node* getfront() { return front; }
	Node* getfront() const { return front; }

	Node* getback() { return back; }
	Node* getback() const { return back; }

	Node& getmax();
	Node* getpointer(int pos);//此方法是可以用来在外部调用的


	bool sorted();
	void sort();

	void list_in(int* list, int len);
	void swap_value(int pos1,int pos2);
	void push_back(const int& item);
	void pop_back();
	void revert();
	void insert_back(int pos, int item);//在pos之后插入
	void insert_front(int pos, int item);//在pos之前插入
	void unite(Node* p1,Node* p2);

	void erase_node(int pos);//删除pos位置的节点
	void erase_value(int value);//按值遍历删除指定值
	
	void display(ostream& os) const;
	linked_list& operator=(const linked_list& list);
	//friend ostream& operator<<(ostream& os,const linked_list& list);
};
ostream& operator<<(ostream& os, const linked_list& list);

