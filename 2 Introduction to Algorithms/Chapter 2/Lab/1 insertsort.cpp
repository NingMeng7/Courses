# include <iostream>

const int N = 9;

void InsertSort(int array[], int n);


int main()
{
	using std::cout;
	int A[N] = { 0, 2, 5, 3, 11, 5, 222, 77, 4 };
	
	cout << "Before insertion sort: \n";
	for (int i = 1; i < N; i++) {
		cout << A[i] << " ";
	}
	
	InsertSort(A, N);

	cout << "\nAfter insertion sort: \n";
	for (int i = 1; i < N; i++) {
		cout << A[i] << " ";
	}

	return 0;
}


void InsertSort(int array[], int n)
{
	int i;
	for (int j = 2; j < n; j++) {
		array[0] = array[j];
		i = j - 1;
		while (i > 0 && array[i] > array[0]) {
			array[i + 1] = array[i];
			i = i - 1;
		}
		array[i + 1] = array[0];
	}
}
