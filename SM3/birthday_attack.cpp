#pragma once
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include"parameter.h"

using namespace std;

#define Size 256						//hash output is 256-bit
string birattack(string str);		//birthday attack,input is hash

string birattack(string str)		//birthday attack,input is hash
{
	cout << "*************************" << "start birthday attack" << "**********************" << endl;
	srand(time(0));
	long long int k =(double)1.177 * (sqrt(pow(2, Size)));		//������Ҫ���ѡ�������
	int up = pow(2, Size) - 1;						//�������ѡ����Ͻ�
	int temp = 0;
	string y = "",hy="",r2="";
	for (int i = 0;i<k; i++)
	{
		temp=rand()%(up+1);							//�������ԭ��
		y = dectohex(temp);
		r2 = hashdata(y,0);
		if (r2 == str)								//�ȶ��Ƿ���ͬ
		{
			cout << y << " �Ĺ�ϣֵ��"<<str<<"��ͬ\n";
			cout << "************************" << "end" << "****************************" << endl<<endl;
			return y;
		}
		cout << y << " �Ĺ�ϣֵ��" << str << "����ͬ\n";
	}
	cout << "û���ҵ���ײ��\n";
	cout << endl << "************************" << "end" << "****************************" << endl<<endl;
	return "0";
}
