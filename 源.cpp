#include<iostream>
#include<cstdlib>
#include <string>
#include <ctime>


using namespace std;
//ѡ����Բ���߲���
int k ;
int a ;
int b ;
int p ;
int r ;


//��˷���Ԫ
int getX_1(int x, int mod) {
	int Q, X1, X2, X3, Y1, Y2, Y3, T1, T2, T3;
	X1 = 1;
	X2 = 0;
	X3 = mod;
	Y1 = 0;
	Y2 = 1;
	Y3 = (x % mod + mod) % mod;
	while (Y3 != 1) {
		Q = X3 / Y3;
		T1 = X1 - Q * Y1;
		T2 = X2 - Q * Y2;
		T3 = X3 - Q * Y3;
		X1 = Y1;
		X2 = Y2;
		X3 = Y3;
		Y1 = T1;
		Y2 = T2;
		Y3 = T3;
	}
	return Y2;
}

//��Ľṹ��
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

//ECDSA��ǩ��α�캯��
void forge(point pk, int n, point G)
{
	const int max = 30;//�����߿��Զ��巶Χ
	srand(time(NULL));
	int u=rand() % max;
	int v = rand()% max;
	point R =  G*u +  pk*v;
	int rn = R.x % n;
	int v_1 = getX_1(v, n);
	int sn = (rn * v_1) % n;
	int en = (rn * u * v_1) % n;
	cout << "���������û��Ĺ�ԿΪ��(" << pk.x<<","<<pk.y<<")" << endl;
	cout << "α�����Ϣ�Ĺ�ϣֵeΪ��" << en << endl;
	cout << "α��ĺϷ���ǩΪ��r,s��:(" << rn << "," << sn << ")" << endl;

}
