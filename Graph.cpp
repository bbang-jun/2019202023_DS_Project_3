#include "Graph.h"

Graph::Graph(bool type, int size) // constructor
{
	m_Type = type;
	m_Size = size;
}

Graph::~Graph() // destructor
{
}

bool Graph::getType(){return m_Type;} // return type
int Graph::getSize(){return m_Size;} // return size
