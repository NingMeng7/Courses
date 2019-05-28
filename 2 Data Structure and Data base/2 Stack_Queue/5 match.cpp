#include <stdio.h>
#include <iostream>
#define EPSILON 1e-7
#define INIT_SIZE 200
#define EXPAND_SIZE 50
typedef int status;
typedef struct {
	int *base;
	int *top;
	int stack;
	int stacksize = 200;
}MyStack;


status initStack(MyStack &S);
status destroyStack(MyStack &S);
status StackEmpty(MyStack S);
status Push(MyStack &S, int e);
status Pop(MyStack &S, int &e);
status GetTop(MyStack S, int &e);

status check(char *exp);
status is_left(char ch);
status is_right(char ch);
status match(char a, char b);


int main()
{
	using namespace std;
	char expression[300];
	char ch;
	while (true) {
		cin.getline(expression, 100);
		if (check(expression) == 1) {
			cout << "Match successfully!" << endl;
		}
		else
			cout << "Wrong!" << endl;
	}
	return 0;
}

status InitStack(MyStack &S)
{
	S.base = (int *)malloc(INIT_SIZE * sizeof(int));
	if (!S.base) {
		printf("OVERFLOW!\n");
		return OVERFLOW;
	}
	S.stacksize = INIT_SIZE;
	S.top = S.base;
	return true;
}


status StackEmpty(MyStack S)
{
	if (S.top == S.base)
		return true;
	else return false;
}


status Push(MyStack &S, int e)
{
	if ((S.top - S.base) == S.stacksize) {
		S.base = (int *)realloc(S.base, (S.stacksize + EXPAND_SIZE)*(sizeof(int)));
		if (!S.base) return(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += EXPAND_SIZE;
	}
	*S.top++ = e;
	return true;
}


status Pop(MyStack &S, int &e)
{
	if (S.top == S.base) return false;
	e = *(--S.top);
	return true;
}


status DestroyStack(MyStack &S)
{
	S.top = S.base;
	free(S.base);
	S.stacksize = 0;
	return true;
}


status GetTop(MyStack S, int &e)
{
	if (S.top == S.base)
		return false;
	e = *(S.top - 1);
	return true;
}


status is_left(char ch)
{
	if (ch == '(' || ch == '[' || ch == '{')
		return true;
	else return false;
}


status is_right(char ch)
{
	if (ch == ')' || ch == ']' || ch == '}')
		return true;
	else
		return false;
}


status match(char a, char b)
{
	if (a == '(' && b == ')')
		return true;
	if (a == '[' && b == ']')
		return true;
	if (a == '{' && b == '}')
		return true;
}


status check(char *exp)
{	//	括号匹配
	MyStack S;
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
		return true;
}

