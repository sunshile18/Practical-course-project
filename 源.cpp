#include<iostream>
#include<cstdlib>
#include "openssl/sha.h"
#include<string>
using namespace std;

//ѡ����Բ���߲���
int k;
int a;
int b;
int c;
int p;


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
	if (hex.length() == 1)
	{
		hex = "0" + hex;
	}
	return hex;
}

string transftohex(unsigned char* md) {
	string result = "";
	for (int i = 0; i < 32; i++)
	{
		result += ten_sixteen((int)md[i]);
	}
	return result;
}

int transftoint(unsigned char* md) {
	int result=0;
	int sss = 1;
	int max = 2147483647;
	for (int i = 0; i < 32; i++)
	{
		result =(result+ (int)md[i]*sss)%max;
		sss = sss * 10;
	}
	return result ;
}

//��Բ���߿��Ա�ʾΪ��y ^ 2 = x ^ 3 + ax ^ 2 + bx + c
int pointXtoY(int x)
{
	int pp = (x ^ 3 + a * x ^ 2 + b * x + c) % p;
	int y = sqrt(pp);
	return y;
}
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

struct point {
	int x;
	int y;
};

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

//����Ϣ���ַ�����ӳ�䵽��Բ�����ϵĵ㲢����
point hashTOpoint(string m)
{
	unsigned char md[33];
	memset(md, 0, 33);
	unsigned char* ptr = SHA256((const unsigned char*)m.c_str(), m.length(), md);
	int xx = transftoint(md);
	int yy = pointXtoY(xx);
	point PP;
	PP.x = xx;
	PP.y = yy;
	return PP;
}


//�󼯺ϵ�Hashֵ
//������������ѡ����Բ����Ϊ������Ⱥ,������Բ�����ϵļӷ���������������:a+b=b+a
//��˿���ʹ�����κ�˳������ļ���ֵ���䣨ֻҪ���ϵ�Ԫ�ز��䣩
point MultisetHash(string* set, int n)
{
	point re = hashTOpoint(set[0]);
	for (int i = 1; i < n; i++)
	{
		re = re + hashTOpoint(set[i]);
	}
	return re;
}