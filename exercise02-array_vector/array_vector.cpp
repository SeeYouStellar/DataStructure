#include <iostream>
#include <vector>
#include<iomanip>

using namespace std;
/*arr_sort:传入数组名和长度，其中数组名代表指向数组的指针
		   要用形参len来创造动态数组，而不是静态数组；
		   （静态数组的内存是编译器在编译过程中就分配的，但len是一个变量）
		   要用循环来遍历原数组和新的动态数组来复制元素
		   其他静态变量在函数体调用结束时生命期就结束了，但new申请的内存不会，要手动delete；
*/

void arr_sort(int *arr,int len)
{
	int i, j, temp;
	int* newarr = new int[len];
	for (i = 0; i < len; i++)//构造动态数组
		newarr[i] = arr[i];
	for (i = 1; i < len; i++)
	{
		for (j = len-1; j >= i; j--)
		{
			if (newarr[j]<newarr[j-1])
			{
				temp = newarr[j - 1];
				newarr[j - 1] = newarr[j];
				newarr[j] = temp;
			}
		}
	}
	for (i = 0; i < len; i++)
	{
		if (i == 0) cout << newarr[i];
		else cout << " " << newarr[i];
	}
	cout << "\n";
	delete[]newarr;
}
/*vec_sort：只需传入vector对象的引用(减少复制构造函数的调用，不用生成临时变量)
			不用传入vector的长度，因为有size()成员函数来返回vector的当前size
			复制vector时，不用遍历原vector来复制，只需调用形参是对象的构造函数
			复制的vector对象会在函数调用结束时自动调用析构函数，来释放对象里的动态内存
*/
void vec_sort(vector<int>& vec)
{
	int i, j, temp,len=vec.size();
	vector<int> newvec(vec); //形参是对象的构造函数
	for (i = 1; i < len; i++)
	{
		for (j = len - 1; j >= i; j--)
		{
			if (newvec[j] < newvec[j - 1])
			{
				temp = newvec[j-1];
				newvec[j - 1]=newvec[j];
				newvec[j] = temp;
			}
		}
	}
	for (i = 0; i < len; i++)
	{
		if (i == 0) cout << newvec[i];
		else cout << " " << newvec[i];
	}
	cout << "\n";
	
}
//测试
int main()
{
	int len;
	cout << setw(15) << left << "请输入数组长度:";
	cin >> len;
	cout << setw(15) << left << "请输入元素:";
	int *array=new int[len], i;
	for (i = 0; i < len; i++) cin >> array[i];
	vector<int> vec(array,array+len); //形参指针的构造函数
	
	//arr_sort
	cout << setw(15) << left << "sorted array:";
	arr_sort(array, len);
	cout << setw(15) << left << "old array:";
	for (i = 0; i < len; i++)   //old array keeps original
	{
		if (i == 0) cout << array[i];
		else cout << " " << array[i];
	}
	cout << endl;

	//vec_sort
	cout << setw(15) << left << "sorted vector:";
	vec_sort(vec);
	cout << setw(15) << left << "old vector:";
	for (i = 0; i < len; i++)   //old vector keeps original
	{
		if (i == 0) cout << vec[i];
		else cout << " " << vec[i];
	}
	cout << endl;
	delete[]array;
}