#include <iostream>

int main()
{
	using namespace std;
	int a = 400 * 500 * 600 * 300;
	int test = 50000 * 50000;
	printf("400 * 500 * 600 * 300 = %d\n", 400 * 500 * 600 * 300);  //  1640261632
	printf("50000 * 50000 = %d\n", 50000 * 50000);  //  -1794967296
	printf("1e20 - 1e20 + 3.14 = %f\n", 1e20 - 1e20 + 3.14);  // 3.140000
	printf("1e20 - 1e20 + 3.14 = %f\n", 1e20+(- 1e20 + 3.14));  //   0.000000
	while (cin.get() != 'q')
		;
	return 0;
}
