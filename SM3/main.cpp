#include<iostream>
#include"parameter.h"
using namespace std;

int main()
{
	//SM3算法
	string data1 = "helloworld";
	string data2 = "abc";
	string hashresult = hashdata(data1,1);

	//长度扩展攻击
	cout << endl<<"****************length extension attack****************" << endl;
	//制作正确结果用于验证
	string asc1 = "", asc2 = "",m1="";
	for (int i = 0; i < data1.size(); i++)
		asc1 += dectohex((int)data1[i]);		//将data1转为ASCII码形式
	//cout << "data1: " << asc1 << endl<<endl;
	string databin1 = hextobin(asc1);			//转为二进制
	m1 += padding(databin1);					//对data1的二进制形式进行长度扩展
	m1 = bintohex(m1);							//将扩展后的结果转为16进制
	//cout << "data1||padding:" << m1 << endl;

	for (int i = 0; i < data2.size(); i++)		//将data2转为ASCII码形式
		asc2 += dectohex((int)data2[i]);
	m1 = m1 + asc2;								//将扩展后的未知data1与data2进行拼接，存入m1
	//cout << "data1||padding||data2: " << m1 << endl;
	string r1 = hashdata(m1,0);					//计算m1的哈希值，即正确答案
	cout << "正确答案为：" << r1<<endl;
	//长度扩展攻击
	int length = databin1.size();
	string r2=LenExtAttack(hashresult, length, asc2);
	cout << "攻击得到的结果为：" << r2 << endl;
	cout << "****************************length extension attack end******************" << endl << endl;
	return 0;
}