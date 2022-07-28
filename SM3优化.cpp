#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

//������ת��Ϊʮ�����ƺ���ʵ��
string twoTOsixteen(string str) {
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//�жϳ�4λ����������ʮ���ƴ�СΪ����
		if (temp < 10) {//���õ���ֵС��10ʱ������ֱ����0-9������
			hex += to_string(temp);
		}
		else {//���õ���ֵ����10ʱ����Ҫ����A-F��ת��
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
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

//������ת��Ϊʮ���Ƶĺ���ʵ��
//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
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

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string tenTOtwo(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
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

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
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

string pad(string res) {//�����ݽ������ 
	
	
	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
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

string lshift(string str, int len) {//ʵ��ѭ������lenλ����
	string res = sixteenTOtwo(str);
	res = res.substr(len) + res.substr(0, len);
	return twoTOsixteen(res);
}

//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
string yihuo(string str1, string str2) {//ʵ��������
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

//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
string yu(string str1, string str2) {//ʵ�������
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

//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
string huo(string str1, string str2) {//ʵ�ֻ����
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

//�Ż���ѭ��չ����4��+����ֻ����һ�Σ���ʱ�����洢��
string fei(string str) {//ʵ�ַǲ���
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

char binyihuo(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binyu(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

//�Ż�������ֻ����һ�Σ���ʱ�����洢��
string mo(string str1, string str2) {//mod 2^32����ĺ���ʵ��
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

string P1(string str) {//ʵ���û�����P1��X��
	return yihuo(yihuo(str, lshift(str, 15)), lshift(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return yihuo(yihuo(str, lshift(str, 9)), lshift(str, 17));
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
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return huo(huo(yu(str1, str2), yu(str1, str3)), yu(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//ʵ�ֲ�������GG����
	if (0 <= j && j <= 15) {
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return huo(yu(str1, str2), yu(fei(str1), str3));
	}
}

//�Ż���ѭ��չ����4��
string ex(string str) {//��Ϣ��չ����
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i+=4) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), lshift(res.substr((i - 3) * 8, 8), 15))), lshift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 15) * 8, 8), res.substr((i - 8) * 8, 8)), lshift(res.substr((i - 2) * 8, 8), 15))), lshift(res.substr((i - 12) * 8, 8), 7)), res.substr((i - 5) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 14) * 8, 8), res.substr((i - 7) * 8, 8)), lshift(res.substr((i - 1) * 8, 8), 15))), lshift(res.substr((i - 11) * 8, 8), 7)), res.substr((i - 4) * 8, 8));
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 13) * 8, 8), res.substr((i - 6) * 8, 8)), lshift(res.substr((i ) * 8, 8), 15))), lshift(res.substr((i - 10) * 8, 8), 7)), res.substr((i - 3) * 8, 8));
	}
	
	for (int i = 0; i < 64; i+=4) {//���ݹ�ʽ����64λW'ֵ
		res += yihuo(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
		res += yihuo(res.substr((i+1) * 8, 8), res.substr((i + 5) * 8, 8));
		res += yihuo(res.substr((i+2) * 8, 8), res.substr((i + 6) * 8, 8));
		res += yihuo(res.substr((i+3) * 8, 8), res.substr((i + 7) * 8, 8));
	}
	
	return res;
}

//�Ż���ѭ��չ����4��
string comp(string str1, string str2) {//��Ϣѹ������
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

string diedai(string str) {//����ѹ������ʵ��
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

int main() {//������
	long beginTime = clock();
	string str = "PracticalCourseProjectNameBianXuQiong";
	string res = "";
	for (int i = 0; i < str.size(); i++) {//���Ƚ�����ֵת��Ϊ16�����ַ���
		res += tenTOsixteen((int)str[i]);
	}
	string value1 = pad(res);
	string result = diedai(value1);
	long endTime = clock();
	std::cout << "endTime-beginTime:" << ((double)(endTime - beginTime)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "�Ӵ�ֵ��" << endl;
	for (int i = 0; i < 8; i++) {
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;
	cout << endl;
}

