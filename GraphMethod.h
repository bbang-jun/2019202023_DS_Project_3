#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
bool BFS(Graph* graph, int vertex); // BFS 
bool DFS(Graph* graph, int vertex); // dfs
bool DFS_R(Graph* graph, bool visit[], int path[], int vertex); // recursive dfs
bool Kruskal(Graph* graph); // kruskal algorithm 
bool Dijkstra(Graph* graph, int vertex); // dikstra algorithm
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex); // bellmanford algorithm
bool FLOYD(Graph* graph); // floyd algorithm
void InsertionSort(vector<pair<int, pair<int, int>>>* arr, int low, int high); // insertion sort
int partition(vector<pair<int, pair<int, int>>> *arr, int low, int high); // partition
int findOperation(int x, int parent[]); // disjoint set(find)
void unionOperation(int a, int b, int parent[]); // disjoint set (union)
void QuickSort(vector<pair<int, pair<int, int>>>* arr, const int low, const int high); // quick sort
void printPath(int start, int i, int vertex, vector<int>* from); // path previous path
bool findVertexInGraph(Graph *graph, int vertex); // find vertex in graph
#endif