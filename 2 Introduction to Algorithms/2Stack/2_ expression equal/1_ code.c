#include "stdio.h"
#include "stdlib.h"
#include "math.h" 
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERLOW -2
#define LEN
#define INIT_SIZE 10000 
#define EXPAND_SIZE 100
#define eps 1e-6
int mod = 1007;


typedef struct {
	int *base;
	int *top;
	int stacksize;
}SqStack;

typedef struct {
	long long int *base;
	long long int *top;
	int stacksize;
}SqStackL;
typedef int status;

status InitStack(SqStack &S);
status DestroyStack(SqStack &S);
status StackEmpty(SqStack S);
status Push(SqStack &S, int e);
status Pop(SqStack &S, int &e);
status GetTop(SqStack S, int &e);

status InitStack_L(SqStackL &S);
status DestroyStack_L(SqStackL &S);
status StackEmpty_L(SqStackL S);
status Push_L(SqStackL &S, long long int e);
status Pop_L(SqStackL &S, long long int &e);

status check(char *exp);
status is_left(char ch);
status is_right(char ch);
status match(char a, char b);

status equal(char *a, char *b);
status isoperator(char ch);
void getsuffix(char exp[], char suffix[]);
long long int operateL(long long int a, char ch, long long int b);
long long int caculateL(char *exp, long long int x0);
status preop(char c, char ch);


int main()
{
	int n;
	scanf("%d", &n);
	char c[n + 1][10000];
	int i, count = 0;
	getchar();
	for (i = 0; i <= n; i++)
		gets(c[i]);
	for (i = 1; i <= n; i++) {
		if ((check(c[i])) != 1)
			c[i][0] = '\0';
	}

	for (i = 1; i <= n; i++) {
		if (c[i][0] == '\0')
			continue;
		if (equal(c[0], c[i]))
			printf("%c", 'A' + i - 1);
	}

	return 0;
}


status InitStack(SqStack &S)
{
	S.base = (int *)malloc(INIT_SIZE * sizeof(int));
	if (!S.base) {
		printf("OVERFLOW!\n");
		return OVERFLOW;
	}
	S.stacksize = INIT_SIZE;
	S.top = S.base;
	return OK;
}


status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else return FALSE;
}


status Push(SqStack &S, int e)
{
	if ((S.top - S.base) == S.stacksize) {
		S.base = (int *)realloc(S.base, (S.stacksize + EXPAND_SIZE)*(sizeof(int)));
		if (!S.base) return(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += EXPAND_SIZE;
	}
	*S.top++ = e;
	return OK;
}


status Pop(SqStack &S, int &e)
{
	if (S.top == S.base) return ERROR;
	e = *(--S.top);
	return OK;
}


status DestroyStack(SqStack &S)
{
	S.top = S.base;
	free(S.base);
	S.stacksize = 0;
	return OK;
}


status GetTop(SqStack S, int &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *(S.top - 1);
	return OK;
}


status is_left(char ch)
{
	if (ch == '(' || ch == '[' || ch == '{')
		return TRUE;
	else return FALSE;
}


status is_right(char ch)
{
	if (ch == ')' || ch == ']' || ch == '}')
		return TRUE;
	else
		return FALSE;
}


status match(char a, char b)
{
	if (a == '(' && b == ')')
		return TRUE;
	if (a == '[' && b == ']')
		return TRUE;
	if (a == '{' && b == '}')
		return TRUE;
}


status check(char *exp)
{	//	括号匹配
	SqStack S;
	int ch, left;
	char *p = exp;
	InitStack(S);
	while ((ch = *p) != '\0') {
		if (is_left(ch))
			Push(S, ch);
		else if (is_right(ch)) {
			if (!Pop(S, left))
				return -1;
			if (!match(left, ch))
				return -2;
		}
		p++;
	}
	if (!StackEmpty(S))
		return -3;
	else
		return TRUE;
}


status isoperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^' || ch == '\0')
		return TRUE;
	return FALSE;
}


