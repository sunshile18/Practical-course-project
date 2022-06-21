#include "openssl/sha.h"
#include<cstdlib>
#include<iostream>
#include<string>

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
SqQueue Q;

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



int main()
{
	int numleaf;
	cout << "Ҷ�ӽڵ�ĸ���Ϊ:" << endl;
	cin >> numleaf;

	cout << "����������Ҷ�ӽڵ�����ݣ�" << endl;
	for (int i = 0; i < numleaf; i++)
	{
		string a;
		cin >> a;
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256(SHA256((const unsigned char*)a.c_str(), a.length(), md), 32, md);

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

	cout << "����Ϊ��" << endl;
	cout << root->data << endl;

	system("pause");
	return 0;
}