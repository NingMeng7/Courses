/********************************************************************************
* @File name: polynomial operator
* @Author: WeiXiong
* @Version: 1.1
* @Date: 2019-3-11
* @Description: Exp 1 for Data structure & Data base.
********************************************************************************/

#include <iostream>
#include <stack>
#include <cmath>
#define EPSILON 1e-8
#define N 30

using namespace std;

typedef struct LNode {
	double coef;
	int expn;
	LNode *next;
}LNode, *pNode, *LinkList;

LinkList Polyn[N];
int pnum = 10;

/*	Fundamental function  */


pNode makeNode(double coef, int expn)
{
	pNode node = new LNode;
	node->coef = coef;
	node->expn = expn;
	node->next = NULL;
	return node;	//	return a pointer here
}


void initPolyn(LinkList &L)
{
	L = new LNode;
	L->next = NULL;
}


/*	Clear: L->next == NULL	*/
void clearPolyn(LinkList &L)
{
	if (!L->next)
		return;
	pNode p = L->next, q;
	L->next = NULL;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}
	//	delete p;
}


/*	Destroy: L == NULL*/
void destroyPolyn(LinkList &L)
{
	if (!L)
		return;
	pNode p = L, q;
	L = NULL;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}
}


void printNode(pNode node) {						 
	if (node->expn>1)	
		printf("%.4lfx^%d", node->coef, node->expn);
	else if (node->expn == 1)	
		printf("%.4lfx", node->coef);
	else
		printf("%.4lf", node->coef);
}


void printPolyn(LinkList L) {					 
	if (!L) { cout << "NULL" << endl; return; }
	if (!L->next) { cout << "0.0000" << endl; return; }
	pNode p;
	printNode(L->next);	 
	for (p = L->next->next; p; p = p->next) {
		if (p->coef>0) cout << "+";
		printNode(p);
	}
	cout << endl;
}


void copyPolyn(LinkList La, LinkList &Lb)	//	Lb <- La
{
	if (Lb->next)
		clearPolyn(Lb);	//	free the memory
	pNode pa = La->next, pb = Lb;
	while (pa) {
		pb->next = makeNode(pa->coef, pa->expn);	//	change the value of the structure
		pa = pa->next;
		pb = pb->next;	// change the value of the pointer
	}
}


void insertNode(LinkList L, pNode node)	//	The powers are from big to small
{
	pNode p = L, q = L->next;
	if (abs(node->coef) <= EPSILON)
		return;
	while (q && node->expn < q->expn) {
		p = q;
		q = q->next;
	}
	if (!q) {	//	new node is inserted at the end
		p->next = node;
		node->next = NULL;
	}
	else if (node->expn == q->expn) {	//	merge
		if (abs(node->coef + q->coef) <= EPSILON)
			p->next = q->next;
		else
			q->coef += node->coef;
		delete node;
	}
	else {
		p->next = node;
		node->next = q;
	}
}

/*	The node with coef 0 will not be accepted  */
void createPolyn(LinkList &L)
{
	double coef;
	int expn;
	pNode node;
	if (L)
		clearPolyn(L);
	else
		initPolyn(L);
	cin >> coef >> expn;
	while (coef || expn) {
		if (coef) {
			node = makeNode(coef, expn);
			insertNode(L, node);
		}
		cin >> coef >> expn;
	}
}


/*	Operator  */

/*  Lc <- La + Lb  */
void addPolyn(LinkList La, LinkList Lb, LinkList &Lc)
{
	pNode pa, pb, pc, tempnode;
	if (!Lc)
		initPolyn(Lc);
	copyPolyn(Lb, Lc);	//	O(|Lb|)
	/*
	for (p = La->next; p; p = p->next) {
		tempnode = makeNode(p->coef, p->expn);
		insertNode(Lc, tempnode);	//	O(|La|^2+|Lb||La|)
	}*/
	pa = La->next;	//	We assume that the powers are orderly
	pb = Lb->next;
	pc = Lc;
	while (pa && pb) {
		if (pa->expn > pb->expn) {
			tempnode = makeNode(pa->coef, pa->expn);
			pc->next = tempnode;
			pa = pa->next;
			pc = pc->next;
		}
		else if (pb->expn > pa->expn) {
			tempnode = makeNode(pb->coef, pb->expn);
			pc->next = tempnode;
			pb = pb->next;
			pc = pc->next;
		}
		else {
			if (abs(pa->coef + pb->coef) <= EPSILON) {
				;
			}
			else {
				tempnode = makeNode(pa->coef + pb->coef, pa->expn);
				pc->next = tempnode;
			}
			pa = pa->next;
			pb = pb->next;
			pc = pc->next;
		}
	}
	while (pa) {
		tempnode = makeNode(pa->coef, pa->expn);
		pc->next = tempnode;
		pa = pa->next;
	}
	while (pb) {
		tempnode = makeNode(pb->coef, pb->expn);
		pc->next = tempnode;
		pb = pb->next;
	}//	O(|La|+|Lb|)
}


