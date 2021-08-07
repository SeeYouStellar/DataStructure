#include "dlist.h"

using namespace std;

Node* dlist::getNode(int pos)
{
	Node* curr = front;
	while (pos--)
		curr = curr->next;
	return curr;
}

dlist::dlist()
	:size(0)
{
	Node* newnode=new Node();
	front = newnode;
}

int dlist::getpos(Node* p)
{
	Node* curr = front;
	int pos = 0;
	while (curr != p)
	{
		curr = curr->next;
		pos++;
	}
	return pos;
}
dlist::dlist(const dlist& copy)
{
	int pos = 1;
	Node * curr2 = copy.front->next;
	front = new Node();
	
	while (curr2 != copy.front) {
		push_back(curr2->data);//push_back()����size++
		curr2 = curr2->next;
	};
}

dlist& dlist::operator=(const dlist& copy)
{
	//�븴�ƹ��첻ͬ�ĵط����ڡ�=����Ҫ��ԭ����������
	if (getsize())
	{
		Node* curr = front->next, * prev;
		while (curr != front)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		delete curr;
		size = 0;
	}
	else if (front != NULL)//��ֹdlist a��a=b;�����������������Ԫ
	{
		delete front;
	}

	int pos = 1;
	Node * curr2 = copy.front->next;
	front = new Node();

	while (curr2 != copy.front) {
		this->push_back(curr2->data);
		curr2 = curr2->next;
	};
	return *this;
}

dlist::~dlist()
{
	Node* curr=front->next,*prev;
	while (curr != front)
	{
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	delete curr; //������Ԫ�ڵ�
}

void dlist::insert(int pos, int item) //��λ��pos���ڵ�֮ǰ����
{
	Node* newnode=new Node(item), * curr = this->getNode(pos-1);
	Node* later = curr->next;//curr֮��Ľڵ�

	newnode->next = later;
	newnode->prev = curr;

	curr->next = newnode;
	later->prev= newnode;

	size++;
}


void dlist::erase(int pos)
{
	Node* curr = getNode(pos);
	Node* behind = curr->prev, * later = curr->next;//curr֮ǰ��֮��Ľڵ�

	if (curr->next == curr)
		delete curr;
	else
	{
		behind->next = later;
		later->prev = behind;
		delete curr;
	}
	size--;
}

ostream& operator<<(ostream& os, const dlist& d)
{
	Node* curr = d.front->next;
	while (curr != d.front)
	{
		
		if (curr == d.front->next)
		{
			if (curr->data != 0)
				os << curr->data << (curr->next == d.front ? '\0' : ',');
			else if (curr->data == 0 && d.size == 1)
				os << curr->data;
			curr = curr->next;
			continue;
		}
		if (curr->data < 10)
			os << "00" << curr->data << (curr->next == d.front ? '\0' : ',');
		else if(curr->data < 100)
			os << "0" << curr->data << (curr->next == d.front ? '\0' : ',');
		else
			os << curr->data << (curr->next == d.front ? '\0' : ',');
		curr = curr->next;
	}
	return os;
}

void dlist::push_front(int item)
{
	this->insert(1, item);
}

void dlist::push_back(int item)
{
	//this->insert(getsize(), item);
	Node* curr = front->prev;
	Node* newnode = new Node(item);

	newnode->prev = curr;
	newnode->next = front;

	front->prev = newnode;
	curr->next = newnode;

	size++;
}

void dlist::pop_back()
{
	int pos = getsize();
	erase(pos);
}

void dlist::pop_front()
{
	erase(1);
}
//--------------------------------------










