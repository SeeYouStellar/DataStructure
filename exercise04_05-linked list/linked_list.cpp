
//linked_list.cpp
#include "linked_list.h"
using namespace std;


void linked_list::list_in(int* list, int len)
{

	int i;
	Node* newnode;
	if (len <= 0)
	{
		cerr << "linked_list list_in(int n): illegal size\n";
		exit(1);
	}
	for (i = len-1; i>=0; i--)
	{
		newnode = new Node(list[i], front);
		front = newnode;
		size++;
	}
	back = this->getpointer(len);
}

//˳�������Ԫ�ص��㷨��1�������½ڵ�
//                    2����backָ��ָ��Ľڵ��nextֵ��Ϊ�½ڵ�ĵ�ַ����ָ���½ڵ�
//                    3���ı�backָ���ָ�򣬼���backָ���µĽڵ�

//���ƹ��캯����һ�ֹ��캯�����롮=�������������������Ϊ���ƹ��캯���Ǵ���һ���µĶ��󣬶�
//��=���ǽ�ԭ�����е�һ������ı��һ���µĶ���ԭ���Ķ���ռ�õ��ڴ���Ҫ���ͷ�

linked_list::linked_list(const linked_list& copy)//���û�������Ƕ���
	:front(NULL),back(NULL),size(copy.size)
{
	Node* newnode,*curr=copy.front;
	while (curr!=NULL)
	{
		if (curr==copy.front)          //Ϊ��Ҫ���������֧������ĳ�Ա����Ҳһ����:��Ϊ�����Ԫ�ص��㷨��ͨ���ı�backָ����еģ������øı�front��������ӵ�һ��Ԫ��ʱfrontָ����Ҫ������������Ҫ�ı�front��
		{
			front = new Node(curr->data, NULL);
			back = front;
		}
		else
		{
			newnode = new Node(curr->data, NULL);
			back->next = newnode;
			back = newnode;
		}
		curr = curr->next;//����copy����
	}
}

linked_list::linked_list(Node* copy)  //���û���������׽ڵ�
	:front(NULL), back(NULL), size(0)
{
	Node* newnode, * curr = copy;//���β��Ƕ���ĸ��ƹ��캯��Ψһ������
	int i = 0;
	while (curr != NULL)
	{
		if (curr == copy)
		{
			front = new Node(curr->data, NULL);
			back = front;
		}
		else
		{
			newnode = new Node(curr->data, NULL);
			back->next = newnode;
			back = newnode;
		}
		curr = curr->next;
		i++;//����ָ���޷�ֱ�ӻ�ȡ������
	}
	size = i;
}
linked_list& linked_list::operator=(const linked_list& copy)
{
	//��ԭ�������нڵ㣬�ͽ���Щ�ڵ���ռ�ڴ��ͷŵ�
	if (size)
	{
		Node* curr = front, * prev;
		while (curr != NULL)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
			prev = NULL;//�����Ǳ�����������Ϊprev��ָ����ڴ汻�ͷŵ��ˣ���prev��ֵ��Ȼ��ԭ���ڴ�ĵ�ַ��ֻ��ָ���˿�ֵ�����ڴε�����������벻��������������
		}
	}

	//���ƹ��캯������
	size = copy.size;
	Node* newnode, * curr = copy.front;
	while (curr != NULL)
	{
		if (curr == copy.front)
		{
			front = new Node(curr->data, NULL);
			back = front;
		}
		else
		{
			newnode = new Node(curr->data, NULL);
			back->next = newnode;
			back = newnode;
		}
		curr = curr->next;
	}
	return *this;
}

//ע��Ҫ��front��backָ����е�������Ϊ����ָ��Ŀռ��ͷ��ˣ����ǵ�ֵ��Ȼ�ڣ�ֻ�Ǳ��������ֵ������Ҫʱ�̶����Ǹ���
linked_list::~linked_list()
{
	Node* prev;
	while (front != NULL)
	{
		prev = front;
		front = front->next;
		delete prev;
		prev = NULL;//����
	}
}

