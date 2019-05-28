#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4096 
#define NUL 737
#define MB 404
// 太小中间16位是0怎么办 
typedef unsigned long long int llt;
typedef struct {
	llt data;
	int flag; //flag=0表示空，flag=-1表示墓碑，flag=1表示有数 
}node;
int counts = 0; //成功次数 
int sum_s = 0; //成功比较的次数 
int countf = 0; //失败次数 
int sum_f = 0; //失败比较的次数 
node hash[N];

int hash1(llt x)
{
	x = x * x;
	x >>= 26;
	return x % 4096;
}

int hash2(llt x)
{
	if (x % 2 != 0) return (x % 4096);
	else return ((x + 1) % 4096);
}

void hashinsert(llt a)
{
	int addr = hash1(a);
	int k = 0;
	if (hash[addr].flag == 0 || hash[addr].flag == -1) { // 空的或者墓碑，可以插入 
		k++;
		hash[addr].flag = 1;
		hash[addr].data = a;
		printf("%d %d\n", k, addr);  //k为尝试次数，addr为位置 
		return;
	}
	else {
		k++;
		do {
			addr = (addr + hash2(a)) % 4096;
			k++;
		} while (hash[addr].flag == 1); //冲突就一直找下去 
	}
	hash[addr].flag = 1;
	hash[addr].data = a;
	printf("%d %d\n", k, addr);
}

void hashsearch(llt a)
{
	int addr = hash1(a);
	int k = 0;
	if (hash[addr].flag == 1 && hash[addr].data == a) { //如果有数并且就是a 
		hash[addr].flag = -1; //置为墓碑 
		hash[addr].data = 0;
		k++;
		printf("%d %d\n", k, addr);
		counts++;		    //成功的次数++ 
		sum_s = sum_s + k; //成功所需的比较次数加上k 
		return;
	}
	else if (hash[addr].flag == 0) { //空
		k++;
		printf("%d %d\n", k, -1);
		countf++;
		sum_f = sum_f + k;
		return;
	}
	else { //这个点为墓碑或者冲突
		k++;
		do {
			addr = (addr + hash2(a)) % 4096; //
			k++;
			if (hash[addr].flag == 1 && hash[addr].data == a) {
				hash[addr].flag = -1;
				hash[addr].data = 0;
				counts++;
				sum_s = sum_s + k;
				printf("%d %d\n", k, addr);
				return;
			}
			else if (hash[addr].flag == 0) {
				printf("%d %d\n", k, -1);
				countf++;
				sum_f = sum_f + k;
				return;
			}
		} while (1); //冲突或者墓碑就一直往后走，有且为a，有不为a（冲突），墓碑，空 
	}
}

int main()
{
	llt a;
	int b, i, j;
	for (i = 0; i<N; i++)
		hash[i].flag = 0;
	for (i = 0; i<10000; i++) {
		scanf("%lld %d", &a, &b);
		if (b == 1) {
			hashinsert(a);
		}
		else {
			hashsearch(a);
		}
	}
	printf("%d/%d\n", sum_s, counts);
	printf("%d/%d\n", sum_f, countf);
	return 0;

}
