#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

bool MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	int i=0;
	int judgeNum=0;

	while(i<getSize()){
		if(m_Mat[vertex][i]!=0){
			m->insert(pair<int, int>(i, m_Mat[vertex][i]));
			judgeNum++;
		}
			
		
		i++;
	}
	if(judgeNum==0)
		return false;

	return true;
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to]=weight;
}

bool MatrixGraph::printGraph()
{
	fout.open("log.txt", ios::app);
	if( m_Size < 0 )
		return 0;

	fout<<"========PRINT========"<<endl;

	fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]"<<'\t';
	}
	fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && fout<<'\t'; j++)
		{
			fout<<m_Mat[i][j];
		}
		fout<<endl;
	}
	fout<<"====================="<<endl<<endl;
	return 1;
}

// bool MatrixGraph::printvGraph(){
// 	fout.open("log.txt", ios::app);
// 	fout<<"Graph is ListGraph!"<<endl;

// 	for(int i=0; i<m_Size; i++)
// 	{
// 		fout<<"["<<i<<"]";

// 		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && fout<<" -> "; it_++)
// 		{
// 			fout<<"("<<it_->first<<","<<it_->second<<")";
// 		}
// 		fout<<endl;
// 	}
// 	fout<<endl;
// 	return 1;
// }