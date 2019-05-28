#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

int const N = 23;
int const NUL = 9999;
int const MB = 8888;
int const di = 1;
double load_factor = 0.74;

int const test_data[] = { 43,71,93,35,89,05,38,90,61,30,54,39,76,85,63,22,45 };
int const remain[] = { 20, 2, 1, 12, 20, 5, 15, 21, 15, 7, 8, 16, 7, 16, 17, 22, 22 };
int const test_failure[] = { 0, 1, 2, 3,4,28,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,68 };
int counts = 0; //成功次数 
int sum_s = 0; //成功比较的次数 
int countf = 0; //失败次数 
int sum_f = 0; //失败比较的次数 
int hash[N];

bool is_clash(int x) 
{
	if (x != NUL && x != MB) {
		return true;
	}
	return false;
}

void print_hash()
{
	using std::cout;
	using std::endl;
	int i;
	for (i = 0; i < N; ++i) {
		if (hash[i] == NUL) {
			cout << "NUL\t";
		}
		else if (hash[i] == MB) {
			cout << "MB\t";
		}
		else
			cout << hash[i] << "\t";
	}
	cout << endl;
}

int hash1(int x)
{
	return x % N;
}

int hash2(int x)
{
	return di;
}

void hashinsert(int a)
{
	int addr = hash1(a);
	if (!is_clash(hash[addr])) { // 空的或者墓碑，可以插入 
		hash[addr] = a;
		return;
	}
	else {
		do {
			addr = (addr + hash2(a)) % N;
		} while (is_clash(hash[addr])); //冲突就一直找下去 
	}
	hash[addr] = a;
}

void hashdelete(int a)
{
	int addr = hash1(a);
	int k = 0;
	if (is_clash(hash[addr] && hash[addr] == a)) { //如果有数并且就是a 
		hash[addr] = MB;
		return;
	}
	else if (hash[addr] == NUL) { //空
		return;
	}
	else { //这个点为墓碑或者冲突
		do {
			addr = (addr + hash2(a)) % N; //
			k++;
			if (is_clash(hash[addr]) && hash[addr] == a) {
				hash[addr] = MB;
				return;
			}
			else if (hash[addr] == NUL) {
				return;
			}
		} while (1); //冲突或者墓碑就一直往后走，有且为a，有不为a（冲突），墓碑，空 
	}
}

void hashsearch(int a)
{
	int addr = hash1(a);
	int k = 0;
	if (is_clash(hash[addr]) && hash[addr] == a) { //如果有数并且就是a 
		k++;
		counts++;		    //成功的次数++ 
		sum_s = sum_s + k; //成功所需的比较次数加上k 
		return;
	}
	else if (hash[addr] == NUL) { //空
		k++;
		countf++;
		sum_f = sum_f + k;
		return;
	}
	else { //这个点为墓碑或者冲突
		k++;
		do {
			addr = (addr + hash2(a)) % N; //
			k++;
			if (is_clash(hash[addr]) && hash[addr] == a) {
				counts++;
				sum_s = sum_s + k;
				//	printf("%d %d\n", k, addr);
				return;
			}
			else if (hash[addr] == NUL) {
				//	printf("%d %d\n", k, -1);
				countf++;
				sum_f = sum_f + k;
				return;
			}
		} while (1); //冲突或者墓碑就一直往后走，有且为a，有不为a（冲突），墓碑，空 
	}
}


int main()
{
	using std::endl;
	using std::cout;
	int i;
	for (i = 0; i<N; i++)
		hash[i] = NUL;
	for (i = 0; i < 17; i++) {
		hashinsert(test_data[i]);
	}
	for (i = 0; i < 17; i++) {
		hashsearch(test_data[i]);
	}
	for (i = 0; i < N; i++) {
		hashsearch(test_failure[i]);
	}
/*
	for (i = 0; i < 17; i++) {
		cout << remain[i] << "\t";
	}
	cout << endl;
	print_hash();

	printf("%d/%d\n", sum_s, counts);
	printf("%d/%d\n", sum_f, countf);
	*/
	print_hash();
	hashdelete(test_data[1]);
	print_hash();

	while (1);
	return 0;
}