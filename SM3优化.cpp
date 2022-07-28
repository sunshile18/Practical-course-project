#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

//二进制转换为十六进制函数实现
string twoTOsixteen(string str) {
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {//因为每四位二进制数就能够成为一个十六进制数，所以将二进制数长度转换为4的倍数
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//判断出4位二进制数的十进制大小为多少
		if (temp < 10) {//当得到的值小于10时，可以直接用0-9来代替
			hex += to_string(temp);
		}
		else {//当得到的值大于10时，需要进行A-F的转换
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//十六进制转换为二进制函数实现
//优化：循环展开（4）+常量只计算一次（临时变量存储）
string sixteenTOtwo(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int tmp = str.size();
	for (int i = 0; i < tmp; i+=4) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
		if (str[i+1] >= 'A' && str[i+1] <= 'F') {
			bin += table[str[i+1] - 'A' + 10];
		}
		else {
			bin += table[str[i+1] - '0'];
		}
		if (str[i + 2] >= 'A' && str[i + 2] <= 'F') {
			bin += table[str[i + 2] - 'A' + 10];
		}
		else {
			bin += table[str[i + 2] - '0'];
		}
		if (str[i + 3] >= 'A' && str[i + 3] <= 'F') {
			bin += table[str[i + 3] - 'A' + 10];
		}
		else {
			bin += table[str[i + 3] - '0'];
		}
	}
	return bin;
}

//二进制转换为十进制的函数实现
//优化：循环展开（4）+常量只计算一次（临时变量存储）
int twoTOten(string str) {
	int dec = 0;
	int tmp = str.size();
	for (int i = 0; i < tmp; i+=4) {
		dec += (str[i] - '0') * pow(2, tmp - i - 1);
		dec += (str[i+1] - '0') * pow(2, tmp - i);
		dec += (str[i+2] - '0') * pow(2, tmp - i +1);
		dec += (str[i+3] - '0') * pow(2, tmp - i +2);
	}
	return dec;
}

//十进制转换为二进制的函数实现
string tenTOtwo(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//十六进制转换为十进制的函数实现
//优化：循环展开（4）+常量只计算一次（临时变量存储）
int sixteenTOten(string str) {
	int dec = 0;
	int tmp = str.size();
	for (int i = 0; i < tmp; i+=4) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, tmp - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, tmp - i - 1);
		}
		if (str[i+1] >= 'A' && str[i+1] <= 'F') {
			dec += (str[i+1] - 'A' + 10) * pow(16, tmp - i);
		}
		else {
			dec += (str[i+1] - '0') * pow(16, tmp - i);
		}
		if (str[i+2] >= 'A' && str[i+2] <= 'F') {
			dec += (str[i+2] - 'A' + 10) * pow(16, tmp - i+1);
		}
		else {
			dec += (str[i+2] - '0') * pow(16, tmp - i+1);
		}
		if (str[i+3] >= 'A' && str[i+3] <= 'F') {
			dec += (str[i+3] - 'A' + 10) * pow(16, tmp - i+2);
		}
		else {
			dec += (str[i+3] - '0') * pow(16, tmp - i+2);
		}
	}
	return dec;
}

//十进制转换为十六进制的函数实现
string tenTOsixteen(int str) {
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

string pad(string res) {//对数据进行填充 
	
	
	int res_length = res.size() * 4;//记录的长度为2进制下的长度
	res += "8";//在获得的数据后面添1，在16进制下相当于是添加8
	while (res.size() % 128 != 112) {
		res += "0";
	}
	string res_len = tenTOsixteen(res_length);
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string lshift(string str, int len) {//实现循环左移len位功能
	string res = sixteenTOtwo(str);
	res = res.substr(len) + res.substr(0, len);
	return twoTOsixteen(res);
}

//优化：循环展开（4）+常量只计算一次（临时变量存储）
string yihuo(string str1, string str2) {//实现异或操作
	string res1 = sixteenTOtwo(str1);
	string res2 = sixteenTOtwo(str2);
	string res = "";
	int tmp = res1.size();
	for (int i = 0; i < tmp; i+=4) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+1] == res2[i+1]) {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+2] == res2[i+2]) {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+3] == res2[i+3]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return twoTOsixteen(res);
}

//优化：循环展开（4）+常量只计算一次（临时变量存储）
string yu(string str1, string str2) {//实现与操作
	string res1 = sixteenTOtwo(str1);
	string res2 = sixteenTOtwo(str2);
	string res = "";
	int tmp = res1.size();
	for (int i = 0; i < tmp; i+=4) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+1] == '1' && res2[i+1] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+2] == '1' && res2[i+2] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+3] == '1' && res2[i+3] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return twoTOsixteen(res);
}

//优化：循环展开（4）+常量只计算一次（临时变量存储）
string huo(string str1, string str2) {//实现或操作
	string res1 = sixteenTOtwo(str1);
	string res2 = sixteenTOtwo(str2);
	string res = "";
	int tmp= res1.size();
	for (int i = 0; i < tmp; i+=4) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+1] == '0' && res2[i+1] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+2] == '0' && res2[i+2] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
		if (res1[i+3] == '0' && res2[i+3] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return twoTOsixteen(res);
}

//优化：循环展开（4）+常量只计算一次（临时变量存储）
string fei(string str) {//实现非操作
	string res1 = sixteenTOtwo(str);
	string res = "";
	int tmp= res1.size();
	for (int i = 0; i < tmp; i+=4) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+1] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+2] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
		if (res1[i+3] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return twoTOsixteen(res);
}

