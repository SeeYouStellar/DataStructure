#include "tnode.h"
#include<queue>
#include<stack>
#include<iomanip>

using namespace std;
tnode* bts::creattree()
{
	char ch;
	tnode* t;
	cin >> ch;
	if (ch==' ') 
		t=NULL;
	else
	{
		t = new tnode(ch);//ÿ�ݹ�һ�ξͻᴴ��һ��t
		t->left = creattree();
		t->right = creattree();
	}
	return t;
}

tnode* bts::copytree(tnode* t)
{ 
	tnode* newnode,*newright,*newleft;//myroot(t->nodevalue)Ϊʲô����

	if (t = NULL)
		return NULL;

	newleft = copytree(t->left);
	newright = copytree(t->right);
	newnode = new tnode(t->nodevalue, newleft, newright);
	return newnode;
	
}

bts::bts(const bts& t)
{
	copytree(t.myroot);
}

//�������
void bts::inorderoutput(tnode* t, string& separator)
{
	tnode* p = t;
	if (p != NULL)
	{
		inorderoutput(p->left, separator);
		cout << p->nodevalue << separator;
		inorderoutput( p->right, separator);
	}
}


//�����������
void bts::levelorderoutput(tnode* t, string& separator)
{
	queue<tnode*> q;
	tnode* p;
	q.push(t);
	while (!q.empty())
	{
		p = q.front();//always get front
		q.pop();
		cout << p->nodevalue;
		if (p->left != NULL) q.push(p->left);
		if (p->right != NULL) q.push(p->right);
	}
}

//�����������
void bts::depthorderoutput(tnode* t,string& separator)
{
	stack<tnode*> s;
	tnode* p;
	s.push(p);
	while (!s.empty())
	{
		while (s.top())//����һ·�ߵ���
		{
			p = s.top();
			s.push(p->left);
		}
		s.pop();
		//�������нڵ㱻ѹ��ջ�������ÿ���ڵ�������������Ҫ�����ҽڵ㣬ÿ�ΰ�һ����ڵ����ʱ
		//ͬʱ���ҽڵ�ѹ��ջ�У��������ϻ�����һ��ѭ���������ջ��LIFO��
		if (!s.empty())
		{
			p = s.top();
			cout << p->nodevalue;
			s.pop();
			s.push(p->right);
		}
	}
}

bool bts::search(int& item,tnode* root)
{
	if (root == 0)
		return false;
	else if (root->nodevalue > item)
		search(item,root->left);
	else if (root->nodevalue < item)
		search(item, root->right);
	else if (root->nodevalue == item)
		return true;
}

void bts::search2(int& item, bool& find, tnode* & locptr,tnode* & parent)
{
	find = false;
	parent = 0;
	locptr = myroot;
	while (!find && locptr != NULL)
	{
		parent = locptr;
		if (locptr->nodevalue < item)
			locptr = locptr->right;
		else if (locptr->nodevalue > item)
			locptr = locptr->left;
		else
			find = true;
	}
}

void bts::print(tnode* node_ptr, int depth)
{
	if (node_ptr != NULL)
	{
		print(node_ptr->right, depth + 1);
		cout << setw(4 * depth) << " "; 
			cout << node_ptr->nodevalue << endl;
			print(node_ptr->left, depth + 1);
	}
}

void bts::insert(int item)
{
	bool find;
	tnode* locptr=myroot, * parent=NULL;
	search2(item, find, locptr, parent);
	if (!find)
	{
		if (parent == NULL)
			myroot = new tnode(item);
		else if (item < parent->nodevalue)
			parent->left = new tnode(item);
		else
			parent->right = new tnode(item);
	}
	else
		cout << "this element has already been in the tree\n";
}

void bts::remove(int& item)
{
	bool find;
	tnode* locptr=myroot, * parent=NULL;
	search2(item, find, locptr, parent);
	if (!find)
	{
		cout << "error";
		return;
	}
	else
	{
		if (locptr->left != NULL && locptr->right != NULL)
		{
			tnode* xsucc = locptr->right;
			parent = locptr;
			while (xsucc ->left != NULL)
			{
				parent = xsucc;
				xsucc = xsucc->left;
			}
			locptr->nodevalue = xsucc->nodevalue;
			locptr = xsucc;
		}
		tnode* subtree = locptr->left;
		if (subtree == NULL)
			subtree = locptr->right;
		if (parent == NULL)
			myroot = subtree;
		else if (parent->left == locptr)
			parent->left = subtree;
		else 
			parent->right = subtree;
		delete locptr;

	}
}