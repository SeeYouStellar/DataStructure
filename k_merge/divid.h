#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<windows.h>
#define MAX 1000000/500
#define MAX2 500
using namespace std;

double t1, t2;  //t1�����ݣ�д���ݣ�t2�ڲ�����

int divid()
{
	char name[80];
	double begin, begin1;
	double end, end1;
	FILE* fp;
	int* a;
	a = new int[MAX + 1];
	int i;
	int j;
	fopen_s(&fp, "test.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	std::cout.precision(3);
	begin1 = (double)GetTickCount();
	for (j = 1; j <= MAX2; j++)
	{

		sprintf_s(name, "C:/Users/������/Desktop/k_merge/part/%02d.txt", j);

		//��ȡ�ļ�
		begin = (double)GetTickCount();
		for (i = 1; i < MAX + 1; i++)
		{
			fscanf_s(fp, "%d", &a[i]);
		}
		end = (double)GetTickCount();
		//std::cout << "�������ݻ��ѵ�ʱ��:" << (end - begin) << "\n";
		t1 += (end - begin);

		//��������
		begin = (double)GetTickCount();
		sort(a, a+MAX);
		end = (double)GetTickCount();
		//std::cout << "�������������ѵ�ʱ��:" << (end - begin) << "\n";
		t2 += (end - begin);
		//д���ļ�
		FILE* fp1;
		fopen_s(&fp1, name, "w");
		begin = (double)GetTickCount();
		if (fp1 == NULL)
		{
			return 0;
		}
		for (i = 1; i < MAX; i++)
		{
			fprintf_s(fp1, "%d ", a[i]);
			if (i % 30 == 0 && i != 0)
			{
				fprintf(fp1, "\n");
			}
		}
		fprintf_s(fp1, "%d", a[i]);
		end = (double)GetTickCount();
		fclose(fp1);
		//std::cout << "д�����ݻ��ѵ�ʱ��:" << (end - begin) << "\n";
		t1 += (end - begin);
	}
	end1 = (double)GetTickCount();
	//std::cout << "��ʮ�����ֳ�500���ļ������������ѵ�ʱ��:" << (end1 - begin1);
	cout << "��д500���ļ�ʱ��:"<< t1/1000 << " ; "<<"500���ļ��ڲ�����ʱ��" <<t2/1000 <<endl;
	fclose(fp);
	delete[] a;
	return 0;
}

