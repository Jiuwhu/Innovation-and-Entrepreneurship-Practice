#pragma once
#include<iostream>
#include<cmath>
#include"parameter.h"

using namespace std;
string LenExtAttack(string md1,int len,string m3);		//length extension attack

string LenExtAttack(string md1,int len,string m3)		
{
	/*length extension attack, 
	md1为未知数据m1的hash结果,len为m1的长度，m3为选择的攻击数据的16进制*/
	int num1 = len / 512+1;
	int num2 = m3.size() * 4;
	string append = hextobin(m3) + '1';
	while (append.size() % 512 != 448)
		append += '0';
	string length = dectobin(num1*512+num2);
	while (length.size() < 64)
		length = '0' + length;
	append = append + length;
	//string appendhex = bintohex(append);
	//cout << "append is: " << appendhex << endl;
	string result = iteration(append, md1);
	result = bintohex(result);
	return result;
}