#include "stdio.h"
#include "stdlib.h"
#include "math.h" 


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  //不可实现 
#define OVERLOW -2


#define N 30
#define INIT_SIZE 4
#define EXPAND_SIZE 10
#define LEN sizeof(struct LNode)
#define EPS 1e-8

typedef struct LNode{
	double coef;
	int expn;
	struct LNode *next;
}LNode,*LinkList;


typedef struct{
	int *base;
	int *top;
	int stacksize;
}SqStack;


typedef int Status;

LNode *MakeNode(double coef,int expn);
Status InitList(LinkList &L);
Status ListDelete(LinkList L,int i);
Status PrintList(LinkList &L);
Status DestroyList(LinkList &L);
Status ClearList(LinkList &L);
void SimpList(LinkList &L);
void ListSort(LinkList &L);
Status ListDelete(LinkList L,int i);
Status CopyList(LinkList L1,LinkList &L);
double ValueList(LinkList L,double x);
Status AddList(LinkList L1,LinkList L2,LinkList &L);
Status SubList(LinkList L1,LinkList L2,LinkList &L);
Status MulList(LinkList L1,LinkList L2,LinkList &L);
Status DivList(LinkList L1,LinkList L2,LinkList &L);
Status RemList(LinkList L1,LinkList L2,LinkList &L);
Status GcdList(LinkList L1,LinkList L2,LinkList &L);
Status LcmList(LinkList L1,LinkList L2,LinkList &L);

Status ModiPolyn(LinkList *Poly);
Status InitPolyn(LinkList *Poly);
Status PrintPolyn(LinkList *Poly); 
Status CreatePolyn(LinkList *Poly);
Status DestroyPolyn(LinkList *Poly);
Status ClearPolyn(LinkList *Poly);
Status CopyPolyn(LinkList *Poly);
Status AddPolyn(LinkList *Poly);
Status SubPolyn(LinkList *Poly);
Status MulPolyn(LinkList *Poly);
Status DivPolyn(LinkList *Poly);
Status RemPolyn(LinkList *Poly);
Status ModPolyn(LinkList *Poly);
Status PowPolyn(LinkList *Poly);
Status GcdPolyn(LinkList *Poly);
Status LcmPolyn(LinkList *Poly);
Status DifPolyn(LinkList *Poly);
Status IndefintPolyn(LinkList *Poly);
Status IntPolyn(LinkList *Poly);
Status Value(LinkList *Poly);
Status PowPolyn(LinkList *Poly);
Status Sizeyunsuan(LinkList *Poly);


// Stack：限制插入和删除位置只能在表尾进行的线性表 （后进先出）
// 约定: S.top 指在当前元素后一个 
// StackEmpty条件： S.top == S.base
// ADT  
Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S); 
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S); 
Status GetTop(SqStack S,int &e); 
Status Push(SqStack &S,int e); // 算法模型中没有给S加上&
Status Pop(SqStack &S,int &e);
void Print1(SqStack S);
void Print2(SqStack S);
//ADT
// 代表多项式的数字放在栈里，符号直接外部判断 
void operate(LinkList L1,LinkList L2,LinkList &L);
Status isoperator(char ch);
Status preop(char c,char ch);
//


Status InitStack(SqStack &S)
{
	S.base = (int *)malloc(INIT_SIZE * sizeof(int));
	if(!S.base){
		printf("OVERFLOW!\n");
		return OVERFLOW;
	}
	S.stacksize = INIT_SIZE;
	S.top = S.base; 	
	return OK;
	/* -> & .
		如果是结构体引用元素应到使用。stacksize 如果是指向结构体的指针引用元素应当使用->stacksize 或者(*s).stacksize 
	*/
}

Status GetTop(SqStack S,int &e)
{
	if(S.top == S.base)
		return ERROR; //栈空
	e = *(S.top - 1);
	return OK; 
}

Status StackEmpty(SqStack S)
{
	if(S.top == S.base)
		return TRUE;
	else return FALSE;
}

