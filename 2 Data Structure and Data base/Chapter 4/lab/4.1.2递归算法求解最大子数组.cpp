#include <iostream>
using namespace std;

void FindMaxSubarray(float A[], int low, int high, int & left, int & right, float & maxsum);
void FindMaxCrossingSubarray(float A[], int low, int mid, int high, int & left, int & right, float & maxsum);
int const N = 16;

int main()
{
	int left, right;
	float maxsum;
	float A[N] = {13, -3, -25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	FindMaxSubarray(A, 0, N-1, left, right, maxsum);
	cout << "left: " << left << " right: " << right << " maxsum: " << maxsum << endl;
	while (cin.get() != 'q')
		;
	return 0;
}


void FindMaxCrossingSubarray(float A[], int low,int mid, int high, int & left, int & right, float & maxsum)
{
	float leftsum, rightsum, sum;
	int i, j;

	leftsum = -99999;
	sum = 0;
	for (i = mid; i >= low; i--) {
		sum = sum + A[i];
		if (sum > leftsum) {
			leftsum = sum;
			left = i;
		}
	}

	rightsum = -99999;
	sum = 0;
	for (j = mid + 1; j <= high; j++) {
		sum = sum + A[j];
		if (sum > rightsum) {
			rightsum = sum;
			right = j;
		}
	}
	
	maxsum = leftsum + rightsum;
}


void FindMaxSubarray(float A[], int low, int high, int & left, int & right, float & maxsum)
{
	int mid, leftlow, lefthigh, rightlow, righthigh, crosslow, crosshigh;
	float leftsum, rightsum, crosssum;

	if (low == high) {
		left = right = low;
		maxsum = A[low];
	}
	else {
		mid = (low + high) / 2;
		FindMaxSubarray(A, low, mid, leftlow, lefthigh, leftsum);
		FindMaxSubarray(A, mid + 1, high, rightlow, righthigh, rightsum);
		FindMaxCrossingSubarray(A, low, mid, high, crosslow, crosshigh, crosssum);

		if (leftsum >= rightsum && leftsum >= crosssum) {
			left = leftlow;
			right = lefthigh;
			maxsum = leftsum;
		}
		else if (rightsum >= leftsum && rightsum >= crosssum) {
			left = rightlow;
			right = righthigh;
			maxsum = rightsum;
		}
		else {
			left = crosslow;
			right = crosshigh;
			maxsum = crosssum;
		}
	}
}

