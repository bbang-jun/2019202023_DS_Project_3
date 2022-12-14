#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
// 그래프 연산을 수행하는 일반 함수들을 모아둔 헤더 파일
bool BFS(Graph* graph, int vertex); 
bool DFS(Graph* graph, int vertex);
bool DFS_R(Graph* graph, bool visit[], int path[], int vertex); // DFS 재귀연산
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);
// void InsertionSort(int a[], int low, int high);
void InsertionSort(vector<pair<int, pair<int, int>>>* a, int low, int high);
int partition(vector<pair<int, pair<int, int>>> *a, int low, int high);
int findParent(int x, int parent[]);
void unionParent(int a, int b, int parent[]);
void QuickSort(vector<pair<int, pair<int, int>>>* a, const int low, const int high);
void printPath(int start, int i, int vertex, vector<int>* from);
bool findVertexInGraph(Graph *graph, int vertex);
void find_path(int s, int e, int dist[], int prev[]);
#endif