status preop(char c, char ch)
{
	int p[8][8] = { { 1,1,-1,-1,-1,-1,1,1 },{ 1,1,-1,-1,-1,-1,1,1 },{ 1,1,1,1,-1,-1,1,1 },{ 1,1,1,1,-1,-1,1,1 },{ 1,1,1,1,1,-1,1,1 },{ -1,-1,-1,-1,-1,-1,0,0 },
	{ 1,1,1,1,1,0,1,1 },{ -1,-1,-1,-1,-1,-1,0,0 } };
	int i, j;
	switch (c) {
	case'+': i = 0; break;
	case'-': i = 1; break;
	case'*': i = 2; break;
	case'/': i = 3; break;
	case'^': i = 4; break;
	case'(': i = 5; break;
	case')': i = 6; break;
	case'\0': i = 7; break;
	}
	switch (ch) {
	case'+': j = 0; break;
	case'-': j = 1; break;
	case'*': j = 2; break;
	case'/': j = 3; break;
	case'^': j = 4; break;
	case'(': j = 5; break;
	case')': j = 6; break;
	case'\0': j = 7; break;
	}
	return p[i][j];
}


long long int  operateL(long long int a, char ch, long long int b)
{
	long long int i, temp = 1;
	switch (ch) {
	case '+': return (a % mod + b % mod) % mod; break;
	case '-': return (a % mod - b % mod + mod) % mod; break;
	case '*': return (a * b) % mod; break;
	case '/': return a / b; break;
	case '^': for (i = 1; i <= b; i++)
		temp = (temp * a) % mod;
		return temp; break;
	}
	return FALSE;
}


void getsuffix(char exp[], char suffix[])
{
	SqStack S;
	InitStack(S);
	Push(S, '\0');
	int k = 0, ch, c, e, d;
	char *p;
	p = exp;
	ch = *p++;
	while (!(ch == '\0' && d == '\0')) {
		if (ch == ' ') {
			ch = *p++;
			continue;
		}
		if (!isoperator(ch)) {
			suffix[k++] = ch;
			ch = *p++;
			if (isoperator(ch) || ch == ' ') {
				suffix[k++] = ' ';
			}
			GetTop(S, d);

		}
		else {
			GetTop(S, c);
			switch (preop(c, ch)) {
			case -1: Push(S, ch); ch = *p++;	GetTop(S, d); break;
			case 0:  Pop(S, e);   ch = *p++; GetTop(S, d); break;
			case 1:  Pop(S, c); 	 suffix[k++] = (char)c; GetTop(S, d); break;
			}
		}
	}
	suffix[k++] = '\0';
}


status equal(char a[], char b[])
{
	long long int test[50] = { 0,1,25,100 };
	int count = 0;
	char suf_a[10000], suf_b[10000];
	long long int i;
	getsuffix(a, suf_a);
	getsuffix(b, suf_b);
	for (i = 0; i <= 3; i = i + 1) {
		if (caculateL(suf_a, test[i]) != caculateL(suf_b, test[i]))
			return FALSE;
	}

	return TRUE;
}



status InitStack_L(SqStackL &S)
{
	S.base = (long long int *)malloc(INIT_SIZE * sizeof(long long int));
	if (!S.base) {
		printf("OVERFLOW!\n");
		return OVERFLOW;
	}
	S.stacksize = INIT_SIZE;
	S.top = S.base;
	return OK;
}



status Push_L(SqStackL &S, long long int e)
{
	
	if ((S.top - S.base) == S.stacksize) {
		S.base = (long long int *)realloc(S.base, (S.stacksize + EXPAND_SIZE)*(sizeof(long long int)));
		if (!S.base) return(OVERFLOW);
		S.top = S.base + S.stacksize;  //  
		S.stacksize += EXPAND_SIZE;
	}
	*S.top++ = e;
	return OK;
}


status Pop_L(SqStackL &S, long long int &e)
{
	if (S.top == S.base) return ERROR;
	e = *(--S.top);
	return OK;
}


long long int caculateL(char *suffix, long long int x0)
{
	long long int a, b, e, result, temp;
	char ch;
	SqStackL S;
	char *p = suffix;
	InitStack_L(S);
	ch = *p;
	while (ch != '\0') {
		if (!isoperator(ch)) {
			temp = 0;
			while (ch != ' ' && !(isoperator(ch))) {
				if (ch == 'x') {
					temp = temp * 10 + (x0);
					ch = *(++p);
				}
				else {
					temp = temp * 10 + (ch - '0');
					ch = *(++p);
				}
			}
			Push_L(S, temp);
			p++;
		}
		else {
			Pop_L(S, b); Pop_L(S, a);
			Push_L(S, operateL(a, ch, b));
			p++;
		}
		ch = *p;
	}
	Pop_L(S, result);
	//printf("the result is:%lf\n",result);
	return result;
}
