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
		t = new tnode(ch);//每递归一次就会创造一个t
		t->left = creattree();
		t->right = creattree();
	}
	return t;
}

tnode* bts::copytree(tnode* t)
{ 
	tnode* newnode,*newright,*newleft;//myroot(t->nodevalue)为什么不行

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

//中序遍历
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


//广度优先搜索
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

//深度优先搜索
void bts::depthorderoutput(tnode* t,string& separator)
{
	stack<tnode*> s;
	tnode* p;
	s.push(p);
	while (!s.empty())
	{
		while (s.top())//左链一路走到底
		{
			p = s.top();
			s.push(p->left);
		}
		s.pop();
		//当左链有节点被压入栈中则进行每个节点的输出，这里需要处理右节点，每次把一个左节点输出时
		//同时将右节点压入栈中，并且马上会在下一个循环中输出（栈的LIFO）
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