#include "stdio.h"
#include "stdlib.h"
#include "math.h" 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  //不可实现 
#define OVERLOW -2
#define INIT_SIZE 200000
#define EXPAND_SIZE 100000
#define N 900000

typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
	BiTree *base;
	BiTree *top;
	int stacksize;
}SqStack;

typedef struct {
	int parent;
	int lchild;
	int rchild;
	int Height;
	int son;
}infom;

infom	info[N]; //0不用 

typedef int status;
typedef struct {
	BiTree *elem;
	int front; //指向队头元素 
	int rear; //指向队尾元素后一个位置，数组下标 
	int queuesize;
	int incrementsize;
}SqQueue;

void incrementQueuesize(SqQueue &Q);
void InitQueue(SqQueue &Q)
{
	Q.queuesize = 400000;
	Q.elem = (BiTree*)malloc(sizeof(BiTree)*Q.queuesize);
	Q.front = Q.rear = 0;
	Q.incrementsize = 20000;
}

void EnQueue(SqQueue &Q, BiTree e)
{
	if (Q.front == (Q.rear + 1) % Q.queuesize)
		incrementQueuesize(Q);
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.queuesize;
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

status EmptyQueue(SqQueue Q)
{
	return Q.front == Q.rear ? TRUE : FALSE;
}

status DeQueue(SqQueue &Q, BiTree &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.queuesize;
	return OK;
}

void visite(int data)
{
	printf("%d ", data);
}

status BinSrTree(BiTree bt, int kval, BiTree &p, BiTree &f)
{//在根指针bt所指的二叉树中查找关键字为kval的记录，如果找到p指向它，否则false，f指向p指向记录的双亲 
	p = bt;
	while (p) {
		if (p->data == kval) return TRUE;
		else {
			f = p;
			if (p->data > kval)
				p = p->lchild;
			else
				p = p->rchild;
		}
	}
	return FALSE;
}

status BinSrTree_Ins(BiTree &bt, int kval)
{
	BiTree f, p;
	f = NULL;
	if (BinSrTree(bt, kval, p, f))
		return FALSE;
	else {
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = kval;
		p->lchild = p->rchild = NULL;
	}
	if (!f) {
		bt = p;
		(info[p->data].parent) = 0;
	}
	else if (kval < f->data) {
		f->lchild = p;
		(info[f->data]).lchild = p->data;
		(info[p->data]).parent = f->data;
	}
	else {
		f->rchild = p;
		(info[f->data]).rchild = p->data;
		(info[p->data]).parent = f->data;
	}
	return TRUE;
}

void CreateBiTree(BiTree &bt, int pre[], int n)
{
	int i;
	for (i = 1; i <= n; i++) {
		BinSrTree_Ins(bt, pre[i]);
	}
}

int postorder(BiTree bt)
{
	int sonl, sonr;
	if (!bt)
		return 0;
	sonl = postorder(bt->lchild);
	sonr = postorder(bt->rchild);
	(info[bt->data]).son = sonl + sonr + 1;
	visite(bt->data);
	return sonl + sonr + 1;
}


void level(BiTree bt, int lev)
{
	// lev传递的是双亲的层次，lev对应的实参初值应为0,先序 
	if (!bt) return;
	lev++;
	(info[bt->data]).Height = lev;
	level(bt->lchild, lev);
	level(bt->rchild, lev);
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

int main()
{
	BiTree bt = NULL;
	int n, i, m, lev;
	infom c;
	c.Height = c.lchild = c.parent = c.rchild = c.son = 0;
	scanf("%d", &n);
	int pre[n + 10], ind[n + 10], refer[n + 10];
	for (i = 1; i <= n; i++) {
		(info[i]) = c;
	}
	for (i = 1; i <= n; i++) {
		scanf("%d", &pre[i]);
	}
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%d", &refer[i]);
	}
	CreateBiTree(bt, pre, n);
	postorder(bt);
	putchar('\n');
	Traverse(bt);
	putchar('\n');
	lev = -1;
	level(bt, lev);
	for (i = 1; i <= m; i++) {
		printf("%d %d %d %d %d\n", info[refer[i]].parent, info[refer[i]].lchild, info[refer[i]].rchild, info[refer[i]].Height, info[refer[i]].son);
	}
	//printf("%d %d %d %d %d",info[refer[m]].parent,info[refer[m]].lchild,info[refer[m]].rchild,info[refer[m]].Height,info[refer[m]].son);
	return 0;
}
