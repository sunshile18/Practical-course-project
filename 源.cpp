#include <iostream>
#include <string>
#include <cmath>
#include<map>
using namespace std;

//������ת��Ϊʮ�����ƺ���ʵ��
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

//ʮ������ת��Ϊ�����ƺ���ʵ��
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

//������ת��Ϊʮ���Ƶĺ���ʵ��
int two_ten(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string ten_two(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
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

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
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

string padding(string str) {//��亯��
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

string shiftL(string str, int len) {//ʵ��ѭ������
	string res = sixteen_two(str);
	res = res.substr(len) + res.substr(0, len);
	return two_sixteen(res);
}

string XOR(string str1, string str2) {//ʵ��������
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

string AND(string str1, string str2) {//ʵ�������
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

string OR(string str1, string str2) {//ʵ�ֻ����
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

string NOT(string str) {//ʵ�ַǲ���
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

char binXor(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32����ĺ���ʵ��
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

string P1(string str) {//ʵ���û�����P1��X��
	return XOR(XOR(str, shiftL(str, 15)), shiftL(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return XOR(XOR(str, shiftL(str, 9)), shiftL(str, 17));
}

string T(int j) {//����Tj����ֵ�ĺ���ʵ��
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//ʵ�ֲ�������FF����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//ʵ�ֲ�������GG����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) {//��Ϣ��չ����
	string res = str;
	for (int i = 16; i < 68; i++) {
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), shiftL(res.substr((i - 3) * 8, 8), 15))), shiftL(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	for (int i = 0; i < 64; i++) {
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	return res;
}

string compress(string str1, string str2) {//��Ϣѹ������
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

string iteration(string str) {//����ѹ������ʵ��
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

int main() {//������
	std::map<std::string, std::string>mapsm3;
	mapsm3.insert(map<string, string>::value_type("0", "0"));
	srand(time(0));      //�������������
	const int outputlen = 32;
	cout << "����HASH�����ײ��λ��:" << outputlen << endl;
	int n = pow(2,outputlen/2);     //�ַ������� 
	//int n = 3;     //�ַ�������
	bool label = 0;
	while (n--)                              //���β���n���ַ��� 
	{
		int k = rand() % 200 + 50;                  //�������һ���ַ����ĳ��� 
		string data = "";
		for (int i = 1; i <= k; i++)
		{
			int x, s;                        //x��ʾ����ַ���ascii�� ��s��ʾ����ַ��Ĵ�Сд  
			s = rand() % 2;                     //���ʹsΪ1��0��Ϊ1���Ǵ�д��Ϊ0����Сд 
			if (s == 1)                        //���s=1 
				x = rand() % ('Z' - 'A' + 1) + 'A';       //��x��Ϊ��д��ĸ��ascii�� 
			else
				x = rand() % ('z' - 'a' + 1) + 'a';  //���s=0��x��ΪСд��ĸ��ascii�� 
			data += (char)x;//��xת��Ϊ�ַ���� 
		}
		
		string paddingValue = padding(data);
		string result = iteration(paddingValue);

		map<string, string>::iterator iter;
		iter = mapsm3.find(result.substr(0, outputlen/4));
		if (iter != mapsm3.end())
		{
			label = 1;
			cout << "Find!" << endl;
			cout << "����������ײ����Ϣ�ֱ�Ϊ��" << endl;
			cout << iter->second << endl;
			cout << data << endl;
			cout << endl;
			cout << "ǰ"<<outputlen<<"λ��ϣֵΪ:" << endl;
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
		cout<<"û���ҵ���ײ" << endl;
	}
	
	
	system("pause");
	return 0;
}

