#include "openssl/sha.h"
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define MAX_QUEUE_SIZE 200
//����������ṹ
typedef struct BiTNode {
	char data[65];
	BiTNode* lChild = NULL;
	BiTNode* rChild = NULL;

};
BiTNode list[MAX_QUEUE_SIZE];
int number = 0;
typedef struct queue
{
	BiTNode array[MAX_QUEUE_SIZE];
	int front;
	int rear;
}SqQueue;

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

string transf(unsigned char* md) {
	string result = "";
	for (int i = 0; i < 32; i++)
	{
		result += ten_sixteen((int)md[i]);
	}
	return result;
}

//ѭ�����л�������
//��ʼ������
SqQueue* Init_CirQueue()
{
	SqQueue* Q = (SqQueue*)malloc(sizeof(SqQueue));
	if (!Q)
		exit(0);
	Q->front = Q->rear = 0;
	return(Q);
}

SqQueue Q;//�洢���ڵ�
SqQueue Q1;//������֤�����õ��Ķ���
SqQueue Q2; //��������֤�����õ��Ķ���


//�ж϶����Ƿ�Ϊ��
bool IsEmpty_Queue(SqQueue& Q)
{
	if (Q.front == Q.rear)
		return 1;       /*  ���пգ�����ʧ�ܱ�־  */
	return 0;
}
//�ж϶����Ƿ�����
bool IsFull_Queue(SqQueue& Q)
{
	if ((Q.rear + 1) % MAX_QUEUE_SIZE == Q.front)	/*  ����*/
		return 1;
	return 0;
}
//ͳ�ƶ�����Ԫ�ظ���
int Size_Queue(SqQueue& Q)
{
	return (Q.rear + MAX_QUEUE_SIZE - Q.front) % MAX_QUEUE_SIZE;
}
//�������в���Ԫ��
bool Push(SqQueue& Q, BiTNode& e)
/*  ������Ԫ��e���뵽ѭ������Q�Ķ�β  */
{
	if (IsFull_Queue(Q))	/*  ����*/
	{
		printf("Insert: The queue is full.\n");
		return 1;
	}
	memset(Q.array[Q.rear].data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		Q.array[Q.rear].data[i] = e.data[i];

	}
 /*  Ԫ��e���  */
	Q.array[Q.rear].lChild = e.lChild;
	Q.array[Q.rear].rChild = e.rChild;
	Q.rear = (Q.rear + 1) % MAX_QUEUE_SIZE;
	/*  ��βָ����ǰ�ƶ�  */
	return 0;        /*  ��ӳɹ�    */
}
//ȡ����Ԫ��
BiTNode* Pop(SqQueue& Q)
/*  ��ѭ������Q�Ķ���Ԫ�س���  */
{
	if (IsEmpty_Queue(Q))	/*  �ӿգ����ش����־    */
	{
		printf("The queue is empty.\n");
		/*  ���пգ�����ʧ�ܱ�־  */
	}
	BiTNode* x = (BiTNode*)malloc(sizeof(BiTNode));
	memset(x->data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		x->data[i] = Q.array[Q.front].data[i];
	}
	 /*  ȡջ��Ԫ��  */
	x->lChild = Q.array[Q.front].lChild;
	x->rChild = Q.array[Q.front].rChild;
	Q.front = (Q.front + 1) % MAX_QUEUE_SIZE;
	/*  ����ָ����ǰ�ƶ�  */
	return x;

}
//���򴴽�������
void CreateBiTree()
{
	if (!IsEmpty_Queue(Q))
	{
		BiTNode* x = Pop(Q);
		if (!IsEmpty_Queue(Q))
		{
			BiTNode* y = Pop(Q);
			string a = x->data;
			string b = y->data;
			string s = (string)a + (string)b;
			unsigned char md[33];
			memset(md, 0, 33);
			
			unsigned char* p = SHA256(SHA256((const unsigned char*)s.c_str(), s.length(), md), 32, md);
			BiTNode* d = &list[number];
			number++;
			string c = transf(md);
			memset(d->data, 0, 65);
			for (int i = 0; i < 64; i++)
			{
				d->data[i] = c.c_str()[i];
			}
			d->lChild = x;
			d->rChild = y;
			Push(Q, *d);
			CreateBiTree();
		}
		else
		{
			Push(Q, *x);
			return;
		}
	}


}

