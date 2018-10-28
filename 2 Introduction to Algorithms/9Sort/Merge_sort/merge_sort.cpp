#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
int n,count = 0;

void Merge(int a[],int temp[],int first,int mid,int last)
{
	int i = first,j,k;
	for(k=i,j=mid+1;i<= mid && j<=last;k++){
		if(a[i] <= a[j])
			temp[k] = a[i++];
		else {
			temp[k] = a[j++];
			count += mid - i + 1;			
		}
	} 
	while(i <= mid)
		temp[k++] = a[i++];
	while(j <= last)
		temp[k++] = a[j++];
}

void MeSort(int a[],int b[],int first,int last)
{
	int temp[n+1],mid;
	if(first == last)
		b[first] = a[first];
	else {
		mid = (first + last) / 2;
		MeSort(a,temp,first,mid);
		MeSort(a,temp,mid+1,last);
		Merge(temp,b,first,mid,last);
	}
}

void MergePass2(int a[],int b[],int s,int n)
{ //a[]中长度为s的序列已经有序，处理它为2s有序 
	int i = 1;
	while(i+2*s-1 <= n) {
		Merge(a,b,i,i+s-1,i+2*s-1);
		i += 2*s;
	}
	if(i+s-1 < n)
		Merge(a,b,i,i+s-1,n);
	else 
		while(i<=n) {
			b[i] = a[i]; i++;
		}
}

void MeSort2(int a[],int length)
{
	int b[length+1];
	int s= 1;
	while(s<n) {
		MergePass2(a,b,s,length);
		s *= 2;
		MergePass2(b,a,s,n);
		s *= 2;
	}
}

int main()
{
	int i,j;
	scanf("%d",&n);
	int a[n+1],b[n+1];
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]); 
	}
	
/*	for(i=1;i<=n;i++) {
		for(j=i+1;j<=n;j++) {
			if(a[i] > a[j])
				count++;
		}
	}*/
	MeSort2(a,n);
	for(i=1;i<=n;i++) {
		printf("%d ",a[i]);
	}	
	putchar('\n');
	printf("%d \n",count); 
}
