#include <iostream>
#include<time.h>
#include"random.h"
#include"divid.h"
#include"result.h"

using namespace std;
int main()
{
	unsigned int begin, end, begin1, begin2, begin3, end1, end2, end3;
	begin = (unsigned int)time(NULL);
	begin1 = (unsigned int)time(NULL);
	random();
	begin2 = (unsigned int)time(NULL);
	end1 = (unsigned int)time(NULL);
	std::cout << "�����ļ���ʱ" << (end1 - begin1) << "s" << endl;
	divid();
	begin3 = (unsigned int)time(NULL);
	end2 = (unsigned int)time(NULL);
	std::cout << "�ڲ�����Ӷ�д�ļ���ʱ" << (end2 - begin2) << "s" << endl;
	result();
	end3 = (unsigned int)time(NULL);
	end = (unsigned int)time(NULL);
	std::cout << "�鲢����Ӷ�д�ļ���ʱ" << (end3 - begin3) << "s" << endl;
	std::cout << "����ʱΪ" << (end - begin) << "s" << endl;
}