void linked_list::push_back(const int& item)
{
	
	Node* newnode = new Node(item, NULL);
	if (newnode == NULL)
	{
		cerr << "linked_list push_back(const int& item):memory failure\n";
		exit(1);
	}
	if (front == NULL)
	{
		front = newnode;
		back = front;
	}
	else
	{
		back->next = newnode;
		back = newnode;
	}
	size++;
}


//��βɾ���ڵ���㷨��1�������ҵ������ڶ����ڵ㣬����Ϊprev
//                  2�����ҵ���βԪ�أ�����Ϊcurr
//                  3���ͷ�curr��ָ���ڴ�
//                  4���ı�backָ�룬��back����prev
//                  5) ��prev��next����
void linked_list::pop_back()
{
	if (front == NULL)
	{
		cerr << "linked_list pop_bcak():list is empty\n";
		exit(1);
	}
	
	if (front->next == NULL)
	{
		delete front;//һ���ڵ������back=front���ͷ�frontָ����ڴ�Ҳ���ͷ�backָ����ڴ�
		//���ղ���
		front = NULL;
		back = NULL;
	}
	else
	{
		Node* curr = front, * prev=NULL;
		while (curr != back)
		{
			prev = curr;
			curr = curr->next;
		}
		
		delete curr;
		curr = NULL;	
		
		back = prev;
		prev->next = NULL;
	}
	size--;
}

int linked_list::getpos(Node* p)//��һ���ڵ�pos����1
{
	Node* curr = front;
	int index = 1;
	while (curr != p)
	{
		index++;
		curr = curr->next;
	}
	return index;
}

Node* linked_list::getpointer(int pos)//posΪ1�Ľڵ��Ƕ��׽ڵ�
{
	Node* curr = front;
	int curr_pos = 1;
	while (curr_pos != pos)
	{
		curr = curr->next;
		curr_pos++;
	}
	return curr;
}

Node& linked_list::getmax()//���ص������ֵ���ڵĽڵ�
{
	Node* curr=front,*max=front;
	if (front == NULL)
	{
		cerr << "linked_list getmax():list is empty\n";
		exit(1);
	}
	while (curr != NULL)
	{
		if (curr->data > max->data)
			max = curr;
		curr = curr->next;
	}
	return *max;
}


bool linked_list::sorted()//�ж������Ƿ���˳������
{
	Node* curr = front;
	if (size == 0)
	{
		cerr << "linked_list sorted(): size = 0" << endl;
		exit(1);
	}
	while (curr -> next != NULL)
	{
		if (curr->data > curr->next->data)
			return false;
		curr = curr->next;
	}
	return true;
}

void linked_list::swap_value(int pos1, int pos2) //�û�����pos����������Ҫָ�������
{
	//ѡ�����������swap����
	Node* curr1=front, * curr2=front;
	if (pos1<1 || pos1>size || pos2<1 || pos2>size)//�ų��Ƿ�pos
	{
		cerr << "linked_list swap_Node(): illegal pos" << endl;
		exit(1);
	}
	/*
	����getpointer()�����������ʵ����Ȼ�Ǳ���
	int i = 1;
	while (i < pos1)
	{
		curr1 = curr1->next;
		i++;
	}
	i = 1;
	while (i < pos2)
	{
		curr2 = curr2->next;
		i++;
	}*/
	curr1 = getpointer(pos1);
	curr2 = getpointer(pos2);
	int data;
	data = curr1->data;
	curr1->data = curr2->data;
	curr2->data = data;
}

void linked_list::sort()
{
	Node* curr1,*curr2;
	if (!size)
	{
		cerr << "linked_list sort(): list is empty" << endl;
		exit(1);
	}

	//��������
	for ( curr1 = front; curr1->next != NULL; curr1 = curr1->next)
		for (curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next)
			if (curr1->data > curr2->data) swap_value(getpos(curr1), getpos(curr2));
}

