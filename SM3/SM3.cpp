#pragma once
/*
* input: hex or dec
* call the function: hashdata()
* output: hash
1. padding data
2. Iterative compression
2.1 message extension
2.2 compression function
*/
#include <iostream>
#include <string>
#include <cmath>
#include"parameter.h"

using namespace std;

string IV = "7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e";

string hashdata(int num,string iv);			//hash the number,input is dec
string hashdata(string num,bool a,string iv);		//hash the number,input is hex

string bintohex(string str); //turn bin to hex
string hextobin(string str);//turn hex to bin
int bintodec(string str);		//turn bin to dec
string dectobin(int str);		//turn dec to bin
int hextodec(string str);		//turn hex to dec
string dectohex(int dec);		//turn dec to hex

string padding(string str);		//padding the data,input is binary
string XOR(string str1, string str2);		//xor operation
string AND(string str1, string str2);		//and operation,input is binary
string OR(string str1, string str2);		//or operation,input is binary
string NOT(string str);		//not operation,input is binary
string P1replacement(string str);		//P1 replacement
string P0replacement(string str);	//P0 replacement
string leftshift(string str, int len);		//Cyclic shift to the left,input is binary
string extension(string str);		//message extension
char BitXor(char str1, char str2);	//xor betweent bit
char BitAnd(char str1, char str2);	//add betweent bit
string ModAdd(string str1, string str2);		//mod 2^32
string funcT(int j);		//implement Tj
string funcFF(string str1, string str2, string str3, int j);			//FF,bool function
string funcGG(string str1, string str2, string str3, int j);			//GG,bool function
string compressfunc(string str1, string str2);		//compression function
string iteration(string str,string iv);		//iteration function

string hashdata(int num,string iv)			//hash the number
{
	cout << "*************************" << "strat hash" << "**********************" << endl;
	string databin = dectobin(num);
	string datahex = bintohex(databin);
	cout << "the hexadecimal representation of the number is: " << datahex << endl;
	
	string data = padding(databin);		//padding data
	data = iteration(data,iv);
	string result = bintohex(data);
	cout << "杂凑值：\n";
	for (int i = 0; i < 8; i++)
		cout << result.substr(i * 8, 8) << " ";
	cout << endl << "************************" << "end" << "****************************" << endl;
	return result;
}

string hashdata(string datap,bool a,string iv)		//hash,input is hex
{
	cout << "*************************" << "strat hash" << "**********************" << endl;
	string datahex = "";
	if (a == 1)					//输入需要转为ascii码再操作,即输入为消息
	{
		for (int i = 0; i < datap.size(); i++)
			datahex += dectohex((int)datap[i]);
		cout << "the ASCII of data is: " << datahex << endl;
	}
	else						////输入为16进制形式
		datahex = datap;		
	string databin = hextobin(datahex);
	string data = padding(databin);		//padding data
	//string data = padding(datap);		//padding data
	data = iteration(data,iv);
	string result = bintohex(data);
	cout << "杂凑值：\n";
	for (int i = 0; i < 8; i++)
		cout << result.substr(i * 8, 8) << " ";
	cout << endl << "************************" << "end" << "****************************" << endl;
	return result;
}

string bintohex(string str)		//turn bin to hex
{
	string hex="";				//the hex
	int temp=0;					//tenth
	int num = str.size() % 4;
	string alphabet = "0123456789abcdef";
	if (num != 0)
	{
		for (int i = num; i < 4; i++)
			str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		temp = ((str[i] - '0') << 3) + ((str[i + 1] - '0') << 2) + ((str[i + 2] - '0') << 1) + (str[i + 3] - '0');
		hex = hex + alphabet[temp];
	}
	return hex;
}

string hextobin(string str)		//turn hex to bin
{
	string alphabet = "0123456789abcdef";
	string hextable[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	string bin = "";
	int temp=0;
	for (int i = 0; i < str.size(); i++)
	{
		temp = alphabet.find(str[i]);
		bin += hextable[temp];
	}
	return bin;
}

int bintodec(string str)		//turn bin to dec
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++) 
		dec += (str[i] - '0')<<(str.size()-i-1);
	return dec;
}

string dectobin(int str)		//turn dec to bin
{		
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

int hextodec(string str)		//turn hex to dec
{
	string temp= hextobin(str);
	int dec = bintodec(temp);
	return dec;
}

string dectohex(int dec)		//turn dec to hex
{
	string temp = dectobin(dec);
	string hex = bintohex(temp);
	return hex;
}

string padding(string str)		//padding the data,input is binary
{
	/*string datahex = "";
	for (int i = 0; i < str1.size(); i++)
		datahex += dectohex((int)str1[i]);
	string str = hextobin(datahex);*/

	string data = "";
	int length = str.size();
	data = str + '1';
	while (data.size() % 512 != 448)
		data += '0';
	string lengthbin = dectobin(length);
	while (lengthbin.size() < 64)
		lengthbin = '0' + lengthbin;
	data = data + lengthbin;
	//string datahex1 = bintohex(data);
	//cout << "消息填充后："<<datahex1 << endl;
	return data;
}

string XOR(string str1, string str2)		//xor operation,input is binary
{
	string str3 = "";
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == str2[i])
			str3 += "0";
		else
			str3 += "1";
	}
	return str3;
}

string AND(string str1, string str2)		//and operation,input is binary
{
	string str3="";
	for (int i = 0; i < str1.size(); i++)
		str3 += str1[i] & str2[i];
	return str3;
}

