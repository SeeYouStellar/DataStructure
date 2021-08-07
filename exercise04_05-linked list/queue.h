#pragma once
#include "linked_list.h"
#include <iostream>
using namespace std;
class queue
{
private:
	Node* front, *back;
	int size;
public:
	queue()
		:front(NULL), back(NULL), size(0){}
	void enqueue(int value);
	void dequeue();
	int get_front();
	int get_back();
	bool empty();
	//void display(ostream& os) const;
	friend ostream& operator << (ostream& os, const queue& q);
};
//ostream& operator << (ostream & os, const queue & q);

