#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	// map<int, int>* (map[from vertex].insert([to vertex], [weight]))
	map < int, int >* m_List; // 그래프 데이터
	vector<map<int, int>*> v;
	
public:	
	ListGraph(bool type, int size);
	~ListGraph();
	int temp=-1;
	bool getAdjacentEdges(int vertex, map<int, int>* m); // 인자로 입력된 vertex에 인접한 edge들을 map에 저장하는 함수
	void insertEdge(int from, int to, int weight); // map을 만드는 함수?
	bool printGraph();
};

#endif