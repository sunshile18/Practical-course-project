#include<iostream>
#include<cstdlib>
#include <string>
#include <ctime>
#include <cmath>
#include "openssl/sha.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/ec.h>


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



int en_sm2(string a1, unsigned char* b1, int c1, unsigned char* d1)
{
	EVP_PKEY_CTX* c = NULL;
	BIO* a = NULL;
	size_t l1;
	EVP_PKEY* b = NULL;
	char* d = NULL;
	char* e = const_cast<char*>(a1.c_str());
	if ((a = BIO_new_mem_buf(e, -1)) == NULL)
	{
		cout << "fail!" << endl;
		return NULL;
	}
	b = PEM_read_bio_PUBKEY(a, NULL, NULL, NULL);
	BIO_free_all(a);
	if ((EVP_PKEY_set_alias_type(b, EVP_PKEY_SM2)) != 1)
	{
		goto clean_up;
	}

	if (!(c = EVP_PKEY_CTX_new(b, NULL)))
	{
		goto clean_up;
	}

	if ((EVP_PKEY_encrypt_init(c)) != 1)
	{
		goto clean_up;
	}

	if ((EVP_PKEY_encrypt(c, NULL, &l1, reinterpret_cast<unsigned char*>(b1), (size_t)(c1))) != 1)
	{
		goto clean_up;
	}
	if (!(d = (char*)malloc(l1)))
	{
		goto clean_up;
	}

	if ((EVP_PKEY_encrypt(c, reinterpret_cast<unsigned char*>(d), &l1, reinterpret_cast<unsigned char*>(b1), c1)) != 1)
	{
		goto clean_up;
	}

	memcpy(d1, d, l1);
	return (int)(l1);

clean_up:

	if (b)
	{
		EVP_PKEY_free(b);
	}
	if (c)
	{
		EVP_PKEY_CTX_free(c);
	}

	if (b1)
	{
		free(b1);
	}

	if (d)
	{
		free(d);
	}
}

int de_sm2(string a1, unsigned char* d, int l1, unsigned char* d2)

{
	EVP_PKEY_CTX* c = NULL;
	BIO* aa = NULL;
	size_t l2 = 0;
	EVP_PKEY* bb;
	string temp;
	char* dd = NULL;

	//create pri key
	char* ee = const_cast<char*>(temp.c_str());
	if ((aa = BIO_new_mem_buf(ee, -1)) == NULL)
	{
		cout << "fail!" << endl;
	}
	bb = PEM_read_bio_PrivateKey(aa, NULL, NULL, NULL);
	BIO_free_all(aa);
	if (NULL == bb)
	{
		ERR_load_crypto_strings();
		char buf[512];
		ERR_error_string_n(ERR_get_error(), buf, sizeof(buf));
		cout << "fail!" << endl;
	}
	//����
	if ((EVP_PKEY_set_alias_type(bb, EVP_PKEY_SM2)) != 1)
	{
		cout << "fail!" << endl;
	}

	if (!(c = EVP_PKEY_CTX_new(bb, NULL)))
	{
		cout << "fail!" << endl;
	}
	if ((EVP_PKEY_decrypt_init(c)) != 1)
	{
		cout << "fail!" << endl;
	}
	if ((EVP_PKEY_decrypt(c, NULL, &l2, reinterpret_cast<unsigned char*>(d), l1)) != 1)
	{
		cout << "fail!" << endl;

	}
	if (!(dd = (char*)malloc(l2)))
	{
		cout << "fail!" << endl;
	}
	if ((EVP_PKEY_decrypt(c, reinterpret_cast<unsigned char*>(dd), &l2, reinterpret_cast<unsigned char*>(d), l1)) != 1)
	{
		cout << "fail!" << endl;
	}

	memcpy(d2, dd, l2);
	EVP_PKEY_CTX_free(c);
	free(dd);
	return l2;
}

//PGP�����㷨
void PGP_en(string  pk2,unsigned char *m,int len)
{
	unsigned char s1[512];
	int ll;
	//�Ự��Կ����
	string k;
	int len2 = k.length();
	//ʹ�ý��շ��Ĺ�Կ�ԻỰ��Կ���ܣ����������1
	unsigned char* mm = new unsigned char[len2];
	for (int i = 0; i < len2; i++)
	{
		mm[i] = k[i];
	}
	for (int i = 64; i < pk2.size(); i += 64)
	{
		if (pk2[i] != '\n')
		{
			pk2.insert(i, "\n");
		}
		++i;
	}
	ll = en_sm2(pk2, mm, len2, s1);
	for (int i = 0; i < ll; i++)
	{
		cout << s1[i];
	}
	cout << endl;

    //ʹ�ûỰ��Կ������Ϣ���ܣ����������2
	unsigned char s2[512];
	for (int i = 64; i < k.size(); i += 64)
	{
		if (k[i] != '\n')
		{
			k.insert(i, "\n");
		}
		++i;
	}
	ll = en_sm2(k, m, len, s2);
	for (int i = 0; i < ll; i++)
	{
		cout << s2[i];
	}
	cout << endl;
}

//PGP�����㷨
void PGP_de(string sk2, unsigned char* c1, int len1, unsigned char* c2, int len2 )
{
	unsigned char s1[512];
	int ll;

	//ʹ�ý��շ���˽Կ��������1���ܣ����������1�����Ự��Կ��
	for (int i = 64; i < sk2.size(); i += 64)
	{
		if (sk2[i] != '\n')
		{
			sk2.insert(i, "\n");
		}
		++i;
	}
	ll = de_sm2(sk2,c1, len1, s1);
	for (int i = 0; i < ll; i++)
	{
		cout << s1[i];
	}
	cout << endl;
	
	//ʹ�ûỰ��Կ��������2���ܣ����������2������Ϣ��
	unsigned char s2[512];
	string k = "";
	for (int i = 0; i < 512; i++)
	{
		k += s1[i];
	}
	for (int i = 64; i < k.size(); i += 64)
	{
		if (k[i] != '\n')
		{
			k.insert(i, "\n");
		}
		++i;
	}
	ll = de_sm2(k, c2, len2, s2);
	for (int i = 0; i < ll; i++)
	{
		cout << s2[i];
	}
	cout << endl;
	
}

int main()
{
	//AB˫�����и��ԵĹ�˽Կ��������Կ������˽Կ
	string sk1,sk2;//˽Կ����
	string pk1, pk2;//��Կ����
	

	//PGP�����㷨������㷨������غ�������

	system("pause");
	return 0;
}

