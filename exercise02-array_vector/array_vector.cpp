#include <iostream>
#include <vector>
#include<iomanip>

using namespace std;
/*arr_sort:�����������ͳ��ȣ���������������ָ�������ָ��
		   Ҫ���β�len�����춯̬���飬�����Ǿ�̬���飻
		   ����̬������ڴ��Ǳ������ڱ�������оͷ���ģ���len��һ��������
		   Ҫ��ѭ��������ԭ������µĶ�̬����������Ԫ��
		   ������̬�����ں�������ý���ʱ�����ھͽ����ˣ���new������ڴ治�ᣬҪ�ֶ�delete��
*/

void arr_sort(int *arr,int len)
{
	int i, j, temp;
	int* newarr = new int[len];
	for (i = 0; i < len; i++)//���춯̬����
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
/*vec_sort��ֻ�贫��vector���������(���ٸ��ƹ��캯���ĵ��ã�����������ʱ����)
			���ô���vector�ĳ��ȣ���Ϊ��size()��Ա����������vector�ĵ�ǰsize
			����vectorʱ�����ñ���ԭvector�����ƣ�ֻ������β��Ƕ���Ĺ��캯��
			���Ƶ�vector������ں������ý���ʱ�Զ������������������ͷŶ�����Ķ�̬�ڴ�
*/
void vec_sort(vector<int>& vec)
{
	int i, j, temp,len=vec.size();
	vector<int> newvec(vec); //�β��Ƕ���Ĺ��캯��
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
//����
int main()
{
	int len;
	cout << setw(15) << left << "���������鳤��:";
	cin >> len;
	cout << setw(15) << left << "������Ԫ��:";
	int *array=new int[len], i;
	for (i = 0; i < len; i++) cin >> array[i];
	vector<int> vec(array,array+len); //�β�ָ��Ĺ��캯��
	
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