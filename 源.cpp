#include <iostream>
#include <string>
#include <cmath>
#include<map>
using namespace std;

//二进制转换为十六进制函数实现
string two_sixteen(string str) {
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (temp < 10) {
			hex += to_string(temp);
		}
		else {
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//十六进制转换为二进制函数实现
string sixteen_two(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

//二进制转换为十进制的函数实现
int two_ten(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//十进制转换为二进制的函数实现
string ten_two(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//十六进制转换为十进制的函数实现
int sixteen_ten(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//十进制转换为十六进制的函数实现
string ten_sixteen(int str) {
	string hex = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}

string padding(string str) {//填充函数
	string res = "";
	for (int i = 0; i < str.size(); i++) {
		res += ten_sixteen((int)str[i]);
	}
	
	int res_length = res.size() * 4;
	res += "8";
	while (res.size() % 128 != 112) {
		res += "0";//
	}
	string res_len = ten_sixteen(res_length);
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string shiftL(string str, int len) {//实现循环左移
	string res = sixteen_two(str);
	res = res.substr(len) + res.substr(0, len);
	return two_sixteen(res);
}

string XOR(string str1, string str2) {//实现异或操作
	string res1 = sixteen_two(str1);
	string res2 = sixteen_two(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return two_sixteen(res);
}

string AND(string str1, string str2) {//实现与操作
	string res1 = sixteen_two(str1);
	string res2 = sixteen_two(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return two_sixteen(res);
}

string OR(string str1, string str2) {//实现或操作
	string res1 = sixteen_two(str1);
	string res2 = sixteen_two(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return two_sixteen(res);
}

string NOT(string str) {//实现非操作
	string res1 = sixteen_two(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return two_sixteen(res);
}

char binXor(char str1, char str2) {//实现单比特的异或操作
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//实现单比特的与操作
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32运算的函数实现
	string res1 = sixteen_two(str1);
	string res2 = sixteen_two(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return two_sixteen(res);
}

string P1(string str) {//实现置换功能P1（X）
	return XOR(XOR(str, shiftL(str, 15)), shiftL(str, 23));
}

string P0(string str) {//实现置换功能P0（X）
	return XOR(XOR(str, shiftL(str, 9)), shiftL(str, 17));
}

string T(int j) {//返回Tj常量值的函数实现
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//实现布尔函数FF功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//实现布尔函数GG功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) {//消息扩展函数
	string res = str;
	for (int i = 16; i < 68; i++) {
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), shiftL(res.substr((i - 3) * 8, 8), 15))), shiftL(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	for (int i = 0; i < 64; i++) {
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	return res;
}

string compress(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = shiftL(ModAdd(ModAdd(shiftL(A, 12), E), shiftL(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, shiftL(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = shiftL(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = shiftL(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	return res;
}

string iteration(string str) {//迭代压缩函数实现
	int num = str.size() / 128;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main() {//主函数
	std::map<std::string, std::string>mapsm3;
	mapsm3.insert(map<string, string>::value_type("0", "0"));
	srand(time(0));      //产生随机化种子
	const int outputlen = 32;
	cout << "考虑HASH输出碰撞的位数:" << outputlen << endl;
	int n = pow(2,outputlen/2);     //字符串个数 
	//int n = 3;     //字符串个数
	bool label = 0;
	while (n--)                              //依次产生n个字符串 
	{
		int k = rand() % 200 + 50;                  //随机生成一个字符串的长度 
		string data = "";
		for (int i = 1; i <= k; i++)
		{
			int x, s;                        //x表示这个字符的ascii码 ，s表示这个字符的大小写  
			s = rand() % 2;                     //随机使s为1或0，为1就是大写，为0就是小写 
			if (s == 1)                        //如果s=1 
				x = rand() % ('Z' - 'A' + 1) + 'A';       //将x赋为大写字母的ascii码 
			else
				x = rand() % ('z' - 'a' + 1) + 'a';  //如果s=0，x赋为小写字母的ascii码 
			data += (char)x;//将x转换为字符输出 
		}
		
		string paddingValue = padding(data);
		string result = iteration(paddingValue);

		map<string, string>::iterator iter;
		iter = mapsm3.find(result.substr(0, outputlen/4));
		if (iter != mapsm3.end())
		{
			label = 1;
			cout << "Find!" << endl;
			cout << "两个发生碰撞的消息分别为：" << endl;
			cout << iter->second << endl;
			cout << data << endl;
			cout << endl;
			cout << "前"<<outputlen<<"位哈希值为:" << endl;
			cout << result.substr(0, outputlen / 4) << endl;
			break;
		}
		else
		{
			mapsm3.insert(map<string, string>::value_type(result.substr(0, outputlen / 8), data));
		}
	}
	if (label == 0)
	{
		cout<<"没有找到碰撞" << endl;
	}
	
	
	system("pause");
	return 0;
}

