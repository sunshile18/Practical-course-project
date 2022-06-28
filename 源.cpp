#include "openssl/sha.h"
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
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

SqQueue Q;//存储树节点
SqQueue Q1;//存在性证明中用到的队列
SqQueue Q2; //不存在性证明中用到的队列


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

//存在性证明
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

	cout << "请依次输入验证所需的证据：" << endl;
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

	cout << "请依次输入验证所需的证据：" << endl;
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
	cout << "叶子节点的个数为:" << endl;
	cin >> numleaf;
	string* strdata = new string[numleaf];
	cout << "请依次输入叶子节点的数据：" << endl;
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

	//建立merkle树

	cout << "建立merkle树" << endl;

	CreateBiTree();
	BiTNode* root = Pop(Q);
	printf("先序遍历merkle树:\n");
	TraverseBiTree(root);
	printf("\n");

	cout << "该merkle树的树根为：" << endl;
	string root0 = root->data;
	cout << root->data << endl;

	//********************************************************
	
	cout << "要验证存在性的结点原值为：" << endl;
	number = 0;
	string aa;
	cin >> aa;
	cout << "该结点的位置编码为：" << endl;
	string ma;
	cin>>ma;

	string root1=Existence(aa,ma);
	cout << "存在性证明计算的树根为：" << endl;
	cout << root1.c_str() << endl;
	if (root0 == root1)
	{
		cout<<"此结点存在于此Merkle树中。" << endl;
	}
	
	//*****************************************************
	cout << "要验证不存在性的结点原值为：" << endl;
	
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
			cout << "比该值小的最大的原值为：" << endl;
			cout<<small<<endl;
			cout << "该结点的位置编码为：" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(small,ma);
			cout << "存在性证明计算的树根为：" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "比该值小的最大的值存在于此Merkle树中。" << endl;
			}
			//************************************
			cout << "比该值大的最小的原值为：" << endl;
			cout << big<< endl;
			cout << "该结点的位置编码为：" << endl;
			cin >> ma;
			string root2 = Nonexistence(big,ma);
			cout << "存在性证明计算的树根为：" << endl;
			cout << root2.c_str() << endl;
			if (root0 == root2)
			{
				cout << "比该值大的最小的值存在于此Merkle树中。" << endl;
			}
			if (root0 == root2 && root0 == root1)
			{
				final = 1;
			}
			
		}
		else
		{
			cout << "没有比该值大的值" << endl;
			cout << "比该值小的最大的原值为：" << endl;
			cout << small << endl;
			cout << "该结点的位置编码为：" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(small,ma);
			cout << "存在性证明计算的树根为：" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "比该值小的最大的值存在于此Merkle树中。" << endl;
				final = 1;
			}
		}
	
	}
	else
	{
		if (o2 == 1)
		{
			cout << "没有比该值小的值" << endl;
			cout << "比该值大的最小的原值为：" << endl;
			cout << big << endl;
			cout << "该结点的位置编码为：" << endl;
			string ma;
			cin >> ma;
			string root1 = Nonexistence(big,ma);
			cout << "存在性证明计算的树根为：" << endl;
			cout << root1.c_str() << endl;
			if (root0 == root1)
			{
				cout << "比该值大的最小的值存在于此Merkle树中。" << endl;
				final = 1;
			}
		}
		else
		{
			cout << "没有比该值大或小的值" << endl;
		}
	}
	if (final == 1)
	{
		cout<<"要证明的原值不存在于此Merkle树中。" << endl;
	}
	
	system("pause");
	return 0;
}