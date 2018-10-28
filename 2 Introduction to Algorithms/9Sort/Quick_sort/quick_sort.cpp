#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

void QuickSort(int R[], int low, int hig)
{  //用左i和右j扫描，首先用kval保存副本，然后交换依次让ij扫描 
	if (low >= hig)  return;        // kval 是轴值  
	int i = low, j = hig, kval = R[low]; //以R[low]为轴值 
	while (i < j) {
		while (i < j && kval <= R[j]) //[low](i)被保存，因此j要先跑 
			j--;
		R[i] = R[j];
		while (i < j && kval >= R[i])
			i++;
		R[j] = R[i];
	}
	R[i] = kval; //轴值居中，左边比轴值小，右边比轴值大 
	if (low != hig)
		printf("%d %d\n", low, hig);
	QuickSort(R, low, i - 1);
	QuickSort(R, i + 1, hig);
}

int main()
{
	int n, i;
	scanf("%d", &n);
	int a[n + 1];
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	QuickSort(a, 1, n);
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}
