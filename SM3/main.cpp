#include<iostream>
#include"parameter.h"
using namespace std;

int main()
{
	//SM3�㷨
	string data1 = "helloworld";
	string data2 = "abc";
	string hashresult = hashdata(data1,1);

	//������չ����
	cout << endl<<"****************length extension attack****************" << endl;
	//������ȷ���������֤
	string asc1 = "", asc2 = "",m1="";
	for (int i = 0; i < data1.size(); i++)
		asc1 += dectohex((int)data1[i]);		//��data1תΪASCII����ʽ
	//cout << "data1: " << asc1 << endl<<endl;
	string databin1 = hextobin(asc1);			//תΪ������
	m1 += padding(databin1);					//��data1�Ķ�������ʽ���г�����չ
	m1 = bintohex(m1);							//����չ��Ľ��תΪ16����
	//cout << "data1||padding:" << m1 << endl;

	for (int i = 0; i < data2.size(); i++)		//��data2תΪASCII����ʽ
		asc2 += dectohex((int)data2[i]);
	m1 = m1 + asc2;								//����չ���δ֪data1��data2����ƴ�ӣ�����m1
	//cout << "data1||padding||data2: " << m1 << endl;
	string r1 = hashdata(m1,0);					//����m1�Ĺ�ϣֵ������ȷ��
	cout << "��ȷ��Ϊ��" << r1<<endl;
	//������չ����
	int length = databin1.size();
	string r2=LenExtAttack(hashresult, length, asc2);
	cout << "�����õ��Ľ��Ϊ��" << r2 << endl;
	cout << "****************************length extension attack end******************" << endl << endl;
	return 0;
}