Status Push(SqStack &S,int e)
{
	//进栈
	if((S.top - S .base) == S.stacksize){
		S.base = (int *)realloc(S.base,(S.stacksize+EXPAND_SIZE)*(sizeof(int)));
		if(!S.base) return(OVERFLOW);
		S.top = S.base + S.stacksize;  // 当realloc在S.base后无法找到足够的连续空间的时候保证top不丢失 
		S.stacksize += EXPAND_SIZE;	
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S,int &e)
{	
	//若栈不空,则返回栈顶元素,否则返回ERROR
	if(S.top == S.base) return ERROR;
	e = *(--S.top);
	return OK; 
}

int StackLength(SqStack S)
{
	return S.top - S.base;
}

Status DestroyStack(SqStack &S)
{
	S.top = S.base;
	free(S.base);
	S.stacksize = 0;
	return OK;
}

Status StackClear(SqStack &S)
{
	while(S.top != S.base){
		*(--S.top) = 0;
	}
	return OK;
}

void Print1(SqStack S)
{
	int *p = S.top;
	int count = 0;
	printf("From top -> base: you get:\n");
	while(p != S.base){
		printf("%4d",*(--p));
		++count;
		if(count%16 == 0) 
			putchar('\n');
	} 
	putchar('\n');
}

void Print2(SqStack S)
{
	int *p = S.base;
	int count = 0;
	printf("From base -> top: you get:\n");
	while(p != S.top){
		printf("%4d",*(p++));
		count++;
		if(count%16 == 0)
			putchar('\n');
	}
	putchar('\n'); 
}

Status isoperator(char ch)
{
	if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')' || ch=='#')
		return TRUE;
	return FALSE;
}

Status preop(char c,char ch)
{
	int p[7][7]={{1,1,-1,-1,-1,1,1},{1,1,-1,-1,-1,1,1},{1,1,1,1,-1,1,1},{1,1,1,1,-1,1,1},{-1,-1,-1,-1,-1,0,0},
				{1,1,1,1,0,1,1},{-1,-1,-1,-1,-1,0,0}};
	int i,j;
	switch(c){
		case'+': i=0; break;
		case'-': i=1; break;
		case'*': i=2; break;
		case'/': i=3; break;
		case'(': i=4; break;
		case')': i=5; break;
		case'#': i=6; break;
	}
	switch(ch){
		case'+': j=0; break;
		case'-': j=1; break;
		case'*': j=2; break;
		case'/': j=3; break;
		case'(': j=4; break;
		case')': j=5; break;
		case'#': j=6; break;
	}
	return p[i][j];
}
void operate(LinkList L1,char ch,LinkList L2,LinkList &L)
{
	switch(ch){
		case '+': AddList(L1,L2,L); break;
		case '-': SubList(L1,L2,L); break;
		case '*': MulList(L1,L2,L); break;
		case '/': DivList(L1,L2,L); break;
	}
}
void getsuffix(char exp[],char suffix[])
{
	SqStack S; 
	InitStack(S);
	Push(S,'#');
	int k = 0, ch,c,e,d;
	char *p;
	p = exp;
	while(*p!='\0'){
		p++;
	}
	*p = '#';
	*(++p) = '\0';
	p = exp;
	ch = *p++;
	while(!(ch=='#' && d == '#')){
		if(!isoperator(ch)){
	    	suffix[k++] = ch;
			ch = *p++;
			GetTop(S,d);
			//putchar('\n');
			//printf("%s",suffix);
		}
		else{
			GetTop(S,c);
			switch(preop(c,ch)){
				case -1: Push(S,ch); ch = *p++;	GetTop(S,d);break;
				case 0:  Pop(S,e);   ch = *p++; GetTop(S,d);break;
				case 1:  Pop(S,c); 	 suffix[k++]=c; GetTop(S,d);break;
			}
		//	putchar('\n');
			//printf("%s",suffix);
		}	
	}
	printf("%s",suffix);
	suffix[k++] ='\0';
}

