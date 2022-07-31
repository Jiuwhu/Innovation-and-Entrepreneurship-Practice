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
	long long int k =(double)1.177 * (sqrt(pow(2, Size)));		//计算需要随机选择的数量
	int up = pow(2, Size) - 1;						//计算随机选择的上界
	int temp = 0;
	string y = "",hy="",r2="";
	for (int i = 0;i<k; i++)
	{
		temp=rand()%(up+1);							//随机生成原象
		y = dectohex(temp);
		r2 = hashdata(y,0);
		if (r2 == str)								//比对是否相同
		{
			cout << y << " 的哈希值与"<<str<<"相同\n";
			cout << "************************" << "end" << "****************************" << endl<<endl;
			return y;
		}
		cout << y << " 的哈希值与" << str << "不相同\n";
	}
	cout << "没有找到碰撞。\n";
	cout << endl << "************************" << "end" << "****************************" << endl<<endl;
	return "0";
}
