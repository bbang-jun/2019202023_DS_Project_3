#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	// map<int, int>* (map[from vertex].insert([to vertex], [weight]))
	map < int, int >* m_List; // 그래프 데이터

public:	
	ListGraph(bool type, int size);
	~ListGraph();
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printGraph();
};

#endif