void subPolyn(LinkList La, LinkList Lb, LinkList &Lc)
{
	pNode pa, tempnode;
	if (!Lc)
		initPolyn(Lc);
	copyPolyn(Lb, Lc);	//	O(|Lb|)
	for (pa = La->next; pa; pa = pa->next) {
		tempnode = makeNode(-pa->coef, pa->expn);
		insertNode(Lc, tempnode);	//	O(|La|^2+|Lb||La|)
	}
}


double valuePolyn(LinkList L, double x) {				//返回非空L的值，当x=x(input) 
	pNode p = L->next;
	double val = 0;
	for (; p; p = p->next)
		if (abs(p->coef) >= EPSILON)	val += p->coef * pow(x, p->expn);
	return val;
}


void deleteNode(LinkList &L, int expn)
{
	pNode p = L, q = L->next;
	while (q) {
		if (q->expn == expn) {
			p->next = q->next;
			delete q;
			return;
		}
		p = q;
		q = q->next;
	}
}


void setNode(LinkList &L, double coef, int expn)
{
	pNode p = L->next, tempnode;
	if (abs(coef) <= EPSILON) {
		deleteNode(L, expn);
	}
	
	while (p) {
		if (p->expn == expn) {
			p->coef = coef;
			return;
		}
		p = p->next;
	}
	
	tempnode = makeNode(coef, expn);	//	if not exist, insert it.
	insertNode(L, tempnode);
}


void IndefiniteIntegral(LinkList L1, LinkList &L2) 
{
	if (!L2)	initPolyn(L2);
	else if (L2->next)	clearPolyn(L2);	
	pNode p, tempnode;
	for (p = L1->next; p; p = p->next) {
		tempnode = makeNode(p->coef / (p->expn + 1), p->expn + 1);
		insertNode(L2, tempnode);
	}
}


void Differential(LinkList L1, LinkList &L2) {	
	if (L2 == NULL)	initPolyn(L2);
	else if (L2->next)	clearPolyn(L2);	
	pNode p, tempnode;
	for (p = L1->next; p; p = p->next)
		if (p->expn) {
			tempnode = makeNode(p->coef * p->expn, p->expn - 1);
			insertNode(L2, tempnode);
		}
}


void multiPolyn(LinkList La, LinkList Lb, LinkList &Lc)	//	Lc <- La * Lb, without checking La, Lb
{
	if (!Lc)
		initPolyn(Lc);
	else if (Lc->next)
		clearPolyn(Lc);
	pNode pa, pb, tempnode;
	if (!Lb->next)	return;
	for(pa = La->next;pa;pa=pa->next)
		for (pb = Lb->next; pb; pb = pb->next) {
			tempnode = makeNode(pa->coef*pb->coef, pa->expn + pb->expn);
			insertNode(Lc, tempnode);
		}
}


void divPolyn(LinkList La, LinkList Lb, LinkList &Lc)	//	Lc = La / Lb, without checking La, Lb
{
	LinkList divisor, tempmult, remain;
	initPolyn(divisor);	initPolyn(tempmult);  initPolyn(remain);
	if (!Lc)	initPolyn(Lc);
	else if (Lc->next)	clearPolyn(Lc);
	pNode tempnode1, tempnode2, pa, pb,q;
	copyPolyn(La, divisor);
	pa = divisor->next;
	pb = Lb->next;
	while (pa && pa->expn >= pb->expn) {
		tempnode1 = makeNode(pa->coef / pb->coef, pa->expn - pb->expn);
		insertNode(Lc, tempnode1);
		clearPolyn(tempmult);
		for (q = pb; q != NULL; q = q->next) {
			tempnode2 = makeNode(tempnode1->coef*q->coef, tempnode1->expn + q->expn);
			insertNode(tempmult, tempnode2);
		}
		subPolyn(divisor, tempmult, remain);
		copyPolyn(remain, divisor);
	}
}


void remPolyn(LinkList La, LinkList Lb, LinkList Lc)	//	Lc = La - La/Lb
{
	LinkList divisor, tempmult, remain;
	initPolyn(divisor);	initPolyn(tempmult);  initPolyn(remain);
	if (!Lc)	initPolyn(Lc);
	else if (Lc->next)	clearPolyn(Lc);
	pNode tempnode1, tempnode2, pa, pb, q;
	copyPolyn(La, divisor);
	pa = divisor->next;
	pb = Lb->next;
	while (pa && pa->expn >= pb->expn) {
		tempnode1 = makeNode(pa->coef / pb->coef, pa->expn - pb->expn);
		insertNode(Lc, tempnode1);
		clearPolyn(tempmult);
		for (q = pb; q != NULL; q = q->next) {
			tempnode2 = makeNode(tempnode1->coef*q->coef, tempnode1->expn + q->expn);
			insertNode(tempmult, tempnode2);
		}
		subPolyn(divisor, tempmult, remain);
		copyPolyn(remain, divisor);
	}
	copyPolyn(divisor, Lc);
}


