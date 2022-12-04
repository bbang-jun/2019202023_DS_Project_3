#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	// int** ([from vertext][to vertex] = weight)
	int** m_Mat; // 그래프 데이터

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();	
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printGraph();
};

#endif