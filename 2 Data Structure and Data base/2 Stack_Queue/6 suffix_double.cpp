#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stack>

#define EPSILON 1e-7

typedef int status;
status isoperator(char ch);
status preop(char c, char ch);
double operate(double a, char ch, double b);
void getsuffix(char exp[], char suffix[]);
double evaluate(char * expression);

using namespace std;

int main()
{
	using namespace std;
	char expression[300];
	char suffix[300];
	char ch;
	double result;
	//cin >> ch;
	//getchar();
	//while (ch != 'q') {
	while (true) {
		cin.getline(expression, 300);
		getsuffix(expression, suffix);
		result = evaluate(suffix);
		cout << "The result is: " << result << " \n";
		//}
	}
	while (1);
	return 0;
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


double operate(double a, char ch, double b)
{
	double temp = 1;
	switch (ch) {
	case '+': return (a + b); break;
	case '-': return (a - b); break;
	case '*': return (a * b); break;
	case '/': return (a / b); break;
	case '^': return pow(a, b); break;
	}
	return false;
}


void getsuffix(char exp[], char suffix[])
{
	stack<char> SOP;
	SOP.push('\0');
	int k = 0, ch, c, e, d;
	char *p;
	p = exp;
	ch = *p++;
	while (!(ch == '\0' && d == '\0')) {
		if (ch == ' ') {
			ch = *p++;
		}	//	Deal with the blank
		if (!isoperator(ch)) {
			suffix[k++] = ch;
			ch = *p++;
			if (isoperator(ch) || ch == ' ') {
				suffix[k++] = ' ';
			}
			d = SOP.top();

		}
		else {
			c = SOP.top();
			switch (preop(c, ch)) {
			case -1: SOP.push(ch); ch = *p++;	d = SOP.top(); break;
			case 0:  e = SOP.top(); SOP.pop();   ch = *p++; d = SOP.top(); break;
			case 1:  c = SOP.top(); SOP.pop();   suffix[k++] = (char)c; d = SOP.top(); break;
			}
		}
	}
	suffix[k++] = '\0';
	cout << suffix << endl;
}


double evaluate(char *suffix)
{
	double a, b, e, result, temp;
	char ch, flag;
	int count;
	stack<double> SOP;
	char *p = suffix;
	ch = *(p);
	while (ch != '\0') {
		if (ch == ' ') {
			ch = *(++p);
			continue;
		}
		else if (!isoperator(ch)) {
			temp = 0;
			count = 0;
			flag = 0;
			while (ch != ' ' && !(isoperator(ch))) {
				if (ch == '.') {
					flag = 1;
					ch = *(++p);
				}
				temp = temp * 10 + (ch - '0');
				ch = *(++p);
				if (flag == 1)
					count++;
			}
			p++;
			temp = temp / pow(10, count);
			SOP.push(temp);
		}
		else {
			b = SOP.top(); SOP.pop();
			a = SOP.top(); SOP.pop();

			SOP.push(operate(a, ch, b));
			p++;
		}
		ch = *p;
	}
	result = SOP.top();
	SOP.pop();
	//printf("the result is:%lf\n",result);
	return result;
}