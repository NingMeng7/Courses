#include "stdio.h"
#include "stdlib.h"
#include "math.h" 
#include <queue>
#include <iostream>

int const INF = 88888888;
int const max_n = 10000;

int s, t, m, n;
int visited[max_n] = { 0 };

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

void visit(int v)
{
	using std::cout;
	cout << v << "\t";
}

/*
Input: (x, y, weight) to create a edge: x->y with weight
*/
void CreateGraph(ALGraph &G) 
{
	int k, x, y, weight, flag;
	ArcNode *p = NULL;
	ArcNode *m;
	for (k = 1; k <= G.arcnum; k++) {
		scanf("%d %d %d", &x, &y, &weight);
		flag = 1;
		p = new ArcNode;
		if (x == y)
			continue;
		for (m = G.vertices[x].firstarc; m != NULL; m = m->nextarc) {
			if (m->adjvex == y)
				if (weight < m->weight) {	//	Select the edge with less weight
					m->weight = weight;
					flag = 0;
				}
		}
		if (flag) {
			p->adjvex = y; 
			p->weight = weight;
			p->nextarc = G.vertices[x].firstarc;
			G.vertices[x].firstarc = p;      
		}
		
	}
}

void DFS(ALGraph &G, int v) {
	ArcNode *p;
	visit(v);
	visited[v] = true;
	for (p = G.vertices[v].firstarc; p != NULL; p = p->nextarc)
		if (!visited[p->adjvex])
			DFS(G, p->adjvex);
}

void BFS(ALGraph &G)
{
	using namespace std;
	int v = 1, u;
	int visited[max_n] = { 0 };
	ArcNode * w;
	for (v = 0; v < G.vexnum; v++)visited[v] = 0;
	queue<int> Q;
	for (v = 1; v <= G.vexnum; v++) {
		if (!visited[v]) {
			cout << v;
			visited[v] = 1;
			Q.push(v);
			while (!Q.empty()) {
				u = Q.front();
				Q.pop();
				for (w = G.vertices[u].firstarc; w != NULL; w = w->nextarc)
					if (!visited[w->adjvex]) {
						visit(w->adjvex);
						visited[w->adjvex] = 1;
						Q.push(w->adjvex);
					}

			}
		}
	}
}

void Dijkstra(ALGraph &G, int v0)
{ //v0是下标 
	int i, j, k, min;
	ArcNode *p;
	for (i = 1; i <= G.vexnum; i++) {
		D[i] = INF;
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
	using std::cout; using std::endl; using std::cin;
	int i;
	ArcNode *p; 
	ALGraph G;

	cin >> G.vexnum ;
	cin >> G.arcnum;
	for (i = 1; i <= G.vexnum; i++) {
		(G.vertices[i]).data = i;
		(G.vertices[i]).firstarc = NULL;
	}
	CreateGraph(G);
	cin >> s;
	cin >> t;DFS(G, s);
	cout << endl; 
	BFS(G);
	cout << endl;

	Dijkstra(G, s);

	
	for (i = 1; i <= G.vexnum; i++) {
		if (D[i] == INF) {
			cout << "-1 \t";
		}
		else {
			cout << D[i] << "\t";
		}
	}

	while (1);
	return 0;
}