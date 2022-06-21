#include "openssl/sha.h"
#include<cstdlib>
#include<iostream>
#include<string>

using namespace std;
#define MAX_QUEUE_SIZE 200
//定义二叉树结构
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

//循环队列基本操作
//初始化队列
SqQueue* Init_CirQueue()
{
	SqQueue* Q = (SqQueue*)malloc(sizeof(SqQueue));
	if (!Q)
		exit(0);
	Q->front = Q->rear = 0;
	return(Q);
}
SqQueue Q;

//判断队列是否为空
bool IsEmpty_Queue(SqQueue& Q)
{
	if (Q.front == Q.rear)
		return 1;       /*  队列空，返回失败标志  */
	return 0;
}
//判断队列是否已满
bool IsFull_Queue(SqQueue& Q)
{
	if ((Q.rear + 1) % MAX_QUEUE_SIZE == Q.front)	/*  队满*/
		return 1;
	return 0;
}
//统计队列中元素个数
int Size_Queue(SqQueue& Q)
{
	return (Q.rear + MAX_QUEUE_SIZE - Q.front) % MAX_QUEUE_SIZE;
}
//往队列中插入元素
bool Push(SqQueue& Q, BiTNode& e)
/*  将数据元素e插入到循环队列Q的队尾  */
{
	if (IsFull_Queue(Q))	/*  队满*/
	{
		printf("Insert: The queue is full.\n");
		return 1;
	}
	memset(Q.array[Q.rear].data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		Q.array[Q.rear].data[i] = e.data[i];

	}
	/*  元素e入队  */
	Q.array[Q.rear].lChild = e.lChild;
	Q.array[Q.rear].rChild = e.rChild;
	Q.rear = (Q.rear + 1) % MAX_QUEUE_SIZE;
	/*  队尾指针向前移动  */
	return 0;        /*  入队成功    */
}
//取队首元素
BiTNode* Pop(SqQueue& Q)
/*  将循环队列Q的队首元素出队  */
{
	if (IsEmpty_Queue(Q))	/*  队空，返回错误标志    */
	{
		printf("The queue is empty.\n");
		/*  队列空，返回失败标志  */
	}
	BiTNode* x = (BiTNode*)malloc(sizeof(BiTNode));
	memset(x->data, 0, 65);
	for (int i = 0; i < 64; i++)
	{
		x->data[i] = Q.array[Q.front].data[i];
	}
	/*  取栈顶元素  */
	x->lChild = Q.array[Q.front].lChild;
	x->rChild = Q.array[Q.front].rChild;
	Q.front = (Q.front + 1) % MAX_QUEUE_SIZE;
	/*  队首指针向前移动  */
	return x;

}
//先序创建二叉树
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

//先序遍历二叉树
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
	cout << "叶子节点的个数为:" << endl;
	cin >> numleaf;

	cout << "请依次输入叶子节点的数据：" << endl;
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

	//建立merkle树

	cout << "建立merkle树" << endl;

	CreateBiTree();
	BiTNode* root = Pop(Q);
	printf("先序遍历merkle树:\n");
	TraverseBiTree(root);
	printf("\n");

	cout << "树根为：" << endl;
	cout << root->data << endl;

	system("pause");
	return 0;
}