string OR(string str1, string str2)		//or operation,input is binary
{
	string str3 = "";
	for (int i = 0; i < str1.size(); i++)
		str3 += str1[i] | str2[i];
	return str3;
}

string NOT(string str)		//not operation,input is binary
{
	string str1 = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] ==  '0')
			str1 += "1";
		else
			str1 += "0";
	}
	return str1;
}

string leftshift(string str, int len)		//Cyclic shift to the left len_bit,input is binary
{
	string str1 = str.substr(len) + str.substr(0, len);
	return str1;
}

string P1replacement(string str)		//P1 replacement
{
	return XOR(XOR(str, leftshift(str, 15 )), leftshift(str, 23 ));
}

string extension(string str)		//message extension
{
	string str1 = str;
	for (int i = 16; i < 68; i++)		//generate 17-68 
		str1 += XOR(XOR(P1replacement(XOR(XOR(str1.substr((i - 16) * 32, 32), str1.substr((i - 9) * 32, 32)), leftshift(str1.substr((i - 3) * 32, 32), 15))), leftshift(str1.substr((i - 13) * 32, 32), 7)), str1.substr((i - 6) * 32, 32));
	for (int i = 0; i < 64; i++)
		str1 += XOR(str1.substr(i * 32, 32), str1.substr((i + 4) * 32, 32));
	/*string str2 = bintohex(str1);
	cout << "消息扩展后：" << endl;
	for (int i = 0; i < (str2.size() / 8); i++)
	{
		if (i % 8 == 0 && i != 0)
			cout << endl;
		cout << str2.substr(i * 8, 8) << " ";
	}
	cout << endl;*/
	return str1;
}

char BitXor(char str1, char str2)	//xor betweent bit
{
	return str1 == str2 ? '0' : '1';
}

char BitAnd(char str1, char str2)	//add between bit
{
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2)		//add mod 2^32
{
	string str3 = "";
	char temp = '0';
	for (int i = str1.size() - 1; i >= 0; i--)
	{
		str3 = BitXor(BitXor(str1[i], str2[i]), temp) + str3;
		if (BitAnd(str1[i], str2[i]) == '1') 
			temp = '1';
		else
		{
			if (BitXor(str1[i], str2[i]) == '1') 
				temp = BitAnd('1', temp);
			else 
				temp = '0';			
		}
	}
	return str3;
}

string funcT(int j)		//implement Tj
{
	if (j>=0 && j <= 15)
		return "01111001110011000100010100011001";// 79cc4519
	else
		return "01111010100001111001110110001010";// 7a879d8a
}

string funcFF(string str1, string str2, string str3, int j)		//FF,bool function
{
	if (j>=0 && j <= 15) 
		return XOR(XOR(str1, str2), str3);
	else 
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
}

string funcGG(string str1, string str2, string str3, int j)			//GG,bool function
{
	if (j>=0 && j <= 15) 
		return XOR(XOR(str1, str2), str3);
	else 
		return OR(AND(str1, str2), AND(NOT(str1), str3));
}

string P0replacement(string str)	//P0 replacement
{
	return XOR(XOR(str, leftshift(str, 9)), leftshift(str, 17));
}

string compressfunc(string str1, string str2)		//compression function
{
	string iv = str2;
	string A = iv.substr(0, 32),
		B = iv.substr(32, 32),
		C = iv.substr(64, 32),
		D = iv.substr(96, 32),
		E = iv.substr(128, 32),
		F = iv.substr(160, 32),
		G = iv.substr(192, 32),
		H = iv.substr(224, 32);
	string ss1 = "", ss2 = "", tt1 = "", tt2 = "";
	/*cout << "    A         B         C         D         E         F        G         H " << endl;
	cout << bintohex(A) << "  " << bintohex(B) << "  " << bintohex(C) << "  " << bintohex(D) << "  " 
		<< bintohex(E) << "  " << bintohex(F) << "  " << bintohex(G) << "  " << bintohex(H) << endl;*/
	for (int j = 0; j < 64; j++)
	{
		ss1 = leftshift(ModAdd(ModAdd(leftshift(A, 12), E), leftshift(funcT(j), (j % 32))), 7);
		ss2 = XOR(ss1, leftshift(A, 12));
		tt1 = ModAdd(ModAdd(ModAdd(funcFF(A, B, C, j), D), ss2), str1.substr((j + 68) * 32, 32));
		tt2 = ModAdd(ModAdd(ModAdd(funcGG(E, F, G, j), H), ss1), str1.substr(j  * 32, 32));
		D = C;
		C = leftshift(B, 9);
		B = A;
		A = tt1;
		H = G;
		G = leftshift(F, 19);
		F = E;
		E = P0replacement(tt2);
		/*
		cout << bintohex(A) << "  " << bintohex(B) << "  " << bintohex(C) << "  " << bintohex(D) << "  "
			<< bintohex(E) << "  " << bintohex(F) << "  " << bintohex(G) << "  " << bintohex(H) << endl;
		*/
	}
	string str3 = A + B + C + D + E + F + G + H;
	return str3;
}

string iteration(string str,string iv)		//iteration function
{
	int num = str.size() / 512;
	cout << "消息填充后共有：" << num << "个分组" << endl;
	//string iv = "7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e";
	string iv1 = hextobin(iv);
	string str1="",exstr="",comstr="";//temp
	for (int i = 0; i < num; i++)
	{
		str1 = str.substr(i * 512, 512);
		exstr = extension(str1);
		comstr = compressfunc(exstr, iv1);
		iv1 = XOR(iv1, comstr);
	}
	return iv1;
}
