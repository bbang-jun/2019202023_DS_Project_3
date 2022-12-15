#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size) // constructor
{
	m_Type = type; // set type
	m_List = new map<int, int>[size]; // set size
}

ListGraph::~ListGraph() // destructor
{
	delete[] m_List; // delete
}

bool ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) // get adjacent edges
{
	if(vertex==-1) // exception handlidng
		return false; // return false
	map<int, int>* v_map = v[vertex]; // declare v_map
	if(v_map==NULL) // if v_map is null
		return false; // return false
	map<int, int>::iterator iter; // set iterator
	for(iter=v_map->begin(); iter!=v_map->end(); iter++){ // loop iterator
		m->insert(pair<int, int>(iter->first, iter->second)); // insert edge
	}

	return true; // return true
}

// map<int, int>* (map[from vertex].insert([to vertex], [weight]))
void ListGraph::insertEdge(int from, int to, int weight) // insert edge
{
	vector<map<int, int>*>::iterator it=v.begin(); // set iterator

	if(to==0 && weight==0){ // to vertex is 0, weight is 0
		it=v.insert(it+from, 0); // insert
	}
	else{
		if(temp!=from){ // judge it is continuous 
			m_List[from].insert(pair<int, int>(to, weight)); // insert to m_list
			it=v.insert(it+from, m_List+from); // inser to vector
			temp=from; 
		}
		else
			m_List[from].insert(pair<int, int>(to, weight)); // insert
	}

	return;
}

bool ListGraph::printGraph() // print graph information
{
	fout.open("log.txt", ios::app); // print for log.txt
	fout<<"========PRINT========"<<endl;

	for(int i=0; i<m_Size; i++) // loop
	{
		fout<<"["<<i<<"]"; // print

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && fout<<" -> "; it_++)
		{
			fout<<"("<<it_->first<<","<<it_->second<<")"; // print
		}
		fout<<endl;
	}

	fout<<"====================="<<endl<<endl;
	return 1;
}