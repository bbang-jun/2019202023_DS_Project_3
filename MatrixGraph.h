#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{ // inheritance
private:
	// int** ([from vertext][to vertex] = weight)
	int** m_Mat; // data of graph
	
	vector<map<int, int>*> v; // declare vector

public:
	MatrixGraph(bool type, int size); // constructor
	~MatrixGraph();	 // destructor
	int temp=-1; // initialize
	bool getAdjacentEdges(int vertex, map<int, int>* m); // save adjacent edges information to map
	void insertEdge(int from, int to, int weight); // insert edge
	bool printGraph(); // print graph
};

#endif