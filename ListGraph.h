#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{ // header file for ListGraph
private:
	// map<int, int>* (map[from vertex].insert([to vertex], [weight]))
	map < int, int >* m_List; // data of graph
	vector<map<int, int>*> v; // vector
	
public:	
	ListGraph(bool type, int size); // contructor
	~ListGraph(); // decturctor
	int temp=-1; // judge for continuous
	bool getAdjacentEdges(int vertex, map<int, int>* m); // get adjacent edges number and weight to map
	void insertEdge(int from, int to, int weight); // make m_list
	bool printGraph(); // print graph
};

#endif