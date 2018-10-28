#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define N  13 
void monkeySort(int a[],int n);
int main()
{
	int i,count=0;
	int a[N];
	for(i=0;i<N;i++) {
		scanf("%d",&a[i]);
	}
	printf("Before Sort:\n");
	for(i=0;i<N;i++) {
		printf("%4d",a[i]);
	}
	putchar('\n');
	monkeySort(a,N);
	printf("After Sort:\n");
	for(i=0;i<N;i++) {
		printf("%4d",a[i]);
	}
	putchar('\n');
	return 0;
}

int isok(int a[],int n)
{
	int i,flag = 1;
	for(i=0;i<=n-2;i++) {
		if(a[i] > a[i+1]) {
			flag = 0;
			break;
		}
	}
	return flag; 
}
void monkeySort(int a[],int n)
{
	int i,flag,x,y,temp;
	time_t start,end;
	flag = 0;
	start = time(NULL);
	while(!flag) {
		x = rand()%n;
		y = rand()%n;
		
		temp = a[x];
		a[x] = a[y];
		a[y] = temp;
		flag = isok(a,n);
	}
	end = time(NULL);
	printf("time:%d \n",start - end);
}
