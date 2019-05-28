#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stack>

typedef int status;
int judge(char ch);
using namespace std;

void print(stack<char> Stack)
{
	stack<char> inverStack;
	while (!Stack.empty()) {
		inverStack.push(Stack.top());
		Stack.pop();
	}
	while (!inverStack.empty()) {
		cout << inverStack.top();
		inverStack.pop();
	}
}

void clear(stack<char> &Stack)
{
	while (!Stack.empty()) {
		Stack.pop();
	}
}
int main()
{
	using namespace std;
	char ch;
	stack<char> Stack;
	ch = cin.get();
	while (ch != EOF) {
		switch (judge(ch)) {
		case 1: Stack.pop(); break;
		case 2: clear(Stack); break;
		case 3: print(Stack); clear(Stack);break;
		default: Stack.push(ch);
		}
		ch = cin.get();
	}

	while (1);
	return 0;
}


int judge(char ch)
{
	if (ch == '#') {
		return 1;
	}
	if (ch == '@') {
		return 2;
	}
	if (ch == '\n') {
		return 3;
	}
	return -1;
}