//���������������������ڴ���ж���������������һ�����������꣬��һ������ִ������ʱ�������������������currָ�뵽��
//���һ��δ�������Ľڵ�ʱ������next��Ȼ��һ��������ֵַ��ʵ��������ڴ��Ѿ����ͷţ�����ô�������ͻ����ڴ���Ѱ�������ַָ��
//���ڴ棬��ʱ�ͻ������޾���Ѱ���У������޷�������������������ǲ���ͨ��deleteʱ�ı�����������ģ���Ϊ��һ����������ʱ����Ȼÿһ��delete����prev
//���˿գ���ǰ���Ǹ���������һ���ڵ��next��Ȼ��ֵ��������ȥ����Ѱַ��

/*����д��
void linked_list::unite(Node* p1, Node* p2)
{
	this->front = p1;
	this->back->next = p2;
}
*/

void linked_list::unite(Node* p1,Node* p2)//��Ҫֱ�ӽ�����������β��������������ɶ�����������
{
	Node* newnode;
	while (p1 != NULL && p2 != NULL) //��ĳһ������Ľڵ�Ԫ�ض���������ʱ����ѭ��
	{
		if (p1->data < p2->data)//˳������ʱ���ѱȽϺ�С���Ǹ�Ԫ��ֵ��Ϊ�½ڵ��ֵ������������p1
		{
			newnode = new Node(p1->data, NULL);
			p1 = p1->next;
		}
		else
		{
			newnode = new Node(p2->data, NULL);
			p2 = p2->next;
		}
		//��backָ���½ڵ㣬�����⴦��front
		if (front==NULL)
		{
			front = newnode;
			back = newnode;
		}
		else
		{
			back->next = newnode;
			back = newnode;
		}
	}
	//��ʣ���û�б���������Ԫ�ؽ��д�����ֻ������������ѭ���е�һ����
	while (p1 != NULL)
	{
		newnode = new Node(p1->data, NULL);
		p1 = p1->next;
		back->next = newnode;
		back = newnode;
	}
	while (p2 != NULL)
	{
		newnode = new Node(p2->data, NULL);
		p2 = p2->next;
		back->next = newnode;
		back = newnode;
	}
}

//��ת������㷨��1����������ָ�룬curr��prev,nextnode��
//              2����curr��¼��ǰ�ڵ㣬��prev��¼ǰһ���ڵ㣬��nextnode��¼��һ���ڵ㣨��curr��next��ֵ����
//              3��curr��nextָ��ָ��prev����ɵ�ת��������ʱcurr�Ѿ�û�к����������õڶ�����nextnode���䵱next
//              4��prev��ǰ��������curr��curr������ǰ��������nextnode��
void linked_list::revert()
{
	Node* curr = front->next, * prev = front, * nextnode = front->next;
	if (size <= 1)
	{
		cerr << "linked_list revert(): size is too small" << endl;
		exit(1);
	}
	back = front;
	while (nextnode != NULL)
	{
		nextnode = nextnode->next;//1��
		curr->next = prev;//2��
		prev = curr;//3��
		curr = nextnode;//4��
	}
	front = prev;//��ʱprevָ��ԭ����������һ���ڵ㣬����ڵ����������ͷ
	back->next = NULL;//��ԭ�ȵĶ���һ������ָ��NULL
}

//insert�ļ�����������������Ҫ������
//����ĳ���ڵ㣬��Ҫ��һ��prevָ�룬�Լ�currָ��
//prevָ��Ҫ�����pos��ǰһ���ڵ㣬currָ��posλ�õĽڵ�
void linked_list::insert_front(int pos, int item)//�ⲻ��pop_back��������������pos�ڵ�ǰ�����ڵ㣬���ú��½ڵ��pos��pos+1;
{
	Node* newnode = new Node(item, NULL), *curr = front, *prev = NULL;
	if (pos < 0 || pos>size) {
		cerr << "linked_list insert(int n, int item): illegal variable n" << endl;
		exit(1);
	}
	else if (newnode == NULL)
	{
		cerr << "linked_list insert(int n, int item):Allocation Error" << endl;
		exit(1);
	}
	//����ڵ�
	if (front == NULL || pos == size)
	{
		push_back(item);
		/*front = newnode;
		back = front;*/
	}
	else 
	{
		int curr_pos = 1;
		while (curr_pos <= pos) {
			prev = curr;
			curr = curr->next;
			curr_pos++;
		}
		newnode->next = curr;
		prev->next = newnode;
	}
	size++;
}