int main()
{
/*	int a;
	FILE *fin,*fout;
	fin = fopen("example.in","r");
	fout = fopen("example.out","w");
	fscanf(fin,"%d",&a);
	fprintf(fout,"%d",&a);
	fclose(fin);
	fclose(fout);
	return 0;  */
	LinkList Poly[N]; 
	int w,i;
	for(i=0;i<=N;i++)
		Poly[i] = NULL;
	while(1){
		printf("Please input the function you want to use:\n1.Create 2.Print 3.Copy 4.Add 5.Sub 6.Value 7.Destroy 8.Clear 9.Modi 10.Diff 11.Indeint 12.Int 13.Multi 14.Div 15.Rem 17:Gcd 18:Lcm : ");
		do{
			scanf("%d",&w);
			if(w == 0) break;
			if(w<0 || w>19) printf("You input an error number,please input again!\n");
		}while(w<1 || w>19);
		switch(w){
			case 1:	CreatePolyn(Poly);  break;
			case 2:	PrintPolyn(Poly);	break;
			case 3:	CopyPolyn(Poly);	break;
			case 4:	AddPolyn(Poly); 	break;
			case 5:	SubPolyn(Poly); 	break;
			case 6:	Value(Poly); 		break;
			case 7:	DestroyPolyn(Poly); break; 
			case 8:	ClearPolyn(Poly); 	break;
			case 9:	ModPolyn(Poly); 	break; 
			case 10:DifPolyn(Poly); 	break;
			case 11:IndefintPolyn(Poly);break;
 			case 12:IntPolyn(Poly); 	break;
 			case 13:MulPolyn(Poly); 	break;
 			case 14:DivPolyn(Poly); 	break;
 			case 15:RemPolyn(Poly); 	break;
 			case 16:PowPolyn(Poly); 	break;
 			case 17:GcdPolyn(Poly); 	break;
			case 18:LcmPolyn(Poly);		break;
			case 19:Sizeyunsuan(Poly);  break;
		}
	}
}

Status InitList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

Status ListDelete(LinkList L,int i)   // L带头结点 
{
	LNode *p,*q;
	int j;
	p = L; j =0;
	while(p->next && j<i-1){  //p指向删除结点的前一个位置，所以最后一个结点也应该指向Lenghth-1个结点 
		p = p->next; j++;
	}
	if(!p->next || j>i-1) return ERROR;
	q = p->next; 
	p->next = q->next;
	free(q);
	return OK;
}
Status CopyList(LinkList L1,LinkList &L)
{ // 复制L1到L中
	LNode *p,*q,*rear;
	if(L1==NULL || L1->next==NULL){
		return ERROR;
	}
	p = L1->next;
	L = (LinkList)malloc(LEN);
	L->next = NULL;
	rear = L;
	while(p != NULL){
		q = MakeNode(p->coef,p->expn);
		q->next = rear->next;
		rear->next = q;
		rear = q;
		p = p->next;
	}		
	return OK;
}

Status DestroyList(LinkList &L)
{ // 清空多项式并将头结点置NULL
	LNode *p,*q;
	if(L == NULL) 
		return OK;
	p = L->next;
	while(p){
		q = p->next; free(p); p = q;
	}
	L = NULL;
	return OK;
}

Status PrintList(LinkList &L)
{ // 打印多项式
	LNode *p;
	if(L == NULL){
		printf("NULL\n");
		return(0);
	}
	if(L->next == NULL){
		printf("0\n");
		return 0;
	}
	p = L->next;
	while(p){
		if(p->coef > 0){
			if(p->expn == 0)	
				printf("%.4lf",p->coef);
			else if(p->expn == 1) 
				printf("%.4lfx",p->coef);
			else 
				printf("%.4lfx^%d",p->coef,p->expn);
				p = p->next;
				if(p != NULL) printf("+");
		}
		else if(p->coef < 0){
			if(p->expn == 0)
				printf("(%.4lf)",p->coef);
			else if(p->expn == 1) 
				printf("(%.4lfx)",p->coef);
			else 
				printf("(%.4lfx^%d)",p->coef,p->expn);
				p = p->next;
				if(p != NULL) printf("+");
		}
	}
	putchar('\n');
	return OK;
}

