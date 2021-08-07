#include<iostream>
#include"tnode.h"

using namespace std;
int main()
{	
	int i;
	bts t1;
	string str = " ";
	t1.insert(1);
	t1.insert(4);
	t1.insert(3);
	t1.insert(9);
	t1.insert(6);
	t1.print(t1.root(),0);
	t1.inorderoutput(t1.root(),str);

}