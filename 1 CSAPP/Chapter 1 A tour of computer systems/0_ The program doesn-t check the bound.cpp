#include <iostream>
typedef struct {
	int a[2];
	double d;
} struct_t;

double fun(int i) {
	volatile struct_t s;
	s.d = 3.14;
	s.a[i] = 1073741824;  //  Possibly out of bounds
	return s.d;
}
int main()
{
	for (int i = 0; i < 6; i++) {
		printf("%lf\n", fun(i));
	}
	while (std::cin.get() != 'q')
		;
	return 0;
}

/*
retults:
3.140000
3.140000
3.140000
2.000001
3.140000
3.140000
*/
