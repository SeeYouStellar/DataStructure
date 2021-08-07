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

	//����β�Լ�����ָ�룬�����ں����ĳ�Ա�����У���Ҫ�������׺���β�Ķ���Ҫ�����г�
	Node* front;
	Node* back;
	int size;
	int getpos(Node* p);//ֻ�г�Ա�����Ż����Node* ��������

public:

	linked_list()
		:front(NULL),back(NULL),size(0){}
	linked_list(const linked_list& copy);
	linked_list(Node* copy);//����
	~linked_list();

	bool empty() { return size == 0; }
	int getsize() { return size; }

	Node* getfront() { return front; }
	Node* getfront() const { return front; }

	Node* getback() { return back; }
	Node* getback() const { return back; }

	Node& getmax();
	Node* getpointer(int pos);//�˷����ǿ����������ⲿ���õ�


	bool sorted();
	void sort();

	void list_in(int* list, int len);
	void swap_value(int pos1,int pos2);
	void push_back(const int& item);
	void pop_back();
	void revert();
	void insert_back(int pos, int item);//��pos֮�����
	void insert_front(int pos, int item);//��pos֮ǰ����
	void unite(Node* p1,Node* p2);

	void erase_node(int pos);//ɾ��posλ�õĽڵ�
	void erase_value(int value);//��ֵ����ɾ��ָ��ֵ
	
	void display(ostream& os) const;
	linked_list& operator=(const linked_list& list);
	//friend ostream& operator<<(ostream& os,const linked_list& list);
};
ostream& operator<<(ostream& os, const linked_list& list);

