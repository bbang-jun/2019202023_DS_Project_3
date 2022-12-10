#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex)
{ofstream fout;
    fout.open("log.txt", ios::app);
    if(vertex>graph->getSize()) // 그래프에 있는 노드보다 큰 노드가 들어오면 없으므로 예외처리
		return true;

	bool visited[graph->getSize()]; // 방문했는지 체크하는 bool형 배열
	for(int i=0; i<graph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i]=false;
	visited[vertex]=true;

	queue<int> q;
	q.push(vertex);
	
	if(graph->getSize()==1){ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout<<vertex<<endl;
		return true;
	} 
	else // 처음 노드 출력
		fout<<vertex;

	while(!q.empty()){
		vertex=q.front();
		q.pop();

		map<int, int>*m = new map<int, int>; // map 동적 할당
		graph->getAdjacentEdges(vertex, m); // 해당 vertex에 인접한 vertex들을 map에 담음

		map<int, int>::iterator iter; 

		for(iter=m->begin(); iter!=m->end(); iter++){
			int next=iter->first;

			if(!visited[next]){
				visited[next]=true;

				int k=0; // 마지막 방문이면 "->"가 출력되지 않아야 하므로 이를 판단하기 위한 변수
				for(int j=0; j<graph->getSize(); j++){ // 해당 그래프에서 방문한 횟수 판단
					if(visited[j]==true)
						k++;
				}

				if(k==graph->getSize()){ // 해당 그래프에서 모든 vertex를 방문했으면
					fout<<" -> "<<next<<endl; 
					return true;
				} 
					

				q.push(next);
				fout<<" -> "<<next;
			}
		}
		
	}

	fout<<endl;
}

bool DFS(Graph* graph, int vertex)
{ofstream fout;
    fout.open("log.txt", ios::app);
    if(vertex>graph->getSize()) // 그래프에 있는 노드보다 큰 노드가 들어오면 없으므로 예외처리
		return true;
	
	bool visited[graph->getSize()]; // 방문했는지 체크하는 bool형 배열
	for(int i=0; i<graph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i]=false;
	visited[vertex]=true; // 방문했으므로 true

	stack<int> s;
	s.push(vertex); // stack에 push(시작 vertex)
	
	if(graph->getSize()==1){ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout<<vertex<<endl;
		return true;
	} 
	else // 처음 노드 출력
		fout<<vertex;

	while(!s.empty()){ // stack이 empty일 때까지 반복
		int current = s.top(); // 현재 vertex는 stack의 top
		s.pop(); // pop

		map<int, int>*m = new map<int, int>; // map 동적 할당
		graph->getAdjacentEdges(current, m); // 해당 vertex에 인접한 vertex들을 map에 담음

		map<int, int>::iterator iter; 
		for(iter=m->begin(); iter!=m->end(); iter++){ // 해당 vertex에 인접한 모든 vertex(map) - map은 오름차순 자동 정렬
			int next=iter->first; // 다음 vetex(현재 vertex와 인접한 vertex)

			if(!visited[next]){ // false인 경우, 즉 다음 vertex가 방문하지 않았다면
				visited[next]=true; // 방문할 것이므로 true

				int k=0; // 마지막 방문이면 "->"가 출력되지 않아야 하므로 이를 판단하기 위한 변수
				for(int j=0; j<graph->getSize(); j++){ // 해당 그래프에서 방문한 횟수 판단
					if(visited[j]==true)
						k++;
				}

				if(k==graph->getSize()){// 해당 그래프에서 모든 vertex를 방문했으면
					fout<<" -> "<<next<<endl; 
					return true;
				}
					
				s.push(current); // current를 다시 push하는 이유는 인접한 vertex가 next뿐만 아니라 여러개 있을 수도 있기 때문
				s.push(next); // 다음 반복시 top이 next가 됨(next의 next를 위해)
				fout<<" -> "<<next;
				break;
			}
		}
	}

	fout<<endl;
}

bool DFS_R(Graph* graph, bool visit[], int vertex)
{   ofstream fout;
    fout.open("log.txt", ios::app);

	if(vertex>graph->getSize()) // 그래프에 있는 노드보다 큰 노드가 들어오면 없으므로 예외처리
		return true;
	
	visit[vertex]=true; // 방문했으므로 true

	if(graph->getSize()==1){ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout<<vertex<<endl;
		return true;
	} 
	else{
		fout<<vertex;
	}
    

    map<int, int>*m = new map<int, int>; // map 동적 할당
	graph->getAdjacentEdges(vertex, m); // 해당 vertex에 인접한 vertex들을 map에 담음

	map<int, int>* temp=m;
	for(map<int, int>::iterator iter=temp->begin(); iter!=temp->end(); iter++){
		int next=iter->first; // 다음 vetex(현재 vertex와 인접한 vertex)

		if(!visit[next]){
			fout<<" -> ";
            fout.close();
			DFS_R(graph, visit, next);
		}
	}
}

bool Kruskal(Graph* graph)
{

}

bool Dijkstra(Graph* graph, int vertex)
{

}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{

}

bool FLOYD(Graph* graph)
{

}