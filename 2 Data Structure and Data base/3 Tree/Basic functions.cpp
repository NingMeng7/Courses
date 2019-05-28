#include <stdio.h>
#include <iostream>
#include <queue>
typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
int count;

BiTree createBiTree();
BiTree createBiTree(int pre[], int ind[], int low1, int hig1, int low2, int high2);

void visit(int data);
void preorder(BiTree bt);
void inorder(BiTree bt);
void postorder(BiTree bt);
void levelorder(BiTree bt);

void countNode(BiTree bt, int &n);
void countLeaf(BiTree bt, int &n);
int countHeight(BiTree bt);
int countWidth(BiTree bt);

void copyTree(BiTree bt, BiTree &new_bt);
void reflectTree(BiTree bt);
void destroyTree(BiTree &bt);

void searchParent(BiTree bt, BiTree &p, int data);//	node, parent, children, brother


int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	BiTree bt, new_bt, p;
	int n;
	int pre[7] = { 1,2,4,7,3,5,6 };
	int ind[7] = { 4,7,2,1,5,3,6 };
	bt = createBiTree(pre, ind, 0,6,0,6);
	
	preorder(bt);	count = 0; cout << endl;
	inorder(bt);	count = 0; cout << endl;
	postorder(bt);	count = 0; cout << endl;
	levelorder(bt);	count = 0; cout << endl;

	n = 0; countNode(bt, n);
	cout << "The number of Node: " << n << endl;
	n = 0; countLeaf(bt, n);
	cout << "The number of Leaves: " << n << endl;
	cout << "The Height of this tree: " << countHeight(bt) << endl;
	cout << "The Width of this tree: " << countWidth(bt) << endl;

	copyTree(bt, new_bt);
	levelorder(new_bt); count = 0; cout << endl;
	reflectTree(new_bt); 
	levelorder(new_bt); count = 0; cout << endl;
	destroyTree(new_bt);
	if (new_bt == NULL)
		cout << "The tree has been destroyed!" << endl;

	p = NULL;
	searchParent(bt, p, 7);
	if (p->rchild->data == 7)
		cout << "I have found 7!" << endl;
	while (1);
	return 0;
}

BiTree createBiTree()
{
	using std::cin;
	int temp;
	BiTree p;
	cin >> temp;
	if (temp == 0)
		return NULL;
	p = new BiTNode;
	p->data = temp;
	p->lchild = createBiTree();
	p->rchild = createBiTree();
	return p;
}

BiTree createBiTree(int pre[], int ind[], int low1, int hig1, int low2, int hig2)
{
	if (low1 > hig1)
		return NULL;
	BiTree p;
	int m;
	p = new BiTNode;
	p->data = pre[low1];
	m = low2;
	while (pre[low1] != ind[m])
		++m;
	p->lchild = createBiTree(pre, ind, low1 + 1, low1 + m - low2, low2, m - 1);
	p->rchild = createBiTree(pre, ind, low1 + m - low2 + 1, hig1, m + 1, hig2);
	return p;
}

void visit(int data)
{	//	Remark: count coincides with some element in namespace std!
	using std::cout;
	using std::endl;
	cout << data << ' ';
	++count;
	if (count % 10 == 0){
		cout << endl;
		count = 0;
	}
}


void preorder(BiTree bt)
{
	if (!bt)
		return;
	visit(bt->data);
	preorder(bt->lchild);
	preorder(bt->rchild);
}


void inorder(BiTree bt)
{
	if (!bt)
		return;
	inorder(bt->lchild);
	visit(bt->data);
	inorder(bt->rchild);
}


void postorder(BiTree bt)
{
	if (!bt)
		return;
	postorder(bt->lchild);
	postorder(bt->rchild);
	visit(bt->data);
}


void levelorder(BiTree bt)
{
	using std::queue;
	BiTNode *p;
	queue<BiTree> Q;
	if (!bt)
		return;
	Q.push(bt);
	while (!Q.empty()) {
		p = Q.front();	Q.pop();
		visit(p->data);
		if (p->lchild) 
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);
	}
}


void countNode(BiTree bt, int &n)
{	//	set n == 0 before calling this function
	if (!bt)
		return;
	n++;
	countNode(bt->lchild, n);
	countNode(bt->rchild, n);
}

void countLeaf(BiTree bt, int &n)
{	//	set n == 0 before calling this function
	if (!bt)
		return;
	if (!bt->lchild && !bt->rchild)
		++n;
	countLeaf(bt->lchild, n);
	countLeaf(bt->rchild, n);
}


int countHeight(BiTree bt)
{
	int hl, hr;
	if (!bt)
		return 0;
	hl = countHeight(bt->lchild);
	hr = countHeight(bt->rchild);
	return 1 + (hl > hr ? hl : hr);
}


int countWidth(BiTree bt)
{
	using std::queue;
	BiTNode *p;
	queue<BiTree> Qa, Qb;
	int width = 1, cnt;
	if (!bt)
		return 0;
	
	Qa.push(bt);
	while (!Qa.empty()) {
		cnt = 0;	//	count for the number of elements in this level
		while (!Qa.empty()) {
			cnt++;
			p = Qa.front();	Qa.pop();
			if (p->lchild)
				Qb.push(p->lchild);
			if (p->rchild)
				Qb.push(p->rchild);
		}
		width = (width > cnt ? width : cnt);
		Qa = Qb;
		while (!Qb.empty())
			Qb.pop();
	}
	return width;
}


void copyTree(BiTree bt, BiTree &new_bt)
{
	if (!bt) {
		new_bt = NULL;
		return;
	}
	new_bt = new BiTNode;
	new_bt->data = bt->data;
	copyTree(bt->lchild, new_bt->lchild);
	copyTree(bt->rchild, new_bt->rchild);
}

void reflectTree(BiTree bt)
{
	if (!bt)
		return;
	BiTree p;
	p = bt->lchild;	bt->lchild = bt->rchild; bt->rchild = p;
	reflectTree(bt->lchild);
	reflectTree(bt->rchild);
}

void destroyTree(BiTree &bt)
{
	if (!bt)
		return;
	destroyTree(bt->lchild);
	destroyTree(bt->rchild);
	delete bt;
	bt = NULL;
}


void searchParent(BiTree bt, BiTree &p, int data)
{
	if (!bt || p != NULL)	//	Tree is empty or we have found data
		return;
	if ((bt->lchild && bt->lchild->data == data) || (bt->rchild && bt->rchild->data == data)) {
		p = bt;
	}
	else {
		searchParent(bt->lchild, p, data);
		searchParent(bt->rchild, p, data);
	}
}
