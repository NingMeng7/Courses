#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

int const N = 23;
int const NUL = 9999;
int const MB = 8888;
int const di = 1;
double load_factor = 0.74;

typedef struct node{
	int data;
	node * next;
}node;

int const test_data[] = { 43,71,93,35,89,05,38,90,61,30,54,39,76,85,63,22,45 };
int const remain[] = { 20, 2, 1, 12, 20, 5, 15, 21, 15, 7, 8, 16, 7, 16, 17, 22, 22 };
int const test_failure[] = { 0, 1, 2, 3,4,28,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,68 };
int counts = 0; //成功次数 
int sum_s = 0; //成功比较的次数 
int countf = 0; //失败次数 
int sum_f = 0; //失败比较的次数 
node * hash[N];


int hash1(int x)
{
	return x % N;
}

void hashinsert(int a)
{
	node * p, *q;
	int addr = hash1(a);
	if (hash[addr]) {
		p = hash[addr];
;		while (p->next) {
			p = p->next;
		}
		q = new node;
		q->data = a;
		q->next = NULL;
		p->next = q;
		return;
	}
	else {
		hash[addr] = new node;
		q = new node;
		q->data = a;
		q->next = NULL;
		hash[addr]->next = q;
	}
}

void hashsearch(int a)
{
	int addr = hash1(a);
	int k = 0;
	node * p;
	if (!hash[addr]) { // 为空
		k++;
		countf++;
		sum_f = sum_f + k;
		return;
	}
	else{ // 空
		p = hash[addr];
		k++;
		while (p->next && p->next->data != a) {
			p = p->next;
			k++;
		}
		if (!p->next) {
			countf++;
			sum_f = sum_f + k;
			return;
		}
		else {
			counts++;
			sum_s = sum_s + k;
		}
		return;
	}
}


int main()
{
	using std::endl;
	using std::cout;
	int i;
	for (i = 0; i<N; i++)
		hash[i] = NULL;
	for (i = 0; i < 17; i++) {
		hashinsert(test_data[i]);
	}
	cout << "1" << endl;
	for (i = 0; i < 17; i++) {
		hashsearch(test_data[i]);
	}
	cout << "2" << endl;
	for (i = 0; i < N; i++) {
		hashsearch(test_failure[i]);
	}

	printf("%d/%d\n", sum_s, counts);
	printf("%d/%d\n", sum_f, countf);
	
	while (1);
	return 0;
}