#include "iostream"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int const N = 256;	//	number of chars
typedef struct {
	long weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

// Select the node with lowest weight from index 1->n
void Select(HuffmanTree HT, int n, int &index1, int &index2)
{
	long long s1, s2;
	s1 = s2 = 400000000;
	for (int i = 1; i <= n; ++i) {
		if (HT[i].parent == 0) {	//	To ignore the nodes that have been merged
			if (HT[i].weight < s1 || HT[i].weight < s2) {
				if (s1 > s2) {
					s1 = HT[i].weight;
					index1 = i;
				}
				else {
					s2 = HT[i].weight;
					index2 = i;
				}
			}
		}
	}
}

void Create_Huffman(HuffmanTree &HT, long *weight)
{
	int s1, s2;
	int m = 2 * N - 1;	// number of nodes
//	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HT = new HTNode[m + 1];	// 0 is not utilized
	for (int i = 1; i <= m; i++) {
		HT[i].weight = i <= N ? weight[i-1] : 0;
		HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
	}
	for (int i = N + 1; i <= m; i++) {
		Select(HT, i-1, s1, s2);
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = HT[s2].parent = i;
	}
}

// Coding by find the road to the leaves
/*
void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC)
{
	char *cd;
	HC = new char *[N + 1];
	cd = new char[N];
	int c, f;
	for (int i = 1; i <= N; ++i) {
		int start = 255;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';

			HC[i] = new char[256 - start];//0号不用 
			strcpy(HC[i], &cd[start]);
	}
	delete cd;
}*/

/* From leaf to root throgh the parent attribute*/
void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC)
{
	char *cd;
	int i;
	HC = (HuffmanCode)malloc((N+1) * sizeof(char*));
	cd = (char*)malloc(N * sizeof(char));
	cd[N-1] = '\0';
	int c, f;
	for (i = 1; i <= N; ++i)	//	coding for N leaf
	{
		int start = N-1;	
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//	start from leaf
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';

			HC[i] = (char*)malloc((N - start) * sizeof(char));//0号不用 
			strcpy(HC[i], &cd[start]);
	}
	free(cd);
}

void Get_Frequency(FILE * fp, long * weight)
{
	long s = 0;
	unsigned char bit[1];
	fseek(fp, 0L, 2);
	long L = ftell(fp);	//	to obtain the length of the file

	fseek(fp, 0L, 0);
	
	while (s <= L)
	{
		s++;
		fread(bit, 1, 1, fp);	//	 read a char from the file
		weight[bit[0]]++;	//	weight is a counter
	}
	
	/*
	while (s <= L)
	{
		s++;
		fread(bit, 1, 1, fp);	//	 read a char from the file
		weight[bit[0]-65]++;	//	weight is a counter
	}
	*/
}

void GetWeight(FILE*fp, long*weight)
{
	for (int i = 0; i < N; i++)
		fscanf(fp, "%ld\r\n", &weight[i]);
}

void Compress(FILE*fp, HuffmanCode HC, long*w, char*s, char*tail)
{
	FILE*f;
	f = fopen(s, "wb");
	fseek(fp, 0L, 0);
	fprintf(f, "%s\r\n", tail);
	for (int i = 0; i < 256; i++)
	{
		fprintf(f, "%ld\r\n", w[i]);
	}
	//	Compression the file
	unsigned char temp[1];
	unsigned char bit[1];
	temp[0] = 0;
	bit[0] = 0;
	int num = 0;
	fread(temp, 1, 1, fp); //read a char 
	do
	{
		int i = 0;
		int l = strlen(HC[temp[0] + 1]);	// Get the length of the code of this char
		for (i = 0; i < l; i++)
		{
			if (HC[temp[0] + 1][i] == '0')
			{	//	右边补0, 左边溢出舍弃 (00001111 << 2 = 00111100)
				bit[0] <<= 1;	//	bit[0] = bit[0] << 1;
			}
			else
			{
				bit[0] <<= 1;
				bit[0] += 1;
			}
			num++;
			if (num == 8)
			{
				fwrite(bit, 1, 1, f);
				bit[0] = 0;
				num = 0;
			}
		}
		fread(temp, 1, 1, fp);
	} while (!feof(fp));
	if (num != 0)
	{
		bit[0] <<= (8 - num);
		fwrite(bit, 1, 1, f);
	}
	fclose(f);
}

void UnCompress(HuffmanTree&HT, HuffmanCode&HC, FILE*fp, char*s)
{
	long w[256] = { 0 };
	char name[100];
	fseek(fp, 0L, 0);
	fscanf(fp, "%s\r\n", name);
	strcat(s, name);
	FILE*f;
	f = fopen(s, "wb");
	GetWeight(fp, w);//读取信息
	Create_Huffman(HT, w);
	HuffmanCoding(HT, HC);	
	int site = N * 2 - 1;
	unsigned char bit[1];
	unsigned char temp[1];
	fread(bit, 1, 1, fp);

	do
	{
		int num = 0;
		while (num < 8)
		{
			if (bit[0] & 128)//第一位是1
			{
				site = HT[site].rchild;
			}
			else
			{
				site = HT[site].lchild;
			}
			num++;
			bit[0] <<= 1;
			if (site <= 256)//某个时刻到了叶子节点 
			{
				temp[0] = site - 1;	// get the char represented by site(ASCII code)
				fwrite(temp, 1, 1, f);
				site = 2 * 256 - 1;
			}
		}
		fread(bit, 1, 1, fp);
	} while (!feof(fp));
	fclose(f);
}

void seperate(char*s, char* tail, char* name)
{
	int L = strlen(s);
	for (; L >= 0; L--)
	{
		if (s[L] == '.')
			break;
	}
	strcpy(tail, s + L);
	int i = 0;
	for (i = 0; i < L; i++)
		name[i] = s[i];
	name[i] = '\0';
}


int main()
{
	using namespace std;
	int t, i;
	char p1[100], p2[100], name[100], tail[100];
	long w[256] = { 0 };
	HuffmanTree HT;
	HuffmanCode HC;
	FILE *fp;
	cin >> t;
	if (t == 1) {
		getchar();
		cin >> p1;
		cin >> p2;
		fp = fopen(p1, "rb");
		seperate(p1, tail, name);
		Get_Frequency(fp, w);
		Create_Huffman(HT, w);
		HuffmanCoding(HT, HC);
		Compress(fp, HC, w, p2, tail);
	}
	else if (t == 2) {
		cin >> p1;
		cin >> p2;
		fp = fopen(p1, "rb");
		seperate(p1, tail, name);
		UnCompress(HT, HC, fp, p2);
	}
	/*
	using std::cin;
	using std::cout;
	using std::endl;
	int menu, i;
	long weight[N] = {0};

	char p1[100], p2[100], name[100], tail[100];
	HuffmanTree HT;
	HuffmanCode HC;

	FILE *fp;

	fp = fopen("data.txt", "rb");
	//Get_Frequency(fp, weight);
	Create_Huffman(HT, weight);
	HuffmanCoding(HT, HC);
	*/
	while (1);

		return 0;


}

/*
long weight[N] = { 4,3,7,5,1,6 };

cout << "weight" << '\t' << "parent" << '\t' << "lchild" << '\t' << "rchild" << endl;
for (i = 1; i <= 2 * N - 1; ++i) {
	cout << HT[i].weight << '\t' << HT[i].parent << '\t' << HT[i].lchild << '\t' << HT[i].rchild << endl;
}
cout << endl;
cout << "Codebook:" << endl;
for (int i = 1; i <= N; i++) {
	cout << HC[i] << endl;
}
*/