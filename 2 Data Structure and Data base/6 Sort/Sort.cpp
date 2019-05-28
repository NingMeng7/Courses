#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<time.h>

int const test_data[] = { 43,71,93,35,89,05,38,90,61,30,54,39,76,85,63,22,45 };
int  standard[] = { 5,22,30,35,38,39,43,45,54,61,63,71,76,85,89,90,93 };
int const M = 17;
int const N = 50000;
double time_[8];
int a[N + 1] = {};	//	Data for comparison
int R[N + 1] = {};

bool test(int before[], int after[], int n);
void print(int a[], int n);
void print_time();
void init();

void InsertSort(int a[], int n);
void BiInsertSort(int R[], int n);
void ShellSortB(int R[], int incr, int length);
void ShellSortA(int R[], int inc[], int length, int m);

void BubbleSort(int R[], int n);
void QuickSort(int R[], int low, int hig);

void SelectSort(int R[], int n);
void HeapAdjust(int R[], int s, int m);
void HeapSort(int R[], int length);

void Merge(int a[], int first, int mid, int last, int temp[]);
void MeSort(int a[], int first, int last, int temp[]);

/*
clock_t start_time=clock();
clock_t end_time=clock();
cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间

*/
int main()
{
	using std::endl;
	using std::cout;
	using std::cin;
	using std::string;
	string const name[8] = {
		"InsertSort",
		"BiInsertSort",
		"ShellSortA",
		"BubbleSort",
		"QuickSort",
		"SelectSort",
		"HeapSort",
		"MergeSort"
	};

	int inc[] = { 5,3,1 };	//	increment for shellsort
	int i;
	int temp[N + 1];	//	temp for mergesort
	/*Test part, to verify the accuracy of algorithm*/

	
	for (i = 0; i < M; ++i) 
		R[i] = test_data[i];
	InsertSort(R, M);
	if (test(R, standard, M)) 
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	BiInsertSort(R, M);
	if (test(R, standard, M))
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	ShellSortA(R, inc, M, 3);
	if (test(R, standard, M))
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	BubbleSort(R, M);
	if (test(R, standard, M))
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	QuickSort(R, 0, M - 1);
	if (test(R, standard, M))
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	SelectSort(R, M );
	if (test(R, standard, M))
		cout << "True" << endl;
	for (i = 0; i < M; ++i)
		R[i] = test_data[i];
	MeSort(R, 0, M-1, temp);
	if (test(R, standard, M))
		cout << "True" << endl;
	
	for (i = 1; i <= M; ++i)
		R[i] = test_data[i-1];
	HeapSort(R, M);
	print(R, M);
	
	cin >> i;
	
	/*Comparison part*/
	init();
	

	for (i = 0; i < N; ++i)
		R[i] = a[i];
	clock_t start_time = clock();
	InsertSort(R, N);
	clock_t end_time = clock();
	time_[0] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	
	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	BiInsertSort(R, N);
	 end_time = clock();
	time_[1] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	ShellSortA(R, inc, N, 3);
	 end_time = clock();
	time_[2] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	BubbleSort(R, N);
	 end_time = clock();
	time_[3] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	QuickSort(R,0, N-1);
	 end_time = clock();
	time_[4] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	SelectSort(R, N);
	 end_time = clock();
	time_[5] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	
	for (i = 0; i < N; ++i)
		R[i] = a[i];
	 start_time = clock();
	MeSort(R, 0, N - 1, temp);
	 end_time = clock();
	time_[6] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	
	for (i = 1; i <= N; ++i)
		R[i] = a[i-1];
	start_time = clock();
	HeapSort(R, N);
	end_time = clock();
	time_[7] = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	print_time();
	while (1);
	return 0;
}

bool test(int before[], int after[], int n)
{
	for (int i = 0; i < n; i++) {
		if (before[i] != after[i])
			return false;
	}
	return true;
}

void print(int a[], int n)
{
	using std::cout;
	for (int i = 1; i <= n; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n";
}

void print_time()
{
	using namespace std;
	string const name[8] = {
		"InsertSort",
		"BiInsertSort",
		"ShellSortA",
		"BubbleSort",
		"QuickSort",
		"SelectSort",
		"MergeSort",
		"HeapSort"
	};
	for (int i = 0; i < 8; ++i) {
		cout << name[i] << ": " << time_[i]/1000 << "s" << endl;
	}
}
void init()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < N; ++i) {
		a[i] = rand() % 300000;
	}
}