//�������������
void TraverseBiTree(BiTNode* T)
{
	if (T == NULL)return;

	cout << T->data << endl;

	TraverseBiTree(T->lChild);
	TraverseBiTree(T->rChild);
}

//������֤��
string Existence(string datatest, string ma)
{
	unsigned char md[33];
	memset(md, 0, 33);
	unsigned char* p = SHA256(SHA256((const unsigned char*)datatest.c_str(), datatest.length(), md), 32, md);
	BiTNode* d = &list[number];
	number++;
	d->lChild = NULL;
	d->rChild = NULL;
	string c = transf(md);
	memset(d->data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		d->data[i] = c.c_str()[i];
	}

	Push(Q1, *d);

	cout << "������������֤�����֤�ݣ�" << endl;
	int number_of_empty_res = 0;
	vector<string> myvec;
	string aa;
	while (getline(cin, aa))
	{
		if (aa.empty()) {
			number_of_empty_res += 1;
			if (number_of_empty_res > 2)
			{
				break;
			}
		}
		else
		{
			number_of_empty_res = 0;
			myvec.push_back(aa + ' ');
		}

	}

	for (int j = 0; j < myvec.size(); j++)
	{

		d = &list[number];
		number++;
		memset(d->data, 0, 65);
		for (int i = 0; i < 64; i++)
		{
			d->data[i] = myvec[j].c_str()[i];
		}
		d->lChild = NULL;
		d->rChild = NULL;
		Push(Q1, *d);

	}
	BiTNode* x = Pop(Q1);
	string a = x->data;
	int len = ma.length()-1;
	while (!IsEmpty_Queue(Q1))
	{
		BiTNode* y = Pop(Q1);
		string b = y->data;
		string s;
		if (ma.c_str()[len] == '0')
		{
			s = a + b;
		}
		else
		{
			s = b+a;
		}
		len--;
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256(SHA256((const unsigned char*)s.c_str(), s.length(), md), 32, md);
		a = transf(md);
	}
	return a;
}
string Nonexistence(string datatest,string ma)
{
	unsigned char md[33];
	memset(md, 0, 33);
	unsigned char* p = SHA256(SHA256((const unsigned char*)datatest.c_str(), datatest.length(), md), 32, md);
	number = 0;
	BiTNode* d = &list[number];
	number++;
	d->lChild = NULL;
	d->rChild = NULL;
	string c = transf(md);
	memset(d->data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		d->data[i] = c.c_str()[i];
	}

	Push(Q2, *d);

	cout << "������������֤�����֤�ݣ�" << endl;
	int number_of_empty_res = 0;
	vector<string> myvec;
	string aa;
	while (getline(cin, aa))
	{
		if (aa.empty()) {
			number_of_empty_res += 1;
			if (number_of_empty_res > 2)
			{
				break;
			}
		}
		else
		{
			number_of_empty_res = 0;
			myvec.push_back(aa + ' ');
		}

	}

	for (int j = 0; j < myvec.size(); j++)
	{

		d = &list[number];
		number++;
		memset(d->data, 0, 65);
		for (int i = 0; i < 64; i++)
		{
			d->data[i] = myvec[j].c_str()[i];
		}
		d->lChild = NULL;
		d->rChild = NULL;
		Push(Q2, *d);

	}

	BiTNode* x = Pop(Q2);
	string a = x->data;
	int len = ma.length() - 1;
	while (!IsEmpty_Queue(Q2))
	{
		BiTNode* y = Pop(Q2);
		string b = y->data;
		string s;
		if (ma.c_str()[len] == '0')
		{
			s = a + b;
		}
		else
		{
			s = b + a;
		}
		len--;
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256(SHA256((const unsigned char*)s.c_str(), s.length(), md), 32, md);
		a = transf(md);
	}
	return a;
}

