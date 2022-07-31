#pragma once
#include<iostream>
#include<cmath>
#include"parameter.h"

using namespace std;
string LenExtAttack(string md1,int len,string m3);		//length extension attack

string LenExtAttack(string md1,int len,string m3)		
{
	/*length extension attack, 
	md1为未知数据data1的hash结果,len为data1的长度，m3为选择的攻击数据data2的16进制*/
	int num1 = len / 512+1;				//计算填充后data1的长度
	int num2 = m3.size() * 4;			//计算data3长度
	string append = hextobin(m3) + '1'; //手动填充append
	while (append.size() % 512 != 448)
		append += '0';
	string length = dectobin(num1*512+num2);	//注意，长度为data1||padding||data2的长度
	while (length.size() < 64)
		length = '0' + length;
	append = append + length;
	//string appendhex = bintohex(append);
	//cout << "append is: " << appendhex << endl;
	string result = iteration(append, md1);		//由于已手动填充，故此处仅迭代压缩即可
	result = bintohex(result);
	return result;
}
