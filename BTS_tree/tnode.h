#pragma once
#include<iostream>
#include<string>
using namespace std;


class tnode
{
public:
	int nodevalue;
	tnode* left;
	tnode* right;
	tnode()
		:left(NULL),right(NULL){}
	tnode(int item,tnode* lptr=NULL,tnode* rptr=NULL)
		:nodevalue(item), left(lptr), right(rptr) {}
};


class bts
{
public:
	bts()
		:myroot(NULL){}
	bts(const bts& t);
	int depth();
	tnode* creattree();
	tnode* root() { return myroot; }
	void inorderoutput(tnode* t, string& separator);
	
	void levelorderoutput(tnode* t, string& separator);
	void depthorderoutput(tnode* t, string& separator);

	bool empty() { return myroot == NULL; }

	bool search(int& item,tnode* root);
	void search2(int& item, bool& find, tnode* & subtreeroot,tnode* & parent);
	void insert(int item);
	void remove(int& item);

	void print(tnode* node_ptr, int depth);
private:
	tnode* myroot;
	tnode* copytree(tnode* t);
};