int main()
{
	int numleaf;
	cout << "Ҷ�ӽڵ�ĸ���Ϊ:" << endl;
	cin >> numleaf;
	string* strdata = new string[numleaf];
	cout << "����������Ҷ�ӽڵ�����ݣ�" << endl;
	for (int i = 0; i < numleaf; i++)
	{
		string a;
		cin >> a;
		strdata[i] = a;
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256 (SHA256((const unsigned char*)a.c_str(), a.length(), md),32,md);
		
		BiTNode* d = &list[number];
		number++;
		d->lChild = NULL;
		d->rChild = NULL;
		string c = transf(md);
		memset(d->data, 0, 65);
		for (int i = 0; i < 64; i++)
		{
			d->data[i] = c.c_str()[i];
		}

		Push(Q, *d);
		
	}

	//����merkle��

	cout << "����merkle��" << endl;

	CreateBiTree();
	BiTNode* root = Pop(Q);
	printf("�������merkle��:\n");
	TraverseBiTree(root);
	printf("\n");

	cout << "��merkle��������Ϊ��" << endl;
	string root0 = root->data;
	cout << root->data << endl;

	//********************************************************
	
	cout << "Ҫ��֤�����ԵĽ��ԭֵΪ��" << endl;
	number = 0;
	string aa;
	cin >> aa;
	cout << "�ý���λ�ñ���Ϊ��" << endl;
	string ma;
	cin>>ma;

	string root1=Existence(aa,ma);
	cout << "������֤�����������Ϊ��" << endl;
	cout << root1.c_str() << endl;
	if (root0 == root1)
	{
		cout<<"�˽������ڴ�Merkle���С�" << endl;
	}
	
	//*****************************************************
	cout << "Ҫ��֤�������ԵĽ��ԭֵΪ��" << endl;
	
	string a;
	cin >> a;
	string* strdata1 = new string[numleaf];
	string* strdata2 = new string[numleaf];
	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < numleaf; i++)
	{
		string temp = strdata[i];
		if (temp < a)
		{
			strdata1 [n1] = temp;
			n1++;
		}
		else if(temp>a)
		{
			strdata2[n2] = temp;
			n2++;
		}
	
	}
	string small,big;
	bool o1=1, o2=1;
	if (n1 > 0)
	{
		small = strdata1[0];
		for (int i = 1; i < n1; i++)
		{
			if (strdata1[i] > small)
			{
				small = strdata1[i];
			}
		}
	}
	else
	{
		o1 = 0;
	}
	if (n2 > 0)
	{
		big = strdata2[0];
		for (int i = 1; i < n2; i++)
		{
			if (strdata2[i] > big)
			{
				big = strdata2[i];
			}
		}
	}
	else
	{
		o2 = 0;
	}
	bool final = 0;
	if (o1 ==1 )
	{
		if (o2 == 1)
		{
			cout << "�ȸ�ֵС������ԭֵΪ��" << endl;
			cout<<small<<endl;
			cout << "�ý���λ�ñ���Ϊ��" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(small,ma);
			cout << "������֤�����������Ϊ��" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "�ȸ�ֵС������ֵ�����ڴ�Merkle���С�" << endl;
			}
			//************************************
			cout << "�ȸ�ֵ�����С��ԭֵΪ��" << endl;
			cout << big<< endl;
			cout << "�ý���λ�ñ���Ϊ��" << endl;
			cin >> ma;
			string root2 = Nonexistence(big,ma);
			cout << "������֤�����������Ϊ��" << endl;
			cout << root2.c_str() << endl;
			if (root0 == root2)
			{
				cout << "�ȸ�ֵ�����С��ֵ�����ڴ�Merkle���С�" << endl;
			}
			if (root0 == root2 && root0 == root1)
			{
				final = 1;
			}
			
		}
		else
		{
			cout << "û�бȸ�ֵ���ֵ" << endl;
			cout << "�ȸ�ֵС������ԭֵΪ��" << endl;
			cout << small << endl;
			cout << "�ý���λ�ñ���Ϊ��" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(small,ma);
			cout << "������֤�����������Ϊ��" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "�ȸ�ֵС������ֵ�����ڴ�Merkle���С�" << endl;
				final = 1;
			}
		}
	
	}
	else
	{
		if (o2 == 1)
		{
			cout << "û�бȸ�ֵС��ֵ" << endl;
			cout << "�ȸ�ֵ�����С��ԭֵΪ��" << endl;
			cout << big << endl;
			cout << "�ý���λ�ñ���Ϊ��" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(big,ma);
			cout << "������֤�����������Ϊ��" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "�ȸ�ֵ�����С��ֵ�����ڴ�Merkle���С�" << endl;
				final = 1;
			}
		}
		else
		{
			cout << "û�бȸ�ֵ���С��ֵ" << endl;
		}
	}
	if (final == 1)
	{
		cout<<"Ҫ֤����ԭֵ�������ڴ�Merkle���С�" << endl;
	}
	
	system("pause");
	return 0;
}