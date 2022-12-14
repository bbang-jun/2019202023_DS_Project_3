#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <list> 

using namespace std;

#define MAX 999999

class Graph{
protected: // for inheritance
	bool m_Type;// 0:List 1:Matrix
	int m_Size; // size of graph
	ofstream fout; // for log.out

public:
	Graph(bool type, int size); // constructor
	~Graph(); // destructor

	bool getType();
	int getSize();
	
	virtual bool getAdjacentEdges(int vertex, map<int, int>* m) = 0; // get adjacentedges map
	virtual void insertEdge(int from, int to, int weight) = 0; // insert edge
	virtual	bool printGraph() = 0; // print graph
};

#endif