Status ClearList(LinkList &L)
{ // 清空多项式，并使得L->next==NULL,代表这个多项式为0.0000
	LNode *p,*q;
	if(!L) return ERROR;
	p = L->next;
	while(p){
		q = p->next; free(p); p = q;  
	} 
	L->next = NULL;
	return OK;	 	
}
double ValueList(LinkList L,double x)
{ // 求值
	double result;
	LNode *p;
	p = L->next;
	result = 0;
	while(p){
		result = result + p->coef * pow(x,p->expn);
		p = p->next;
	}
	return result;	
}
Status AddList(LinkList L1,LinkList L2,LinkList &L)
{ // L1+L2储存在L中
	LNode *p,*q,*rear,*v;
	p = L1->next;
	q = L2->next;
	L = (LinkList)malloc(LEN);
	L->next =NULL;
	rear = L;
	while(p && q){
		if(p->expn > q->expn){
			v = MakeNode(p->coef,p->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			p = p->next;
		}
		else if(p->expn < q->expn){
			v = MakeNode(q->coef,q->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			q = q->next;
		}
		else if(p->expn == q->expn){
			if((p->coef+q->coef) < EPS){
				p = p->next; q = q->next;
			}
			else {
				v = MakeNode(p->coef+q->coef,p->expn);
				v->next = rear->next;
				rear->next = v;
				rear = v;
				p = p->next;
				q = q->next;
			}
		}
	}
	if(p == NULL){
		while(q){
			v = MakeNode(q->coef,q->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			q = q->next;
		} 
	}
	else if(q == NULL){
		while(p){
			v = MakeNode(p->coef,p->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			p = p->next;
		}
	}
	return OK;
}
Status SubList(LinkList L1,LinkList L2,LinkList &L)
{ // L1-L2 储存在 L中
	LNode *p,*q,*rear,*v;
	p = L1->next;
	q = L2->next;
	L = (LinkList)malloc(LEN);
	L->next =NULL;
	rear = L;
	while(p && q){                          //用指针P,q 扫描两个链表通过比较判断将结果插入新的多项式 
		if(p->expn > q->expn){
			v = MakeNode(p->coef,p->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			p = p->next;
		}
		else if(p->expn < q->expn){
			v = MakeNode(-q->coef,q->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			q = q->next;
		}
		else if(p->expn == q->expn){
			if((p->coef-q->coef) < EPS){
				p = p->next; q = q->next;
			}
			else {
				v = MakeNode(p->coef-q->coef,p->expn);
				v->next = rear->next;
				rear->next = v;
				rear = v;
				p = p->next;
				q = q->next;
			}
		}
	}
	if(p == NULL){                        // 当上一个循环结束后，将还没有扫描完的多项式继续插入新的多项式中 
		while(q){
			v = MakeNode(-q->coef,q->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			q = q->next;
		} 
	}
	else if(q == NULL){
		while(p){
			v = MakeNode(p->coef,p->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;
			p = p->next;
		}
	}
	return OK;
}

Status MulList(LinkList L1,LinkList L2,LinkList &L)
{ // L1*L2两个带头节点的单项式储存在L中 
	LNode *p,*q,*rear,*v;
	p = L1->next;
	q = L2->next;
	L = (LinkList)malloc(LEN);
	L->next = NULL;
	rear = L;
	while(p){                     //两层循环，q的一个因子去乘p的每一项，然后再把q的因子遍历 
		while(q){
			v = MakeNode(p->coef*q->coef,p->expn+q->expn);
			v->next = rear->next;
			rear->next = v;
			rear = v;					
			q = q->next;
		}
		q = L2->next;
		p = p->next;
	}
	ListSort(L);
	SimpList(L);
	return OK; 
}


Status DivList(LinkList L1,LinkList L2,LinkList &L)
{ //计算L1/L2 储存在L中 
	LNode *p,*q,*rear,*v;
	LinkList temp,coL1,b;
	if(L1->next->expn < L2->next->expn){ // 如果m1次数比m2低，则得数为0，条件判断不能换序 		
		L = (LinkList)malloc(LEN);
		L->next = NULL;
		return OK;
	}	
	b = (LinkList)malloc(LEN);
	b->next = NULL;
	p = L1->next;		
	q = L2->next;
	L = (LinkList)malloc(LEN);
	L->next =NULL;
	rear = L;
	while(p && p->expn>=q->expn){                     //两层循环，q的一个因子去乘p的每一项，然后再把q的因子遍历 
		v = MakeNode(p->coef/q->coef,p->expn-q->expn);
		b->next = v;
		MulList(b,L2,temp);
		v->next = rear->next;
		rear->next = v;
		CopyList(L1,coL1);
		SubList(coL1,temp,L1);
		p = L1->next;
	}
	ListSort(L);
	SimpList(L);	
	return OK;
}
Status RemList(LinkList L1,LinkList L2,LinkList &L)
{ // 求余式储存在L
	LinkList Div,Mul;
	Div = (LinkList)malloc(LEN);
	Mul = (LinkList)malloc(LEN);
	Div->next = NULL;
	Mul->next = NULL;
	DivList(L1,L2,Div);
	MulList(L2,Div,Mul);
	SubList(L1,Mul,L);
	return OK;
}

Status GcdList(LinkList L1,LinkList L2,LinkList &L)
{ // 求L1 L2 最大公约式储存在L
	double temp = 0;
	LNode *p;
	LinkList Div,Rem;
	if(L1->next == NULL){
		CopyList(L2,L);
		temp = L->next->coef;
		p = L->next;
		while(p){
			p->coef /= temp;
			p = p->next;
		}
		return OK;
	} // 如果有一个是0特殊处理 
	Rem = (LinkList)malloc(LEN);
	Rem->next = NULL;
	do{
		RemList(L1,L2,Rem);
		CopyList(L2,L1);
		CopyList(Rem,L2);
	}while(Rem->next != NULL);
	CopyList(L1,L);
	temp = L->next->coef;
	p = L->next;
	while(p){
		p->coef /= temp;
		p = p->next;
	}
	return OK;
}

Status LcmList(LinkList L1,LinkList L2,LinkList &L)
{ // 求最小公倍式储存在L中
	LinkList Gcd,Mul;
	double temp;
	LNode *p;
	Gcd = (LinkList)malloc(LEN);
	Mul = (LinkList)malloc(LEN);
	Gcd->next = NULL;
	Mul->next = NULL;
	if(L1->next == NULL)
		GcdList(L1,L2,Gcd);  // 保证第二个参数非0 
	else if(L2->next == NULL) 
		GcdList(L2,L1,Gcd);
	else if(L1->next->expn >= L2->next->expn)
		GcdList(L1,L2,Gcd);
	else
		GcdList(L2,L1,Gcd);	
	MulList(L1,L2,Mul);
	DivList(Mul,Gcd,L);
	temp = L->next->coef;
	p = L->next;
	while(p){
		p->coef /= temp;
		p = p->next;
	}
	return OK;
}
LNode *MakeNode(double coef,int expn)
{ // 制造一个结点
	LNode *p; 
	p = (LNode*)malloc(LEN);
	p->coef = coef;
	p->expn = expn;
	p->next = NULL;
	return p; 
} 

void SimpList(LinkList &L)
{ // 将有序多项式中指数相同项合并，然后删除掉系数小于EPS的项
	LNode *p,*q;
	p = L->next;
	while(p->next){  // 合并
		if(p->next && (p->expn == p->next->expn)){
			p->coef += p->next->coef;
			q = p->next;
			p->next = q->next;
			free(q);
		}
		else 
			p = p->next;
}
	p = L;
	while(p->next){  //删除系数<EPS的项
		q = p;
		p = p->next;
		if(fabs(p->coef) < EPS){
			q->next = p->next;
			free(p);			
			p = q;
		}		
	}
}
void ListSort(LinkList &L)  
{ // 将原本无序的链表重组成一个新的有序链表 
	LNode *head;
	LNode *p;
	LNode *pro_min;
	LNode *min;
	head = L->next;
	L->next = NULL;	//分离头结点 
	while(head != NULL){
		for(p=head,min=head;p->next!=NULL;p=p->next){  //for循环按照大小不断找出最小点 
			if(p->next->expn < min->expn){
				pro_min = p;
				min = p->next;
			}
		}
		if(min == head)   //将被选走的点从原链表中删除 
			head = head->next;
		else
			pro_min->next = min->next;
		min->next = L->next;	//将找到的最小点插入到L中 
		L->next = min;	
	}
}

Status CreatePolyn(LinkList *Poly)          
{
	int m,exp;
	double coe;
	LNode *p;
	scanf("%d",&m);
	if(m < 0 || m > 9){
		printf("You give an error number!\n");
		return ERROR;
	}
	if(Poly[m] == NULL) ;
	else if(Poly[m]->next != NULL){
		DestroyList(Poly[m]);
	}
	Poly[m] = (LinkList)malloc(LEN);
	Poly[m]->next = NULL;
	//printf("Please input the coef and expn: coef expn:\n");
	scanf("%lf %d",&coe,&exp);
	do{
		p = (LNode*)malloc(LEN);
		p->coef = coe;	p->expn = exp; 
		p->next = Poly[m]->next;
		Poly[m]->next = p;
	}while(scanf("%lf %d",&coe,&exp) && (exp != 0 || coe != 0));
	ListSort(Poly[m]);
	SimpList(Poly[m]); 
	return OK;
}

Status DestroyPolyn(LinkList *Poly) 
{
	int m;
	LNode *p,*q;
	//printf("Please input a whole number: ");
	scanf("%d",&m);
	if(m<0 || m>9){
		printf("Error input!\n");
		return ERROR; 
	}
	DestroyList(Poly[m]);
}

Status PrintPolyn(LinkList *Poly)
{
	int m;
	LNode *p;
	//printf("Please input a whole number: ");
	scanf("%d",&m);
	if(m < 0 || m > 9){
		printf("You input an error number!\n"); return(ERROR);
	} 
	if(Poly[m] == NULL){
		printf("NULL\n");
		return(0);
	}
	if(Poly[m]->next == NULL){
		printf("0.0000\n");
		return 0;
	}
	p = Poly[m]->next;
	while(p){
		if(p->coef >= 0){
			if(p->expn == 0)	
				printf("%.4lf",p->coef);
			else if(p->expn == 1) 
				printf("%.4lfx",p->coef);
			else 
				printf("%.4lfx^%d",p->coef,p->expn);
				p = p->next;
				if(p != NULL) printf("+");
		}
		else if(p->coef < 0){
			if(p->expn == 0)
				printf("(%.4lf)",p->coef);
			else if(p->expn == 1) 
				printf("(%.4lfx)",p->coef);
			else 
				printf("(%.4lfx^%d)",p->coef,p->expn);
				p = p->next;
				if(p != NULL) printf("+");
		}
	}
	putchar('\n');
	return OK;
}

Status CopyPolyn(LinkList *Poly)
{
	int m1,m2;
	LNode *p,*q,*rear;
	scanf("%d %d",&m1,&m2);
	if((m1<0 || m1>9) || (m2<0 || m2>9) || (m1 == m2) || (Poly[m1]==NULL)){
		printf("Error input!\n"); 
		return ERROR;
	}
	if(Poly[m2] != NULL){
		DestroyList(Poly[m2]);
	}
	CopyList(Poly[m1],Poly[m2]);
	return OK;
} 

Status ClearPolyn(LinkList *Poly)
{
	int m;
	LNode *p,*q;
	scanf("%d",&m);
	if(m<0 || m>9){
		printf("Error input!\n");
		return ERROR;
	}
	if(Poly[m] == NULL){
		printf("This is a NULL List!\n");
		return ERROR;
	}
	ClearList(Poly[m]);
	return OK;
}

Status AddPolyn(LinkList *Poly)
{
	int m1,m2,m3;
	LNode *p,*q,*rear,*v;
	//printf("Please input three whole number m1 m2 m3: ");
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m2) || (m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL)){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	AddList(Poly[m1],Poly[m2],Poly[m3]);
	return OK;
}

Status SubPolyn(LinkList *Poly){
	int m1,m2,m3;
	LNode *p,*q,*rear,*v;
	//printf("Please input three whole number m1 m2 m3: ");
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m2) || (m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL)){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	SubList(Poly[m1],Poly[m2],Poly[m3]);
	return OK;
}

Status Value(LinkList *Poly)
{
	int m;
	double result,x;
	LNode *p;
	//printf("Please input a whole number m and a double x: ");
	scanf("%d %lf",&m,&x);
	if(m<0 || m>9 || Poly[m]==NULL){
		printf("ERROR INPUT!\n");
		return ERROR; 
	}
	result = ValueList(Poly[m],x);
	printf("%.4lf\n",result);
	return OK;	
}

Status ModPolyn(LinkList *Poly)
{
	int m,t,K,i,flag;
	double A;
	LNode *p,*q;
	scanf("%d %d",&m,&t);
	if(m<0 || m>9 || Poly[m]==NULL || t<1 || t>3){
		printf("ERROR INPUT\n!");
		return 0; 
	}
	if(t == 1){
		scanf("%lf %d",&A,&K);
		p = MakeNode(A,K);
		for(q=Poly[m];q->next&&q->next->expn>K;q=q->next){
			;
		} //寻找插入点插入 
		p->next = q->next;
		q->next = p;
		SimpList(Poly[m]);
	}
	else if(t == 2){
		scanf("%d",&K);
		flag = i = 0;
		p = Poly[m];
		while(p->next){ //检测K的合法性 
			p = p->next;
			i++;
			if(p->expn == K){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			printf("ERROR INPUT!\n"); 
			return ERROR;
		}
		ListDelete(Poly[m],i);	
	}
	else if(t == 3){ //检测K的合法性 
		scanf("%lf %d",&A,&K);
		flag = i =0;
			p = Poly[m];
		while(p->next){
			p = p->next;
			i++;
			if(p->expn == K){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			printf("ERROR INPUT!\n");
			return ERROR;
		}
		p->coef = A;
		SimpList(Poly[m]);
}
}

Status DifPolyn(LinkList *Poly)
{
	int m1,m2;
	LNode *p,*rear,*v;
	scanf("%d %d",&m1,&m2);
	if(m1<0 || m2<0 || m1>9 || m2>9 || m1==m2||Poly[m1]==NULL || Poly[m1]->next==NULL){
		printf("ERROR INPUT!\n");
		return ERROR;
	}
	if(Poly[m2] != NULL)
		DestroyList(Poly[m2]);
	Poly[m2] = (LinkList)malloc(LEN);
	Poly[m2]->next = NULL; 
	p = Poly[m1]->next;
	rear = Poly[m2];
	while(p){
		if(p->expn == 0){
			p = p->next;
		}
		else{
		v = MakeNode(p->coef*p->expn,p->expn-1);
		v->next = rear->next;
		rear->next = v;
		rear = v;
		p = p->next;
		}
	}
	return OK;
}

Status IndefintPolyn(LinkList *Poly)
{
	int m1,m2;
	LNode *p,*rear,*v;
	scanf("%d %d",&m1,&m2);
	if(m1<0 || m2<0 || m1>9 || m2>9 || m1==m2 || Poly[m1]==NULL || Poly[m1]->next==NULL){
		printf("ERROR INPUT!\n");
		return ERROR;
	}
	if(Poly[m2] != NULL)
		DestroyList(Poly[m2]);
	Poly[m2] = (LinkList)malloc(LEN);
	Poly[m2]->next = NULL; 
	p = Poly[m1]->next;
	rear = Poly[m2];
	while(p){
		v = MakeNode(p->coef/(p->expn+1),p->expn+1);
		v->next = rear->next;
		rear->next = v;
		rear = v;
		p = p->next;
	}
	return OK;
}

Status IntPolyn(LinkList *Poly)
{
	int m;
	double x1,x2,result;
	LinkList L;
	LNode *p,*v,*rear;
	scanf("%d %lf %lf",&m,&x1,&x2);
	if(m<0 || m>9 || Poly[m]==NULL){
		printf("ERROR INPUT!\n");
		return ERROR;
	}
	L = (LinkList)malloc(LEN);
	L->next = NULL; 
	p = Poly[m]->next;
	rear = L; 	//对多项式求不定积分 
	while(p){
		v = MakeNode(p->coef/(p->expn+1),p->expn+1);
		v->next = rear->next;
		rear->next = v;
		rear = v;
		p = p->next;
	}
	result = 0;
	p = L->next;
	while(p){   //解析解 
		result = result + p->coef * pow(x2,p->expn) - p->coef * pow(x1,p->expn);
		p = p->next;
	}
	printf("%.4lf\n",result);
	DestroyList(L);	
	return OK;
}

Status MulPolyn(LinkList *Poly)
{
	int m1,m2,m3;
	LNode *p,*q,*rear,*v;
	LinkList L;
	//printf("Please input three whole number m1 m2 m3: ");
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m2) || (m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL)){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	MulList(Poly[m1],Poly[m2],Poly[m3]);
	return OK;
}

Status DivPolyn(LinkList *Poly)
{
	int m1,m2,m3;
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL) || fabs(Poly[m2]->next->coef)<=EPS){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	if(Poly[m1]->next==NULL || 	Poly[m1]->next->expn < Poly[m2]->next->expn){ // 如果m1次数比m2低，则得数为0，条件判断不能换序 		
		Poly[m3] = (LinkList)malloc(LEN);
		Poly[m3]->next = NULL;
		return OK;
	}	
	DivList(Poly[m1],Poly[m2],Poly[m3]);
	return OK;
} 

Status RemPolyn(LinkList *Poly)
{
	int m1,m2,m3;
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL) || Poly[m2]->next==NULL){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	if(Poly[m1]->next==NULL || 	Poly[m1]->next->expn < Poly[m2]->next->expn){ // 如果m1次数比m2低，则余式就是m2，条件判断不能换序 
		CopyList(Poly[m2],Poly[m3]);		
		return OK;
	}
	RemList(Poly[m1],Poly[m2],Poly[m3]);
	return OK;
}
Status PowPolyn(LinkList *Poly);

Status GcdPolyn(LinkList *Poly)
{
	int m1,m2,m3;
	scanf("%d %d %d",&m1,&m2,&m3);
	if((m1==m3) || (m2==m3) || (Poly[m1]==NULL) || (Poly[m2]==NULL) || (Poly[m1]->next==NULL && Poly[m2]->next==NULL)){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m3] != NULL) 
		DestroyList(Poly[m3]);
	if(Poly[m1]->next == NULL)
		GcdList(Poly[m1],Poly[m2],Poly[m3]);  // 保证第二个参数非0 
	else if(Poly[m2]->next == NULL) 
		GcdList(Poly[m2],Poly[m1],Poly[m3]);
	else if(Poly[m1]->next->expn >= Poly[m2]->next->expn)
		GcdList(Poly[m1],Poly[m2],Poly[m3]);
	else
		GcdList(Poly[m2],Poly[m1],Poly[m3]);
	return OK; 

}
Status PowPolyn(LinkList *Poly)
{
	int m1,m2,x,i;
	scanf("%d %d %d",&m1,&m2,&x);
	if((m1==m2) || (Poly[m1]==NULL) || m1<0 || m1>9 || m2<0 || m2>9 || x>20){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if(Poly[m2] != NULL) 
		DestroyList(Poly[m2]);
	Poly[m2] = (LinkList)malloc(LEN);
	Poly[m2]->next = NULL;
	CopyList(Poly[m1],Poly[m2]);
	for(i=1;i<x;i++)
		MulList(Poly[m2],Poly[m1],Poly[m2]);
	return OK;
}

Status LcmPolyn(LinkList *Poly)
{
	int m1, m2, m3;
	scanf("%d %d %d", &m1, &m2, &m3);
	if ((m1 == m3) || (m2 == m3) || (Poly[m1] == NULL) || (Poly[m2] == NULL) || (Poly[m1]->next == NULL && Poly[m2]->next == NULL)){
		printf("Wrong Input!\n");
		return ERROR;
	}
	if (Poly[m3] != NULL)
		DestroyList(Poly[m3]);
	LcmList(Poly[m1], Poly[m2], Poly[m3]);
	return OK;
}

Status Sizeyunsuan(LinkList *Poly)
{
	char exp[100],suffix[100];
	int a,b,result,n,m,i;
	n = 1;
	char ch;
	SqStack S;
	char *p;
	InitStack(S);
	scanf("%d",&m);
	scanf("%s",exp);
	getsuffix(exp,suffix);
	p = suffix;
	ch = *p++;
	while(ch!='\0'){
		if(!isoperator(ch)){
			Push(S,ch-'0');
		}
		else{
			Pop(S,b); Pop(S,a);
			operate(Poly[a],ch,Poly[b],Poly[9+n]);
			Push(S,9+n);
			n++;
		}
		ch = *p++;
	}
	Pop(S,result);
	CopyList(Poly[result],Poly[m]);
	DestroyStack(S);
	for(i=10;i<=(9+n-1);i++)
		DestroyList(Poly[i]);
	return OK;

}
