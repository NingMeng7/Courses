#include <iostream>
using namespace std;

void FindMaxSubarray(float A[], int low, int high, int & left, int & right, float & maxsum);

int const N = 16;

int main()
{
	int left, right;
	float maxsum;
	float A[N] = {13, -3, -25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	FindMaxSubarray(A, 0, N, left, right, maxsum);
	cout << "left: " << left << " right: " << right << " maxsum: " << maxsum << endl;
	while (cin.get() != 'q')
		;

	return 0;
}

void FindMaxSubarray(float A[], int low, int high, int & left, int & right, float & maxsum)
{
	maxsum = -99999;
	float currentsum = 0;
	int i, j;
	for (i = 0; i < high; i++) {
		currentsum = 0;
		for (j = i; j < high; j++) {
			currentsum += A[j];
			if (currentsum > maxsum) {
				maxsum = currentsum;
				left = i;
				right = j;
			}
		}
	}
}
