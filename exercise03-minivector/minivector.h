#pragma once
#ifndef MINIVECTOR_H
#define MINIVECTOR_H
#include<iostream>
class minivector
{
private:
	int vsize;
	int vcapacity;
	int* varr;
	void reverse(int capacity, bool copy);
public:
	minivector(int capacity = 0);
	minivector(const minivector& vec);
	~minivector();
	minivector& operator=(const minivector& vec);

	int& operator[](int item);
	const int& operator[](int n)const;

	int& back();
	const int& back()const;

	void pop_back();
	void push_back(const int& n);
	
	int size() { return vsize; }
	const int size()const { return vsize; }
	bool isempty() { return vsize == vcapacity; }
	int capacity() { return vcapacity; }

	void insert(int index,const int& item);
	void erase(int index);

	
	friend std::ostream& operator<<(std::ostream& os, const minivector& vec);
};
#endif // !MINIVECTOR_H



