#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

int m;

void ShellSortB(int R[],int incr,int length)
{//incr为增量,即[1,1+incr,1+2incr...] [2,2+incr,2+2incr...]为子表 
	int i,j;
	for(i=incr+1;i<=length;i++) { // 子表的排序是互相穿插的 
		if(R[i]<R[i-incr]){ //对每个子表而言左侧是有序区，逐渐扩大有序区 
			R[0] = R[i];
			for(j=i-incr;j>0 && R[0]< R[j];j-=incr) //由于不一定最终会和0号下标比，不能单纯用哨兵 
				R[j+incr] = R[j];
			R[j+incr] = R[0];
		}
	}
}

void ShellSortA(int R[],int inc[],int length)
{
	int i,j;
	for(i=1;i<=m;i++){
		ShellSortB(R,inc[i],length);
		for(j=1;j<=length;j++) {
			printf("%d ",R[j]);
		}
		putchar('\n');
	}
}

int main()
{
	int n,i;
	scanf("%d %d",&n,&m);
	int a[n+1],incr[m+1];
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
	}
	for(i=1;i<=m;i++) {
		scanf("%d",&incr[i]);
	}
	ShellSortA(a,incr,n);	
	return 0;
}
