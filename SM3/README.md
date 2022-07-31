### SM3

#### SM3算法实现

SM3算法包含两个过程：消息填充和迭代压缩，迭代压缩包括消息扩展和压缩。

本代码中padding()函数实现消息填充功能：

```C++
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
```

然后iteration()函数实现迭代压缩功能：

```C++
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
```

其中调用的extension()函数和compressfunc()函数分别实现消息扩展功能和压缩功能：

```C++
string extension(string str)		//message extension
{
	string str1 = str;
	for (int i = 16; i < 68; i++)		//generate 17-68 
		str1 += XOR(XOR(P1replacement(XOR(XOR(str1.substr((i - 16) * 32, 32), str1.substr((i - 9) * 32, 32)), leftshift(str1.substr((i - 3) * 32, 32), 15))), leftshift(str1.substr((i - 13) * 32, 32), 7)), str1.substr((i - 6) * 32, 32));
	for (int i = 0; i < 64; i++)
		str1 += XOR(str1.substr(i * 32, 32), str1.substr((i + 4) * 32, 32));
	return str1;
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
	}
```

为了使用方便，对外使用hashdata()函数作为接口，调用该函数即可对目的消息进行哈希。函数的参数中，datap为要哈希的对象，可以为message形式，也可为16进制形式；进一步的处理用bool变量a来区分，message形式则a=1，16进制形式则a=0；iv变量为初始值iv的值，存在默认值，由于链接器的机制，故仅在头文件的声明时声明了默认值。函数具体如下：

```C++
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
	data = iteration(data,iv);
	string result = bintohex(data);
	cout << "杂凑值：\n";
	for (int i = 0; i < 8; i++)
		cout << result.substr(i * 8, 8) << " ";
	cout << endl << "************************" << "end" << "****************************" << endl;
	return result;
}
```

如果突发奇想，要对十进制的数进行哈希，提供了重载函数hashdata(int num)。

#### 长度扩展攻击

攻击条件：

data1为未知消息，但data1的长度可以获取，data2为攻击者随意选择的数据，已知。

已知哈希函数的原理并且可以使用哈希函数，已知data1的哈希值。

攻击过程及原理：

首先制作正确答案。将data1进行消息填充，然后获得m1=data1||padding||data2（||符合表示级联，padding为对data1消息填充的填充的部分），然后对m1进行哈希，获得正确答案r1。这部分代码如下（由于使用了SM3算法中的padding()函数，因其输入、输出为二进制，故进行了一些进制转换）：

```C++
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
```

然后开始攻击，攻击功能在LenExtAttack()函数实现。

长度扩展攻击的目的，是获得和m1=未知数据data1||padding||data2相同的哈希值。故我假设这个消息本身就是ｍ１。所以依据SM３算法的分组原理，最后一次迭代压缩即为data2||padding1（padding1是对m1的填充），又因为data1的哈希值md1已知，所以只需要对data2进行手动填充，然后令初始值iv=md1，在进行一次哈希即可。由于前面已完成手动消息填充，所以仅剩下迭代压缩部分，不需要再调用哈希函数hashdata()，仅需要调用iteration()函数即可。具体代码如下：

```C++
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
```

### 运行结果

运行结果见上一级目录下的README文件，其中展示了所有的运行结果，相关图片也上传至该目录下。

### 代码说明

具体思路及简单说明如上，更多细节请查看代码内的注释。注释可能略乱，请见谅。

### 运行方式

将该文件下所有代码文件放到同一项目下即可。

main.cpp文件为主文件。

### 参考文献

https://blog.csdn.net/szuaurora/article/details/78125585

https://blog.csdn.net/qq_40662424/article/details/121637732



ps：

1.由于本人暂时不会放图片，故说明时放的是代码块而不是代码的截图

2.代码的注释本打算使用全英文，但限于个人英语水平，最终出现中英混用的情况。