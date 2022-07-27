#include<iostream>
#include<cstdlib>
#include <string>
#include <ctime>
#include <cmath>
#include "openssl/sha.h"
#include <tuple>
#include<Winsock2.h>
#include<stdio.h>

using namespace std;
//ѡ����Բ���߲���
int k;
int a;
int b;
int p;
int r;


//��˷���Ԫ
int getX_1(int x, int n) {
	int aa, bb, cc, dd, ee, ff, gg, hh, ii, jj;
	bb = 1;
	cc = 0;
	dd = n;
	ee = 0;
	ff = 1;
	gg = (x % n + n) % n;
	while (gg != 1) {
		aa = dd / gg;
		hh = bb - aa * ee;
		ii = cc - aa * ff;
		jj = dd - aa * gg;
		bb = ee;
		cc = ff;
		dd = gg;
		ee = hh;
		ff = ii;
		gg = jj;
	}
	return ff;
}

//��Ľṹ��
struct point {
	int x;
	int y;
};
point G;
int n;

typedef pair<point, point> twopoint;


//������Բ�����ϵ��жϵ��ڲ���
bool operator == (point pa, point pb)
{
	return pa.x == pb.x && pa.y == pb.y;
}
//������Բ�����ϵļӷ�����
point operator + (point pa, point pb) {
	int k;

	if (pa == pb)
		k = ((3 * pa.x * pa.x + a) * getX_1(2 * pa.y, p)) % p;
	else
		k = (pb.y - pa.y) * getX_1(pb.x - pa.x, p) % p;
	point c;
	c.x = (k * k - pa.x - pb.x) % p;
	c.y = (k * (pa.x - c.x) - pa.y) % p;
	c.x = (c.x + p) % p;
	c.y = (c.y + p) % p;

	return c;
}
//������Բ�����ϵĳ˷�����
point operator * (point& b, int n) {
	point q = b;
	n = n - 1;
	for (int i = 1; i < n; i++) {
		q = q + b;
	}
	return q;
}


//������ת��Ϊʮ�����ƺ���ʵ��
string BinToHex(string str) {
	string hex = "";//�����洢������ɵ�ʮ��������
	int temp = 0;//�����洢ÿ����λ����������ʮ����ֵ
	while (str.size() % 4 != 0) {//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
		str = "0" + str;//���λ��0ֱ������Ϊ4�ı�������
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
string HexToBin(string str) {
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
int BinToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string DecToBin(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
int HexToDec(string str) {
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
string DecToHex(int str) {
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

string padding(string res) {//�����ݽ������ 


	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
	while (res.size() % 128 != 112) {
		res += "0";//��0���������
	}
	string res_len = DecToHex(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) {//ʵ��ѭ������lenλ����
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) {//ʵ��������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) {//ʵ�������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) {//ʵ�ֻ����
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) {//ʵ�ַǲ���
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32����ĺ���ʵ��
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
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
	return BinToHex(res);
}

string P1(string str) {//ʵ���û�����P1��X��
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
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
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}

	for (int i = 0; i < 64; i++) {//���ݹ�ʽ����64λW'ֵ
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}

	return res;
}

string compress(string str1, string str2) {//��Ϣѹ������
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";

	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);

	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
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

int SM3_en(string str)
{
	string res = "";
	for (int i = 0; i < str.size(); i++) {//���Ƚ�����ֵת��Ϊ16�����ַ���
		res += DecToHex((int)str[i]);
	}
	string paddingValue = padding(res);
	string result = iteration(paddingValue);
	int rr = atoi(result.c_str());
	return rr;

}




point cc1(point P1, int n, point G, int d2)
{
	//srand(time(NULL));
	//int d2 = rand() % (n - 1) + 1;//������˽Կ
	int d2_1 = getX_1(d2, n);
	point P;
	P = P1 * d2_1 + (G * -1);//��ԿP
	return P;
}



std::tuple<int, int, int> cc2(std::pair<point, int>result, point G, int n, int d2)
{
	std::tuple<int, int, int> rr;
	srand(time(NULL));
	int k2 = rand() % (n - 1) + 1;
	int k3 = rand() % (n - 1) + 1;
	point Q2, t;
	Q2 = G * k2;
	t = result.first * k3 + Q2;
	int x1 = t.x;
	int y1 = t.y;
	int r = (x1 + result.second) % n;
	int s2 = (d2 * k3) % n;
	int s3 = (d2 * (r + k2)) % n;
	rr = std::make_tuple(r, s2, s3);
	return rr;
}


void main() {
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	//�����׽���
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//�������������������
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//��������
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	string t1 = recvBuf;
	recv(sockClient, recvBuf, 100, 0);
	string t2 = recvBuf;
	point P1;
	P1.x = atoi(t1.c_str());
	P1.y = atoi(t2.c_str());
	srand(time(NULL));
	int d2 = rand() % (n - 1) + 1;//������˽Կ
	point P=cc1(P1, n, G,d2);
	cout << "��ԿΪ��" << endl;
	cout << "P=:(" << P.x << "," << P.y << ")" << endl;
	//��������
	recv(sockClient, recvBuf, 100, 0);
	t1 = recvBuf;
	recv(sockClient, recvBuf, 100, 0);
	t2 = recvBuf;
	recv(sockClient, recvBuf, 100, 0);
	string t3 = recvBuf;
	point Q1;
	Q1.x = atoi(t1.c_str());
	Q1.y = atoi(t2.c_str());
	int e= atoi(t3.c_str());
	std::pair<point, int>result;
	result.first = Q1;
	result.second = e;
	std::tuple<int, int, int>rr;
	rr = cc2(result,  G, n,  d2);
	//��������
	char sendBuf[100];
	int r, s2, s3;
	std::tie(r, s2, s3) = rr;
	t1 = to_string(r);
	t2= to_string(s2);
	t3=to_string(s3);
	int i=0;
	for (i = 0; i < t1.length(); ++i)
	{
		sendBuf[i] = t1[i];
	}

	sendBuf[i] = '\0';
	send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
	for (i = 0; i < t2.length(); ++i)
	{
		sendBuf[i] = t2[i];
	}

	sendBuf[i] = '\0';
	send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
	for (i = 0; i < t3.length(); ++i)
	{
		sendBuf[i] = t3[i];
	}

	sendBuf[i] = '\0';
	send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);

	//�ر��׽���
	closesocket(sockClient);
	WSACleanup();
}


