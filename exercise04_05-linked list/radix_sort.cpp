#include<iostream>
#include<queue>
#include<vector>
using namespace std;
void distribute(vector<int>& v, queue<int> queuelist[], int power)//按个位排则power等于1，十位则为10...
{
	int len = v.size(), i;
	for (i = 0; i < len; i++)
		queuelist[(v[i] / power) % 10].push(v[i]);
	v.clear();
		
}
void collect(vector<int>& v, queue<int> queuelist[])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		while (!queuelist[i].empty())
		{
			v.push_back(queuelist[i].front());
			queuelist[i].pop();
		}
	}
}
void radix_sort(vector<int>& v, int d)
{
	queue<int> queuelist[10];
	int i, power = 1;
	for (i = 0; i < d; i++)
	{
		distribute(v, queuelist, power);
		collect(v, queuelist);
		power *= 10;
	}
}
void display(const vector<int>& v)
{
	int i, len = v.size();
	for (i = 0; i < len; i++)
		cout << v[i] << ' ';
}
//一个project只能有一个main函数
/*int main() 
{
	vector<int> vec;
	int element;

	while (cin >> element)
		vec.push_back(element);

	radix_sort(vec, 2);
	display(vec);
}*/
