#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) // constructor
{
	m_Mat = new int*[size]; // make dimension-2
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size); // iniitialize
	}
}

MatrixGraph::~MatrixGraph() // destructor
{
	for(int i=0; i<getSize(); i++) // deallocation
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

bool MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) // get adjacent edges for certain vertex
{
	int i=0;
	int judgeNum=0;

	while(i<getSize()){ // insert adjacent edges information to map
		if(m_Mat[vertex][i]!=0){
			m->insert(pair<int, int>(i, m_Mat[vertex][i])); // insert
			judgeNum++;
		}
			
		i++;
	}
	if(judgeNum==0)
		return false;

	return true;
}

void MatrixGraph::insertEdge(int from, int to, int weight) // insert edge
{
	m_Mat[from][to]=weight; // save weight
}

bool MatrixGraph::printGraph() // print graph
{
	fout.open("log.txt", ios::app); // print to log.txt
	if( m_Size < 0 ) // if graph size is minus
		return 0;

	fout<<"========PRINT========"<<endl;

	fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]"<<'\t'; // print 
	}
	fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		fout<<"["<<i<<"]"; // print
		for(int j=0; j<m_Size && fout<<'\t'; j++)
		{
			fout<<m_Mat[i][j]; // print
		}
		fout<<endl;
	}
	fout<<"====================="<<endl<<endl;
	return 1;
}