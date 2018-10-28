#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define RADIX 16
typedef struct {
	int keys[4];
	int data;
}Node;

int n;

void Getkey(Node &c)
{
	int temp = c.data;
	int i;
	for(i=0;i<=3;i++){
		c.keys[i] = temp % RADIX;
		temp /= RADIX;
	}
}

void RadixPass(Node a[],Node b[],int n,int i)
{
	int j,k;
	int count[RADIX] = {0};
	for(k=1;k<=n;k++) 
		count[a[k].keys[i]]++;
	for(j=1;j<RADIX;j++) 
		count[j] += count[j-1];
	for(k=n;k>=1;k--) {
		j = a[k].keys[i];
		b[count[j]] = a[k]; count[j]--;
	}	
}

void Print(Node a[])
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d ",a[i].data);
	putchar('\n');
}

void RadixSort(Node a[])
{
	Node C[n+1];
	int i=0,j;
	while(i<=3) {
		RadixPass(a,C,n,i);	i++;
		Print(C);
	if(i<=3) {
		RadixPass(C,a,n,i); i++;
		Print(a);
	}
	else
		for(j=1;j<=n;j++)
			a[j] = C[j];
}
}

int main()
{
	int i,j;
	scanf("%d",&n);
	Node a[n+1];
	for(i=1;i<=n;i++)	{
		scanf("%d",&(a[i].data));
		Getkey(a[i]);
	}
	RadixSort(a);
	for(i=1;i<=n;i++)
		printf("%d ",a[i].data);
	return 0;
}
