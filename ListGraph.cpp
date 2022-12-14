#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

bool ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	if(vertex==-1)
		return false;
	map<int, int>* v_map = v[vertex];
	if(v_map==NULL)
		return false;
	map<int, int>::iterator iter;
	for(iter=v_map->begin(); iter!=v_map->end(); iter++){
		m->insert(pair<int, int>(iter->first, iter->second));
	}

	return true;
}

// map<int, int>* (map[from vertex].insert([to vertex], [weight]))
void ListGraph::insertEdge(int from, int to, int weight)
{
	vector<map<int, int>*>::iterator it=v.begin();

	if(to==0 && weight==0){
		it=v.insert(it+from, 0);
	}
	else{
		if(temp!=from){
			m_List[from].insert(pair<int, int>(to, weight));
			it=v.insert(it+from, m_List+from);
			temp=from;
		}
		else
			m_List[from].insert(pair<int, int>(to, weight));
	}

	return;
}

bool ListGraph::printGraph()
{
	fout.open("log.txt", ios::app);
	fout<<"========PRINT========"<<endl;

	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && fout<<" -> "; it_++)
		{
			fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		fout<<endl;
	}
	//fout<<endl;
	fout<<"====================="<<endl<<endl;
	return 1;
}