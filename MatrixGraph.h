#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	// int** ([from vertext][to vertex] = weight)
	int** m_Mat; // 그래프 데이터
	
	vector<map<int, int>*> v;

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();	
	int temp=-1;
	bool getAdjacentEdges(int vertex, map<int, int>* m); // 인자로 입력된 vertex에 인접한 edge들을 map에 저장하는 함수
	void insertEdge(int from, int to, int weight);
	bool printGraph();
	bool printvGraph();
};

#endif