void linked_list::insert_back(int pos, int item)//��������pos�ڵ�������ڵ㣬���ú��½ڵ�λ������pos
{
	Node* newnode = new Node(item, NULL), * curr = front, * prev = NULL;
	if (pos <= 0 || pos > size) {
		cerr << "linked_list insert(int n, int item): illegal variable n" << endl;
		exit(1);
	}
	else if (newnode == NULL)
	{
		cerr << "linked_list insert(int n, int item):Allocation Error" << endl;
		exit(1);
	}
	//����ڵ�
	if (front == NULL)
	{
		front = newnode;
		back = front;
	}
	else if (pos == 1)
	{
		newnode->next = front;
		front = newnode;
	}
	else 
	{
		int curr_pos = 1;
		while (curr_pos <= pos) {
			prev = curr;
			curr = curr->next;
			curr_pos++;
		}
		newnode->next = curr;
		prev->next = newnode;
	}
	size++;
}

//ɾ����һ�����ֵ�ֵΪ�βεĽڵ㣬��Ҫ��һ��preָ�룬�Լ�currָ��
void linked_list::erase_value(int value)
{
	Node* curr = front, *prev = NULL;
	bool flag = false;
	if (front == NULL)
	{
		cerr << "linked_list erase_value(int value): list is empty\n";
		exit(1);
	}
 	while (curr != NULL && !flag)
	{
		if (curr->data == value)
		{
			if (prev == NULL)//ɾ������
				front = curr->next;
			else if (curr == back)//ɾ����β
			{
				prev->next = curr->next;
				back = prev;
			}
			else
				prev->next = curr->next;
			size--;
			delete curr;
			curr = NULL;
			flag = true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	if (!flag)
	{
		cerr << "linked_list erase_value(int value): value doesn't exist\n";
		exit(1);
	}
}
//
void linked_list::erase_node(int pos)
{
	Node* curr = front, * prev = NULL;
	if (pos > size || pos <= 0) {
		cerr << "linked_list erase_node(int pos): illegal variable n" << endl;
		exit(1);
	}
	else if (front == NULL)
	{
		cerr << "linked_list erase_node(int pos):list is empty" << endl;
		exit(1);
	}

	if (pos == 1)//ɾ��ͷ��ָ�벢����ͷ��ָ��	
		front = curr->next;
	else {
		int curr_pos = 1;
		while (curr_pos != pos) {
			prev = curr;
			curr = curr->next;
			curr_pos++;
		}
		prev->next = curr->next;
		if (pos == size)//����β��ָ��
			back = prev;
	}
	delete curr;
	curr = NULL;
	size--;
}

//output
void linked_list::display(ostream& os) const
{
	if (front == NULL)
	{
		cerr << "linked_list display(ostream& os) : linked_list isn't exist" << endl;
		exit(1);
	}
	Node* p;
	for (p = front; p!= NULL; p = p->next)
		os << p->data << (p->next== NULL ? '\n' : ' ');
}

ostream& operator<<(ostream& os, const linked_list& list)
{
	list.display(os);
	return os;
}

//use friend function to output
/*ostream& operator<<(ostream& os,,const linked_list& list)
{
	if (front == NULL)
	{
		cerr << "linked_list display() : linked_list isn't exist" << endl;
		exit(1);
	}
	Node* p;
	for (p = front; p != NULL; p = p->next)
		os << p->data<<(p->next==NULL?'\n':' ');
	return os;
}
*/



