#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct Node {
	int data;
	struct Node *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct {
	int parent;
	int lchild;
	int rchild;
	int Height;
	int son;
}info;
typedef struct {
	BiTree *elem;
	int front; //指向队头元素 
	int rear; //指向队尾元素后一个位置，数组下标 
	int queuesize;
	int incrementsize;
}SqQueue;

/*	The functions are divided into 3 part
	1.	Operations of queue
	2.	Functions for creating tree
	3.	Postorder and level traversal function
*/
void InitQueue(SqQueue &Q);
void incrementQueuesize(SqQueue &Q);
void EnQueue(SqQueue &Q, BiTree e);
bool EmptyQueue(SqQueue Q);
bool DeQueue(SqQueue &Q, BiTree &e);

bool BiSearchTree(BiTree bt, int kval, BiTree &p, BiTree &pre);
bool BiTree_Insert(BiTree &bt, int kval);

void visite(int data);
int postorder(BiTree bt);
void Traverse(BiTree bt);

info record[800000];

int main()
{
	BiTree bt = NULL;
	int n, i, m, temp;

	scanf("%d", &n);
	for (i = 1; i <= n; i++) {	//	Create Tree
		scanf("%d", &temp);
		BiTree_Insert(bt, temp);
	}
	scanf("%d", &m);

	postorder(bt);	//	postorder traversal
	putchar('\n');
	Traverse(bt);	//	level traversal
	putchar('\n');

	for (i = 1; i <= m; i++) {
		scanf("%d", &temp);
		printf("%d %d %d %d %d\n", record[temp].parent, record[temp].lchild, record[temp].rchild, record[temp].Height, record[temp].son);
	}
	return 0;
}

void InitQueue(SqQueue &Q)
{
	Q.queuesize = 400000;
	Q.elem = (BiTree*)malloc(sizeof(BiTree)*Q.queuesize);
	Q.front = Q.rear = 0;
	Q.incrementsize = 20000;
}

void incrementQueuesize(SqQueue &Q)
{
	BiTree* a;
	int k;
	a = (BiTree*)malloc(sizeof(BiTree)*(Q.queuesize + Q.incrementsize));
	for (k = 0; k<Q.queuesize; k++)
		a[k] = Q.elem[(Q.front + k) % Q.queuesize];
	free(Q.elem);
	Q.elem = a;
	Q.front = 0;
	Q.rear = Q.queuesize - 1;
}

void EnQueue(SqQueue &Q, BiTree e)
{
	if (Q.front == (Q.rear + 1) % Q.queuesize)
		incrementQueuesize(Q);
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.queuesize;
}


bool EmptyQueue(SqQueue Q)
{
	return Q.front == Q.rear ? true : false;
}

bool DeQueue(SqQueue &Q, BiTree &e)
{
	if (Q.front == Q.rear)
		return false;
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.queuesize;
	return true;
}

bool BiSearchTree(BiTree bt, int kval, BiTree &p, BiTree &pre)
{//在根指针bt所指的二叉树中查找关键字为kval的记录，如果找到p指向它，否则false，f指向p指向记录的双亲 
	p = bt;
	while (p) {
		if (p->data == kval) return true;
		else {
			pre = p;
			if (p->data > kval)
				p = p->lchild;
			else
				p = p->rchild;
		}
	}
	return false;
}

bool BiTree_Insert(BiTree &bt, int kval)	//	
{
	BiTree pre, p;
	pre = NULL;

	if (BiSearchTree(bt, kval, p, pre))	//	if value kval exists, return false
		return false;
	else {
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = kval;
		p->lchild = p->rchild = NULL;
	}
	//	Find the right place to insert the node to maintain the property of tree
	if (!pre) {	//	bt == null
		bt = p;
		(record[p->data].parent) = 0;
		(record[p->data].Height) = 0;
	}
	else if (kval < pre->data) {
		pre->lchild = p;
		(record[pre->data]).lchild = p->data;
		(record[p->data]).parent = pre->data;
		(record[p->data]).parent = pre->data;
		(record[p->data].Height) = (record[pre->data].Height) + 1;
	}
	else {
		pre->rchild = p;
		(record[pre->data]).rchild = p->data;
		(record[p->data]).parent = pre->data;
		(record[p->data].Height) = (record[pre->data].Height) + 1;
	}
	return true;
}

void visite(int data)
{
	printf("%d ", data);
}

int postorder(BiTree bt)
{
	int sonl, sonr;
	if (!bt)
		return 0;
	sonl = postorder(bt->lchild);
	sonr = postorder(bt->rchild);
	(record[bt->data]).son = sonl + sonr + 1;
	visite(bt->data);
	return sonl + sonr + 1;
}

void Traverse(BiTree bt)
{
	// 按层次遍历二叉树 
	BiTNode *p;
	SqQueue Q;
	if (!bt)	return;
	InitQueue(Q);
	EnQueue(Q, bt);
	while (!EmptyQueue(Q)) {
		DeQueue(Q, p);
		visite(p->data);
		if (p->lchild)
			EnQueue(Q, p->lchild);
		if (p->rchild)
			EnQueue(Q, p->rchild);
	}
}