void QuickSort(int R[], int low, int hig)
{
	if (low >= hig)  return;
	int i = low, j = hig, kval = R[low];
	while (i < j) {
		while (i < j && kval <= R[j]) //[low](i)被保存，因此j要先跑 
			j--;
		R[i] = R[j];
		while (i < j && kval >= R[i])
			i++;
		R[j] = R[i];
	}
	R[i] = kval;
	QuickSort(R, low, i - 1);
	QuickSort(R, i + 1, hig);
}

void InsertSort(int a[], int n)
{
	int temp;
	int j;
	for (int i = 1; i < n; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0; j--) {
			if (a[j] > temp) {
				a[j + 1] = a[j];
			}
			else
				break;
		}
		a[j + 1] = temp;
	}
}


void BiInsertSort(int R[], int n)
{
	int i, j, x, m;      /*i,j均为循环变量，x用来存储当前待排序的数据，m充当比较区间的中点*/
	int low, high;     /*low代表要与Array[i]进行比较的有序区间的第一个元素所在位置。
					   high代表要与Array[i]进行比较的有序区间的最后一个元素所在位置。*/
	for (i = 1; i < n; i++)
	{
		x = R[i];
		low = 0;      /*第一次划分有序比较区间，比较区间的第一个元素所在位置为0*/
		high = i - 1;   /*第一次划分有序比较区间，比较区间的最后一个元素所在位置为n-1*/
						/*比较查找Array[i]合适插入的位置*/
		while (low <= high)
		{
			m = (low + high) / 2;
			if (x > R[m])
			{
				low = m + 1;
			}
			else
			{
				high = m - 1;
			}
		}
		/*确定好位置后，将位置之后的数据后移，插入待排序数据*/
		for (j = i - 1; j > high; j--)
		{
			R[j + 1] = R[j];
		}
		R[j + 1] = x;
	}
}


void ShellSortB(int R[], int incr, int length)
{//incr为增量,即[1,1+incr,1+2incr...] [2,2+incr,2+2incr...]为子表 
	int i, j;
	int temp;
	for (i = incr; i < length; i++) { // 子表的排序是互相穿插的 
		if (R[i] < R[i - incr]) { //对每个子表而言左侧是有序区，逐渐扩大有序区 
			temp = R[i];
			for (j = i - incr; j >= 0 && temp< R[j]; j -= incr) //由于不一定最终会和0号下标比，不能单纯用哨兵 
				R[j + incr] = R[j];
			R[j + incr] = temp;
		}
	}
}

void ShellSortA(int R[], int inc[], int length, int m)
{
	int i;
	for (i = 0; i < m; i++) {
		ShellSortB(R, inc[i], length);
	}
}

void BubbleSort(int R[], int n)
{
	int temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (R[j] > R[j + 1]) {
				temp = R[j];
				R[j] = R[j + 1];
				R[j + 1] = temp;
			}
		}
	}
}

void SelectSort(int R[], int n)
{
	int temp;
	int k;
	for (int i = 0; i < n - 1; i++) {
		k = i;
		for (int j = k + 1; j < n; j++) {
			if (R[j] < R[k])
				k = j;
		}
		if (i != k) {
			temp = R[i];
			R[i] = R[k];
			R[k] = temp;
		}
	}
}

void HeapSort(int R[], int length)
{
	int i, j, temp;
	for (i = length / 2; i >= 1; i--) {
		HeapAdjust(R, i, length);
	}

	for (j = length; j>1; j--) { //右侧是有序区 
		temp = R[j];	R[j] = R[1];	R[1] = temp;
		HeapAdjust(R, 1, j - 1);
	}
}
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



void Merge(int a[], int first, int mid, int last, int temp[])
{
	int i, j, k = 0;
	for (i = first, j = mid + 1; i <= mid && j <= last;) {
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while (i <= mid)
		temp[k++] = a[i++];
	while (j <= last)
		temp[k++] = a[j++];
	for (i = 0; i <= k - 1; i++)
		a[first + i] = temp[i];
}

void MeSort(int a[], int first, int last, int temp[])
{
	int mid;
	if (first < last) {
		mid = (first + last) / 2;
		MeSort(a, first, mid, temp);
		MeSort(a, mid + 1, last, temp);
		Merge(a, first, mid, last, temp);
	}
}