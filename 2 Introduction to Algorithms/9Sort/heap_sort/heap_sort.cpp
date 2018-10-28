#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

int count, m;
void HeapAdjust(int R[], int s, int m)
{ //H.R[s+1...m]满足大顶堆定义调整使得H.R[s...m]满足大顶堆定义 
  //完全二叉树,i- 2i为左孩子 2i+1为右孩子，每个结点比孩子都大为大顶堆 
	int temp, j;
	temp = R[s];
	for (j = 2 * s; j <= m; j *= 2) {
		if (j<m && R[j] < R[j + 1])	++j;
		if (temp > R[j])	break;
		R[s] = R[j]; s = j; //保存一个副本，然后大的就可以依次上浮 
	}
	R[s] = temp;
}

void HeapSort(int R[], int length)
{
	int i, j, temp, k;
	for (i = length / 2; i >= 1; i--) {
		HeapAdjust(R, i, length);
	}

	for (k = 1; k <= length; k++)
		printf("%d ", R[k]);
	putchar('\n');

	for (j = length; j>1; j--) { //右侧是有序区 
		temp = R[j];	R[j] = R[1];	R[1] = temp;
		HeapAdjust(R, 1, j - 1);
		count--;
		if (count == m) {
			for (k = 1; k <= length; k++)
				printf("%d ", R[k]);
			putchar('\n');
		}

	}
}

int main()
{
	int n, i;
	scanf("%d %d", &n, &m);
	int a[n + 1];
	count = n;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	HeapSort(a, n);
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}