void powerPolyn(LinkList La, LinkList &Lb, int n)	//	Lb <- (La)^n, without checking n
{
	if (!Lb)	initPolyn(Lb);
	else if (Lb->next)	clearPolyn(Lb);
	LinkList templist;
	pNode tempnode;
	if (n == 0) {
		tempnode = makeNode(1, 0);
		insertNode(Lb, tempnode);
		return;
	}
	initPolyn(templist);
	copyPolyn(La, Lb);
	for (; n > 1; n--) {
		multiPolyn(La, Lb, templist);
		copyPolyn(templist, Lb);
	}
}


void gcdPolyn(LinkList La, LinkList Lb, LinkList &Lc)
{
	LinkList divisor, dividend, remain;
	pNode p;
	double coef;
	if (!Lc)	initPolyn(Lc);
	else if (Lc->next)	clearPolyn(Lc);
	initPolyn(divisor);	initPolyn(dividend);  initPolyn(remain);
	if (La->next->expn >= Lb->next->expn) {
		copyPolyn(La, dividend);
		copyPolyn(Lb, divisor);
	}
	else {
		copyPolyn(Lb, dividend);
		copyPolyn(La, divisor);
	}	//	make sure expen of dividend >= that of divisor
	remPolyn(dividend, divisor, remain);
	while (remain->next != NULL) {
		if (divisor->next->expn >= remain->next->expn) {
			copyPolyn(divisor, dividend); copyPolyn(remain, divisor);
		}
		else
			copyPolyn(remain, dividend);
		remPolyn(dividend, divisor, remain);
	}
	copyPolyn(divisor, Lc);
	for (p = Lc->next, coef = p->coef; p; p = p->next) {
		p->coef = p->coef / coef;
	}
}


void lcmPolyn(LinkList La, LinkList Lb, LinkList &Lc)
{
	LinkList gcd, tempmulti;
	pNode p;
	double coef;
	if (!Lc)	initPolyn(Lc);
	else if (Lc->next)	clearPolyn(Lc);
	initPolyn(gcd);	initPolyn(tempmulti);
	multiPolyn(La, Lb, tempmulti);
	gcdPolyn(La, Lb, gcd);
	divPolyn(tempmulti, gcd, Lc);
	for (p = Lc->next, coef=p->coef; p; p = p->next) {
		p->coef = p->coef / coef;
	}
}


int isoperator(char ch) 
{
	return (ch == '\0' || ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')') ? 1 : 0;
}


void operate(char a, char c, char b)
{
	LinkList templist;
	initPolyn(templist);
	switch (c)
	{
	case '+': addPolyn(Polyn[a - 48], Polyn[b - 48], templist); break;
	case '-': subPolyn(Polyn[a - 48], Polyn[b - 48], templist); break;
	case '*': multiPolyn(Polyn[a - 48], Polyn[b - 48], templist); break;
	case '/': divPolyn(Polyn[a - 48], Polyn[b - 48], templist); break;
	}
	if (!Polyn[pnum])	initPolyn(Polyn[pnum]);
	copyPolyn(templist, Polyn[pnum]);	pnum++;
}


int preop(char c, char ch)
{
	int pc, pch;
	switch (c) {
	case '\0':	pc = -1; break;
	case '(':	pc = 0; break;
	case '+':	pc = 1; break;
	case '-':	pc = 1; break;
	case '*':	pc = 2; break;
	case '/':	pc = 2; break;
	}
	switch (ch) {
	case '\0':	pch = -1; break;
	case '(':	pch = 0; break;
	case '+':	pch = 1; break;
	case '-':	pch = 1; break;
	case '*':	pch = 2; break;
	case '/':	pch = 2; break;
	}
	return (pc >= pch) ? 1 : 0;
}


