
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

//顺序添加新元素的算法：1）创造新节点
//                    2）将back指针指向的节点的next值改为新节点的地址，即指向新节点
//                    3）改变back指针的指向，即将back指向新的节点

//复制构造函数是一种构造函数，与‘=’运算符还是有区别，因为复制构造函数是创建一个新的对象，而
//‘=’是将原来已有的一个对象改变成一个新的对象，原来的对象占用的内存需要被释放

linked_list::linked_list(const linked_list& copy)//当用户传入的是对象
	:front(NULL),back(NULL),size(copy.size)
{
	Node* newnode,*curr=copy.front;
	while (curr!=NULL)
	{
		if (curr==copy.front)          //为何要变成两个分支（后面的成员函数也一样）:因为添加新元素的算法是通过改变back指针进行的，而不用改变front，但是添加第一个元素时front指针需要被创建（即需要改变front）
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
		curr = curr->next;//遍历copy对象
	}
}

linked_list::linked_list(Node* copy)  //当用户传入的是首节点
	:front(NULL), back(NULL), size(0)
{
	Node* newnode, * curr = copy;//与形参是对象的复制构造函数唯一的区别
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
		i++;//传入指针无法直接获取链表长度
	}
	size = i;
}
linked_list& linked_list::operator=(const linked_list& copy)
{
	//若原来对象有节点，就将这些节点所占内存释放掉
	if (size)
	{
		Node* curr = front, * prev;
		while (curr != NULL)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
			prev = NULL;//这里是保守做法，因为prev所指向的内存被释放掉了，但prev的值仍然是原来内存的地址，只是指向了空值，若在次调用它程序编译不会出错，但结果不对
		}
	}

	//复制构造函数部分
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

//注意要对front和back指针进行调整，因为他们指向的空间释放了，他们的值仍然在，只是变成了垃圾值，所以要时刻对他们赋空
linked_list::~linked_list()
{
	Node* prev;
	while (front != NULL)
	{
		prev = front;
		front = front->next;
		delete prev;
		prev = NULL;//赋空
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


//队尾删除节点的算法：1）首先找到倒数第二个节点，定义为prev
//                  2）再找到队尾元素，定义为curr
//                  3）释放curr所指的内存
//                  4）改变back指针，让back等于prev
//                  5) 将prev的next赋空
void linked_list::pop_back()
{
	if (front == NULL)
	{
		cerr << "linked_list pop_bcak():list is empty\n";
		exit(1);
	}
	
	if (front->next == NULL)
	{
		delete front;//一个节点的链表back=front；释放front指向的内存也是释放back指向的内存
		//保险操作
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

int linked_list::getpos(Node* p)//第一个节点pos等于1
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

Node* linked_list::getpointer(int pos)//pos为1的节点是队首节点
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

Node& linked_list::getmax()//返回的是最大值所在的节点
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


bool linked_list::sorted()//判断链表是否已顺序排序
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

void linked_list::swap_value(int pos1, int pos2) //用户输入pos，但操作需要指针来完成
{
	//选择排序所需的swap代码
	Node* curr1=front, * curr2=front;
	if (pos1<1 || pos1>size || pos2<1 || pos2>size)//排除非法pos
	{
		cerr << "linked_list swap_Node(): illegal pos" << endl;
		exit(1);
	}
	/*
	调用getpointer()来代替遍历，实质仍然是遍历
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

	//交换排序
	for ( curr1 = front; curr1->next != NULL; curr1 = curr1->next)
		for (curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next)
			if (curr1->data > curr2->data) swap_value(getpos(curr1), getpos(curr2));
}

//二次析构：对已析构的内存进行二次析构，即当上一个对象析构完，下一个对象执行析构时，析构函数里遍历，当curr指针到了
//最后一个未被析构的节点时，它的next仍然是一个正常地址值（实际上这块内存已经被释放），那么编译器就会再内存中寻找这个地址指向
//的内存，此时就会陷入无尽的寻找中，程序无法正常结束。这个问题是不能通过delete时的保险做法避免的，因为上一个对象被析构时，虽然每一次delete都将prev
//赋了空，但前面那个对象的最后一个节点的next仍然有值，照样会去无限寻址。

/*错误写法
void linked_list::unite(Node* p1, Node* p2)
{
	this->front = p1;
	this->back->next = p2;
}
*/

void linked_list::unite(Node* p1,Node* p2)//不要直接将两个链表首尾相连，这样会造成二次析构问题
{
	Node* newnode;
	while (p1 != NULL && p2 != NULL) //当某一个链表的节点元素都被串起来时跳出循环
	{
		if (p1->data < p2->data)//顺序排列时，把比较后小的那个元素值作为新节点的值，并继续遍历p1
		{
			newnode = new Node(p1->data, NULL);
			p1 = p1->next;
		}
		else
		{
			newnode = new Node(p2->data, NULL);
			p2 = p2->next;
		}
		//将back指向新节点，并特殊处理front
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
	//对剩余的没有被串起来的元素进行串联，只可能跳入下面循环中的一个。
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

//倒转链表的算法：1）创立三个指针，curr，prev,nextnode；
//              2）用curr记录当前节点，用prev记录前一个节点，用nextnode记录下一个节点（即curr的next的值）；
//              3）curr的next指针指向prev，完成倒转操作，此时curr已经没有后驱，所以用第二步用nextnode来充当next
//              4）prev向前遍历等于curr，curr继续向前遍历等于nextnode；
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
		nextnode = nextnode->next;//1）
		curr->next = prev;//2）
		prev = curr;//3）
		curr = nextnode;//4）
	}
	front = prev;//此时prev指向原先链表的最后一个节点，这个节点是新链表的头
	back->next = NULL;//给原先的队首一个后驱指向NULL
}

//insert的几个特殊条件设置需要再斟酌
//插入某个节点，需要有一个prev指针，以及curr指针
//prev指向要插入的pos的前一个节点，curr指向pos位置的节点
void linked_list::insert_front(int pos, int item)//这不是pop_back，这里是在任意pos节点前面插入节点，调用后新节点的pos是pos+1;
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
	//插入节点
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

void linked_list::insert_back(int pos, int item)//是在任意pos节点后面插入节点，调用后新节点位置是是pos
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
	//插入节点
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

//删除第一个出现的值为形参的节点，需要有一个pre指针，以及curr指针
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
			if (prev == NULL)//删除链首
				front = curr->next;
			else if (curr == back)//删除链尾
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

	if (pos == 1)//删除头部指针并更新头部指针	
		front = curr->next;
	else {
		int curr_pos = 1;
		while (curr_pos != pos) {
			prev = curr;
			curr = curr->next;
			curr_pos++;
		}
		prev->next = curr->next;
		if (pos == size)//更新尾部指针
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



