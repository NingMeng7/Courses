#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stack>

typedef int status;
status isoperator(char ch);
status preop(char c, char ch);
void process(char * expression, char * new_expression);
int operate(int a, char ch, int b);
int evaluate(char * expression);
using namespace std;

int main()
{
	using namespace std;
	char expression[300];
	char new_expression[300];
	char ch;
	double result;
	//cin >> ch;
	//getchar();
	//while (ch != 'q') {
	cin.getline(expression, 300);

	process(expression, new_expression);
	result = evaluate(new_expression);
	cout << "The result is: " << result << " \n";
	//}
	while (1);
	return 0;
}


void process(char * expression, char new_expression[])
{
	int k = 0;
	char *p = expression;
	while (*p != '\0') {
		if (!('0' <= *p && '9' >= *p)) {
			if (*p == ' ')
				;
			else
				new_expression[k++] = *p;
			
		}
		else {
			if (!('0' <= *(p + 1) && '9' >= *(p + 1))) {
				new_expression[k++] = *p;
				new_expression[k++] = ' ';
			}
			else
				new_expression[k++] = *p;
		}
		p++;
	}
	new_expression[k] = '\0';
	cout << new_expression;
}

status isoperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^' || ch == '\0')
		return true;
	return false;
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


int operate(int a, char ch, int b)
{
	int temp = 1;
	switch (ch) {
	case '+': return (a + b); break;
	case '-': return (a - b); break;
	case '*': return (a * b); break;
	case '/': return (a / b); break;
	case '^': return pow(a, b); break;
	}
	return false;
}



int evaluate(char *suffix)
{
	int a, b,c, e, result, temp, d;
	char ch, flag;
	int count;
	stack<int> mystack_operand;
	stack<char> mystack_operator;  
	mystack_operator.push('\0');
	char *p = suffix;
	ch = *(p++);
	while (!(ch == '\0' && d == '\0')) {
		if (!isoperator(ch)) {
			temp = 0;
			while (ch != ' ' && !(isoperator(ch))) {
				temp = temp * 10 + (ch - '0');
				ch = *(p++);
			}
			mystack_operand.push(temp);
			ch = *(p++);
		}
		else {
			c = mystack_operator.top();
			switch (preop(c, ch)) {
			case -1: mystack_operator.push(ch); ch = *p++;	d = mystack_operator.top(); break;
			case 0:  e = mystack_operator.top(); mystack_operator.pop();   ch = *p++; d = mystack_operator.top(); break;
			case 1:  c = mystack_operator.top(); mystack_operator.pop();
				b = mystack_operand.top(); mystack_operand.pop();
				a = mystack_operand.top(); mystack_operand.pop();
				mystack_operand.push(operate(a, c, b));
				d = mystack_operator.top(); break;
			}
		}
	}
	result = mystack_operand.top();
	mystack_operand.pop();
	return result;
}