#不要随便申请矩阵(n^2)级别的大容量内存#
IDE提示: 0xC00000FD: Stack overflow (参数: 0x00000000, 0x00D02000)。
2048*2048*4 bytes 大概有十几个G，在windows上跑的程序默认分配的栈空间在MB级别，因此爆栈了.


#include <iostream>
#include <ctime>

int const N = 2048;
void copyij(int src[N][N], int dst[N][N])
{
	int i, j;

	clock_t start = clock();
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			dst[i][j] = src[i][j];
	clock_t end = clock();
	std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC;
}

int main()
{
	int src[N][N] = { 0 };
	int dst[N][N];
	copyij(src, dst);
	copyji(src, dst);
	while (std::cin.get() != 'q')
		;
	return 0;
}
