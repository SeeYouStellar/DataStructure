#include "queue.h"

void queue::enqueue(int value)
{
	Node* newnode = new Node(value, NULL);
	if (front == NULL)
	{
		front = newnode;
		back = newnode;
	}
	else
	{
		back->next = newnode;
		back = newnode;
	}
	size++;
}
void queue::dequeue()
{
	Node* curr=front;
	if (!size)
	{
		cerr << "queue dequeue: queue is empty" << endl;
		exit(1);
	}
	else
	{
		while (curr->next != back)
			curr = curr->next;
		back = curr;
		delete curr;
		curr = NULL;
	}
}
int queue::get_front()
{
	return front->data;
}
int queue::get_back()
{
	return back->data;
}
bool queue::empty()
{
	return size == 0;
}
/*
void queue::display(ostream& os) const
{
	Node* curr;
	for (curr = front; curr != NULL; curr = curr->next)
		os << curr->data << " ";
	os << endl;
}
ostream& operator << (ostream& os, const queue& q)
{
	q.display(os);
	return os;
}
*/
ostream& operator << (ostream& os, const queue& q)
{
	Node* curr;
	for (curr = q.front; curr != NULL; curr = curr->next)
		os << curr->data << " ";
	return os;
}
