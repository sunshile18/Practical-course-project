#include "openssl/sha.h"
#include<cstdlib>
#include<iostream>
#include<string>

using namespace std;
//定义二叉树结构
typedef struct BiTNode {
	char* data; 	//数据域struct BiTNode
	BiTNode* lChild, * rChild;	//左右子树域
}*BiTree;

//先序创建二叉树
int CreateBiTree(BiTree* T, string*datashz,int n,int num)
{
	
	if (num > n)
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!(*T))
			exit(-1);
		(*T)->data = (char*)datashz[n].c_str(); 	
		CreateBiTree(&(*T)->lChild, datashz, 2 * n + 1,num);
		CreateBiTree(&(*T)->rChild, datashz, 2 * n + 2,num);
	
	}
	else
	{
		*T = NULL;
	}
	return 1;
}

//先序遍历二叉树
void TraverseBiTree(BiTree T)
{
	if (T == NULL)return;
	cout<< T->data <<endl;

	TraverseBiTree(T->lChild);
	TraverseBiTree(T->rChild);
}

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

string transf(unsigned char*md) {
	string result = "";
	for (int i = 0; i < 32; i++)
	{
		result += ten_sixteen((int)md[i]);
	}
	return result;
}

void sha_com(string* datashz, int n,int num)
{
	string a;
	for (int i = n; i < num; i += 2)
	{
		a = datashz[i] + datashz[i + 1];
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256(SHA256((const unsigned char*)a.c_str(), a.length(), md), 32, md);
		datashz[(i - 1) / 2] = transf(md);
	}
	if (n != 1)
	{
		sha_com(datashz, (n - 1) / 2, n - 1);
	}

}
int main()
{
	int numleaf;
	cout << "叶子节点的个数为:" << endl;
	cin >> numleaf;
	string* datashz = new string[numleaf*2-1];//开辟n长的数组
	cout << "请从左到右输入叶子节点的数据：" << endl;
	//当叶子节点的个数为偶数时
	if (numleaf % 2 == 0)
	{
		for (int i = 0; i < numleaf; i++)
		{
			string a;
			cin >> a;
			unsigned char md[33];
			memset(md, 0, 33);
			unsigned char* p = SHA256(SHA256((const unsigned char*)a.c_str(), a.length(), md), 32, md);
			datashz[numleaf - 1 + i] = transf(md);
			
		}
		int nn = numleaf - 1;
		sha_com(datashz, nn, numleaf*2-2);
	}
	//当叶子节点的个数为奇数时
	else
	{
		for (int i = 0; i < numleaf-1; i++)
		{
			string a;
			cin >> a;
			unsigned char md[33];
			memset(md, 0, 33);
			unsigned char* p = SHA256(SHA256((const unsigned char*)a.c_str(), a.length(), md), 32, md);
			datashz[numleaf +i]= transf(md);
		}
		string a;
		cin >> a;
		unsigned char md[33];
		memset(md, 0, 33);
		unsigned char* p = SHA256(SHA256((const unsigned char*)a.c_str(), a.length(), md), 32, md);
		datashz[numleaf -1] = transf(md);
		int nn = numleaf ;
		sha_com(datashz, nn, numleaf*2-2);
	}
	
	
	//建立merkle树
	BiTree T;
	cout<<"建立merkle树" << endl;
	CreateBiTree(&T,datashz,0,2* numleaf-1);
	printf("先序遍历merkle树:\n");
	TraverseBiTree(T);
	printf("\n");

	cout<<"树根为：" << endl;
	cout<<T->data<<endl;

	system("pause");
	return 0;
}