char binyihuo(char str1, char str2) {//实现单比特的异或操作
	return str1 == str2 ? '0' : '1';
}

char binyu(char str1, char str2) {//实现单比特的与操作
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

//优化：常量只计算一次（临时变量存储）
string mo(string str1, string str2) {//mod 2^32运算的函数实现
	string res1 = sixteenTOtwo(str1);
	string res2 = sixteenTOtwo(str2);
	char temp = '0';
	string res = "";
	int tmp = res1.size() - 1;
	for (int i = tmp; i >= 0; i--) {
		res = binyihuo(binyihuo(res1[i], res2[i]), temp) + res;
		if (binyu(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binyihuo(res1[i], res2[i]) == '1') {
				temp = binyu('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return twoTOsixteen(res);
}

string P1(string str) {//实现置换功能P1（X）
	return yihuo(yihuo(str, lshift(str, 15)), lshift(str, 23));
}

string P0(string str) {//实现置换功能P0（X）
	return yihuo(yihuo(str, lshift(str, 9)), lshift(str, 17));
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
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return huo(huo(yu(str1, str2), yu(str1, str3)), yu(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//实现布尔函数GG功能
	if (0 <= j && j <= 15) {
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return huo(yu(str1, str2), yu(fei(str1), str3));
	}
}

//优化：循环展开（4）
string ex(string str) {//消息扩展函数
	string res = str;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i+=4) {//根据公式生成第17位到第68位的W值
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), lshift(res.substr((i - 3) * 8, 8), 15))), lshift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 15) * 8, 8), res.substr((i - 8) * 8, 8)), lshift(res.substr((i - 2) * 8, 8), 15))), lshift(res.substr((i - 12) * 8, 8), 7)), res.substr((i - 5) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 14) * 8, 8), res.substr((i - 7) * 8, 8)), lshift(res.substr((i - 1) * 8, 8), 15))), lshift(res.substr((i - 11) * 8, 8), 7)), res.substr((i - 4) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 13) * 8, 8), res.substr((i - 6) * 8, 8)), lshift(res.substr((i ) * 8, 8), 15))), lshift(res.substr((i - 10) * 8, 8), 7)), res.substr((i - 3) * 8, 8));
	}
	
	for (int i = 0; i < 64; i+=4) {//根据公式生成64位W'值
		res += yihuo(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
		res += yihuo(res.substr((i+1) * 8, 8), res.substr((i + 5) * 8, 8));
		res += yihuo(res.substr((i+2) * 8, 8), res.substr((i + 6) * 8, 8));
		res += yihuo(res.substr((i+3) * 8, 8), res.substr((i + 7) * 8, 8));
	}
	
	return res;
}

//优化：循环展开（4）
string comp(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	
	for (int j = 0; j < 64; j+=4) {
		SS1 = lshift(mo(mo(lshift(A, 12), E), lshift(T(j), (j % 32))), 7);
		SS2 = yihuo(SS1, lshift(A, 12));
		TT1 = mo(mo(mo(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = mo(mo(mo(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = lshift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = lshift(F, 19);
		F = E;
		E = P0(TT2);

		SS1 = lshift(mo(mo(lshift(A, 12), E), lshift(T(j+1), ((j+1) % 32))), 7);
		SS2 = yihuo(SS1, lshift(A, 12));
		TT1 = mo(mo(mo(FF(A, B, C, j+1), D), SS2), str1.substr((j + 69) * 8, 8));
		TT2 = mo(mo(mo(GG(E, F, G, j+1), H), SS1), str1.substr((j+1) * 8, 8));
		D = C;
		C = lshift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = lshift(F, 19);
		F = E;
		E = P0(TT2);

		SS1 = lshift(mo(mo(lshift(A, 12), E), lshift(T(j+2), ((j+2) % 32))), 7);
		SS2 = yihuo(SS1, lshift(A, 12));
		TT1 = mo(mo(mo(FF(A, B, C, j+2), D), SS2), str1.substr((j + 70) * 8, 8));
		TT2 = mo(mo(mo(GG(E, F, G, j+2), H), SS1), str1.substr((j+2) * 8, 8));
		D = C;
		C = lshift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = lshift(F, 19);
		F = E;
		E = P0(TT2);

		SS1 = lshift(mo(mo(lshift(A, 12), E), lshift(T(j+3), ((j+3) % 32))), 7);
		SS2 = yihuo(SS1, lshift(A, 12));
		TT1 = mo(mo(mo(FF(A, B, C, j+3), D), SS2), str1.substr((j + 71) * 8, 8));
		TT2 = mo(mo(mo(GG(E, F, G, j+3), H), SS1), str1.substr((j+3) * 8, 8));
		D = C;
		C = lshift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = lshift(F, 19);
		F = E;
		E = P0(TT2);
		
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string diedai(string str) {//迭代压缩函数实现
	int num = str.size() / 128;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		B = str.substr(i * 128, 128);
		extensionB = ex(B);
		compressB = comp(extensionB, V);
		V = yihuo(V, compressB);
	}
	return V;
}

int main() {//主函数
	long beginTime = clock();
	string str = "PracticalCourseProjectNameBianXuQiong";
	string res = "";
	for (int i = 0; i < str.size(); i++) {//首先将输入值转换为16进制字符串
		res += tenTOsixteen((int)str[i]);
	}
	string value1 = pad(res);
	string result = diedai(value1);
	long endTime = clock();
	std::cout << "endTime-beginTime:" << ((double)(endTime - beginTime)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "杂凑值：" << endl;
	for (int i = 0; i < 8; i++) {
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;
	cout << endl;
}

