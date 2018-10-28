#include "stdio.h"
#include "stdlib.h"
#include "math.h" 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  //不可实现 
#define OVERLOW -2
#define max_n 10009
#define INIT_SIZE 800
#define EXPAND_SIZE 10900
#define INF 88888888

int s, t, m, n;
int visited[max_n] = { 0 };
int safe[max_n] = { 0 };     //safe 和 visited都用0号下标
int D[max_n] = { 0 };
int S1[max_n] = { 0 };

typedef struct ArcNode { //边结点 
	int adjvex; //邻接点的坐标
	int weight;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode { //顶点结点 
	int data;
	ArcNode *firstarc; //边链头指针 
}VNode, AdjList[max_n];

typedef struct {
	AdjList vertices; //邻接表
	int vexnum, arcnum; //顶点数目和边数
	unsigned kind;
}ALGraph;


void CreateGraph(ALGraph &G1, ALGraph &G2) {
	int i, j, k, x, y, l, flag;
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	ArcNode *m;
	for (k = 1; k <= G1.arcnum; k++) {
		scanf("%d %d %d", &x, &y, &l);
		flag = 1;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		q = (ArcNode*)malloc(sizeof(ArcNode));
		if (x == y)
			continue;
		for (m = G1.vertices[x].firstarc; m != NULL; m = m->nextarc) {
			if (m->adjvex == y)
				if (l<m->weight) {
					m->weight = l;
					flag = 0;
				}
		}
		if (flag) {
			p->adjvex = y; //出边表 
			p->weight = l;
			p->nextarc = G1.vertices[x].firstarc;
			G1.vertices[x].firstarc = p;     //出边 
		}
		if (flag) {
			q->adjvex = x; //入边表便于遍历寻找安全点 
			q->weight = l;
			q->nextarc = G2.vertices[y].firstarc;
			G2.vertices[y].firstarc = q;   //入边 
		}
		else {
			for (m = G2.vertices[y].firstarc; m != NULL; m = m->nextarc)
				if (m->adjvex == x)
					m->weight = l;
		}
	}
}

void DFS(ALGraph &G, int v) {
	ArcNode *p;
	safe[v] = 1; //能被机房遍历到且不和陷阱相连的是安全的 
	visited[v] = TRUE;
	for (p = G.vertices[v].firstarc; p != NULL; p = p->nextarc)
		if (!visited[p->adjvex])
			DFS(G, p->adjvex);
}

void Dijkstra(ALGraph &G, int v0)
{ //v0是下标 
	int i, j, k, min;
	ArcNode *p;
	for (i = 1; i <= G.vexnum; i++) {
		D[i] = INF;
		if (safe[i] != 1) {
			S1[i] = 1;
			n--;
		}
	}
	for (p = G.vertices[v0].firstarc; p != NULL; p = p->nextarc) {
		if (!S1[p->adjvex]) D[p->adjvex] = p->weight; //下标=次序-1 
	}
	S1[v0] = 1;
	D[v0] = 0;
	for (i = 1; i<G.vexnum; i++) {
		min = INF;
		for (j = 1; j <= G.vexnum; j++)
			if (!S1[j] && D[j]<min) {
				min = D[j];
				k = j;
			}//寻找新红点 
		S1[k] = 1;
		for (p = G.vertices[k].firstarc; p != NULL; p = p->nextarc)
			if (!S1[p->adjvex] && (D[k] + p->weight) < D[p->adjvex])
				D[p->adjvex] = (D[k] + p->weight);
	}
}

int main()
{
	int i, j;
	ArcNode *p;
	scanf("%d %d", &n, &m); //n个顶点，m条边 
	ALGraph G1, G2;
	G1.vexnum = G2.vexnum = n;
	G1.arcnum = G2.arcnum = m;
	for (i = 1; i <= G1.vexnum; i++) {
		(G1.vertices[i]).data = i;
		(G1.vertices[i]).firstarc = NULL;
		(G2.vertices[i]).data = i;
		(G2.vertices[i]).firstarc = NULL;
	}
	CreateGraph(G1, G2);
	scanf("%d %d", &s, &t);
	DFS(G2, t);
	//	for(i=1;i<=G1.vexnum;i++)
	//		printf("#%d\n",safe[i]);
	for (i = 1; i <= G1.vexnum; i++) {
		if (safe[i] == 0)
			for (p = G2.vertices[i].firstarc; p != NULL; p = p->nextarc) {
				safe[p->adjvex] = 3;   //不安全点和陷阱点的标志不能一样！！否则在后续判断会扩大范围！！！ 
			}
	}
	if (safe[s] != 1 || safe[t] != 1) {
		printf("-1");
		return 0;
	}
	if (s == t) {
		printf("0");
		return 0;
	}
	safe[s] = safe[t] = 1;
	//	for(i=1;i<=G1.vexnum;i++)
	//		printf("#%d\n",safe[i]);
	Dijkstra(G1, s);
	if (D[t] == INF) {
		printf("-1");
		return 0;
	}
	else {
		printf("%d", D[t]);
		return 0;
	}
}
