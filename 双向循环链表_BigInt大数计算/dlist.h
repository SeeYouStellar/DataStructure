
//带哑元节点的双向循环链表
#pragma once
#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* prev;
	Node()
	{
		next = this;
		prev = this;
	}
	Node(const int& item)
		:data(item)
	{
		next = this;
		prev = this;
	}
};

class dlist
{
private:
	Node* front;
	int size;
	Node* getNode(int pos);
public:
	dlist();
	dlist(const dlist& copy);
	dlist& operator=(const dlist& copy);
	~dlist();

	void insert(int pos, int item);
	void push_front(int item);
	void push_back(int item);
	void pop_back();
	void pop_front();
	void erase(int pos);
	int getpos(Node* p);

	int getsize() { return size; }
	int getsize() const { return size; }
	Node* getfront() { return front; }
	Node* getfront() const { return front; }

	friend ostream& operator<<(ostream& os, const dlist& d);
};