void EvaluateExp(char exp[], LinkList &L) {	//四则运算 
	stack<char> SOP, SVAL;	//运算符栈SOP，操作数栈SVAL
	SOP.push('\0');
	char ch, c, a, b;
	char *p = exp;
	while (!SOP.empty()) {
		ch = *p++;
		if (!isoperator(ch)) {
			SVAL.push(ch); continue;
		}
		switch (ch) {
		case'(':SOP.push(ch); break;
		case')':
			while ((c = SOP.top()) != '(') {
				SOP.pop();
				b = SVAL.top(); SVAL.pop(); if (b>57)pnum--;
				a = SVAL.top(); SVAL.pop(); if (a>57)pnum--;
				operate(a, c, b);
				SVAL.push(pnum + 47);
			}
			SOP.pop(); break;
		case'\0':
			while ((c = SOP.top()) != '\0') {
				SOP.pop();
				b = SVAL.top(); SVAL.pop(); if (b>57)pnum--;
				a = SVAL.top(); SVAL.pop(); if (a>57)pnum--;
				operate(a, c, b);
				SVAL.push(pnum + 47);
			}
			SOP.pop(); break;
		default:
			while ((c = SOP.top()) != '\0'&&preop(c, ch)) {
				SOP.pop();
				b = SVAL.top(); SVAL.pop(); if (b>57)pnum--;
				a = SVAL.top(); SVAL.pop(); if (a>57)pnum--;
				operate(a, c, b);
				SVAL.push(pnum + 47);
			}
			SOP.push(ch); break;
		}//endswitch
	}//endwhile
	if (!L)	initPolyn(L);
	copyPolyn(Polyn[10], L);
	pnum = 10;
}


int main() {
	double x, y, val, c;		//x,y-自变量；val-函数值；c-系数 
	int w, m, n, t, e;			//w-操作数；m,n,t-多项式序号；t-次操作数；e-指数 
	pNode tempnode;
	char exp[100];			//存放中缀表达式 
	int i;
	for (i = 1; i<11; i++)	Polyn[i] = NULL;
	cin >> w;
	while (w != 0) {
		switch (w) {
		case 1:				//创建 
			cin >> m; createPolyn(Polyn[m]); break;
		case 2:				//显示 
			cin >> m; printPolyn(Polyn[m]); break;
		case 3:				//复制 
			cin >> m >> n;
			if (Polyn[m] && Polyn[n])
				copyPolyn(Polyn[m], Polyn[n]);
			else if (Polyn[m]) {
				initPolyn(Polyn[n]);
				copyPolyn(Polyn[m], Polyn[n]);
			}
			break;
		case 4:				//求和 
			cin >> m >> n >> t; addPolyn(Polyn[m], Polyn[n], Polyn[t]); break;
		case 5:				//求差 
			cin >> m >> n >> t; subPolyn(Polyn[m], Polyn[n], Polyn[t]); break;
		case 6:				//求值 
			cin >> m >> x; val = valuePolyn(Polyn[m], x); printf("%.4lf\n", val); break;
		case 7:				//销毁 
			cin >> m; destroyPolyn(Polyn[m]); break;
		case 8:				//清空 
			cin >> m;
			if (Polyn[m])	clearPolyn(Polyn[m]); break;
		case 9:				//修改 
			cin >> m >> t;
			switch (t) {
			case 1:cin >> c >> e; tempnode = makeNode(c, e); insertNode(Polyn[m], tempnode); break;						//插入新项 
			case 2:cin >> e; deleteNode(Polyn[m], e); break;								//删除项 
			case 3:cin >> c >> e; setNode(Polyn[m], c, e); break;	//修改项 可优化 
			}
			break;
		case 10:	//微分
			cin >> m >> n; Differential(Polyn[m], Polyn[n]); break;
		case 11:	//不定积分
			cin >> m >> n; IndefiniteIntegral(Polyn[m], Polyn[n]); break;
		case 12:	//定积分
			cin >> m >> x >> y;
			IndefiniteIntegral(Polyn[m], Polyn[10]);
			val = valuePolyn(Polyn[10], y) - valuePolyn(Polyn[10], x);
			printf("%.4lf\n", val); break;
		case 13:			//乘法
			cin >> m >> n >> t; multiPolyn(Polyn[m], Polyn[n], Polyn[t]); break;
		case 14:	//除法 
			cin >> m >> n >> t; divPolyn(Polyn[m], Polyn[n], Polyn[t]); break;
		case 15:	//求余 
			cin >> m >> n >> t; remPolyn(Polyn[m], Polyn[n], Polyn[t]); break;
		case 16:	//乘方 
			cin >> m >> n >> t; powerPolyn(Polyn[m], Polyn[n], t); break;
		case 17:	//最大公约式
			cin >> m >> n >> t; gcdPolyn(Polyn[m], Polyn[n], Polyn[t]);  break;
		case 18:	//最小公倍式 
			cin >> m >> n >> t; lcmPolyn(Polyn[m], Polyn[n], Polyn[t]);  break;
		case 19:	//四则运算 
			cin >> m; cin >> exp; EvaluateExp(exp, Polyn[m]); break;
		}//endswitch
		cin >> w;
	}//endwhile
	return 0;
}
