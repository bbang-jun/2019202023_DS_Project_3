#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
// 그래프 연산을 수행하는 일반 함수들을 모아둔 헤더 파일
bool BFS(Graph* graph, int vertex); 
bool DFS(Graph* graph, int vertex);
bool DFS_R(Graph* graph, bool visit[], int vertex); // DFS 재귀연산
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);

#endif
