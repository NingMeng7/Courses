#include "stdio.h"
#include "stdlib.h"
#include "math.h" 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  //不可实现 
#define OVERLOW -2
#define N 900000 

typedef int state;
int cake[N], sortcake[N];
void Select_sort(int a[], int n);
state BinSearch(int cake[], int k, int len);
void F_sort(int sortcake[], int low, int hig);

int main()
{
	int n, m, i, j, k, a, b, len, flag, temp;
	char c;
	scanf("%d", &n);
	len = n;
	//int cake[n+1],sortcake[n+1];
	for (i = 1; i <= n; i++) {
		scanf("%d", &cake[i]);
	}
	for (i = 1; i <= n; i++)
		sortcake[i] = cake[i];
	scanf("%d", &m);
	getchar();
	F_sort(sortcake, 1, n); //sortcake中饼干数目大->小 
	for (i = 1; i <= m; i++) {
		scanf("%c", &c);

		// 
		if (c == 'Q') { //查询饼干第k多的饼干盒子里的饼干数目 
			scanf("%d", &k);
			getchar();
			if (len<k)
				printf("%d\n", -1); //不足k个就输出-1 
			else {
				printf("%d\n", sortcake[k]); // 第k多 
			}
		}
		//

		// 
		else if (c == 'A') { //从a盒中取b块 
			scanf("%d %d", &a, &b);
			getchar();
			flag = BinSearch(sortcake, cake[a], len); //记录下a号盒子在有序排列情况下的下标 
			cake[a] = cake[a] - b;
			if (cake[a] <= 0) {
				cake[a] = -1;  // -1代表这个盒子被丢掉了 
				if (len>0)
					len--;	//丢了一个盒子，盒子数目-1 
			}
			sortcake[flag] = cake[a];
			temp = sortcake[flag];
			for (j = flag; sortcake[j]<sortcake[j + 1] && j < n; j++) {
				sortcake[j] = sortcake[j + 1];
				sortcake[j + 1] = temp;
			} //把cake[a]对应的盒子放到有序的位置上去 
		}
		//

		// 
		else { //向a盒中放b块 
			scanf("%d %d", &a, &b);
			getchar();
			flag = BinSearch(sortcake, cake[a], len); //记录下a号盒子在有序排列情况下的下标 
			cake[a] = cake[a] + b;
			sortcake[flag] = cake[a];
			temp = sortcake[flag];
			for (j = flag; sortcake[j]>sortcake[j - 1] && j>1; j--) {
				sortcake[j] = sortcake[j - 1];
				sortcake[j - 1] = temp;
			} //把cake[a]对应的盒子放到有序的位置上去
		}
		// 
	}
	printf("%d", len);
	return 0;
}

state BinSearch(int cakesort[], int kval, int len)
{ // len为当前饼干盒子的个数，约定0号下标不用 
	int bot = 1, top = len, mid;
	while (bot <= top) {
		mid = (bot + top) / 2;
		if (cakesort[mid] == kval)
			return mid;
		else {
			if (cakesort[mid] > kval)
				bot = mid + 1; //在右半区 
			else
				top = mid - 1; //在左半区 
		}
	}
	return 0;
}

void F_sort(int sortcake[], int low, int hig) {
	if (low >= hig)  return;
	int i = low, j = hig, kval = sortcake[low];
	while (i < j) {
		while (i < j && kval >= sortcake[j])
			j--;
		sortcake[i] = sortcake[j];
		while (i < j && kval <= sortcake[i])
			i++;
		sortcake[j] = sortcake[i];
	}
	sortcake[i] = kval;
	F_sort(sortcake, low, i - 1);
	F_sort(sortcake, i + 1, hig);
}


void Select_sort(int a[], int n)
{
	//将a[]中整数序列自大到小排列 
	long int i, j, k;
	int temp;
	for (i = 1; i<n; i++) { // i从0->n-1 遍历 
		j = i;
		for (k = i + 1; k <= n; k++) {
			if (a[k] > a[j]) j = k; // 对i右侧元素进行扫描，用j记录下当前最小元素位置 
		}
		if (j != i) {        // 如果i不是最小的，把最小的j和i进行交换 
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
}
