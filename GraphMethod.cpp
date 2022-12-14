#include "GraphMethod.h"
# define INF 0x3f3f3f3f
bool firstPrint=true;
int order=0;


bool BFS(Graph *graph, int vertex)
{
	if(findVertexInGraph(graph, vertex)==false)
		return false;

	ofstream fout;
	fout.open("log.txt", ios::app);
			
	bool visited[graph->getSize()];			   // 방문했는지 체크하는 bool형 배열
	for (int i = 0; i < graph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i] = false;
	visited[vertex] = true;

	queue<int> q;
	q.push(vertex);

	fout<<"======== BFS ========"<<endl;
	fout<<"startvertex: "<<vertex<<endl;

	if (graph->getSize() == 1)
	{ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout << vertex << endl;
		return true;
	}
	else // 처음 노드 출력
		fout << vertex;

	while (!q.empty())
	{
		vertex = q.front();
		q.pop();

		map<int, int> *m = new map<int, int>; // map 동적 할당
		graph->getAdjacentEdges(vertex, m);	  // 해당 vertex에 인접한 vertex들을 map에 담음

		map<int, int>::iterator iter;

		for (iter = m->begin(); iter != m->end(); iter++)
		{
			int next = iter->first;

			if (!visited[next])
			{
				visited[next] = true;

				int k = 0; // 마지막 방문이면 "->"가 출력되지 않아야 하므로 이를 판단하기 위한 변수
				for (int j = 0; j < graph->getSize(); j++)
				{ // 해당 그래프에서 방문한 횟수 판단
					if (visited[j] == true)
						k++;
				}

				if (k == graph->getSize())
				{ // 해당 그래프에서 모든 vertex를 방문했으면
					fout << " -> " << next << endl;
					fout<<"====================="<<endl<<endl;
					return true;
				}

				q.push(next);
				fout << " -> " << next;
			}
		}
		delete m;
	}
	fout<<endl;
	fout<<"====================="<<endl<<endl;

	return true;
}

bool DFS(Graph *graph, int vertex)
{
	if(findVertexInGraph(graph, vertex)==false)
		return false;
		
	ofstream fout;
	fout.open("log.txt", ios::app);

	bool visited[graph->getSize()];			   // 방문했는지 체크하는 bool형 배열
	for (int i = 0; i < graph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i] = false;
	visited[vertex] = true; // 방문했으므로 true

	stack<int> s;
	s.push(vertex); // stack에 push(시작 vertex)

	fout<<"======== DFS ========"<<endl;
	fout<<"startvertex: "<<vertex<<endl;

	if (graph->getSize() == 1)
	{ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout << vertex << endl;
		return true;
	}
	else // 처음 노드 출력
		fout << vertex;

	while (!s.empty())
	{						   // stack이 empty일 때까지 반복
		int current = s.top(); // 현재 vertex는 stack의 top
		s.pop();			   // pop

		map<int, int> *m = new map<int, int>; // map 동적 할당
		graph->getAdjacentEdges(current, m);  // 해당 vertex에 인접한 vertex들을 map에 담음

		map<int, int>::iterator iter;
		for (iter = m->begin(); iter != m->end(); iter++)
		{							// 해당 vertex에 인접한 모든 vertex(map) - map은 오름차순 자동 정렬
			int next = iter->first; // 다음 vetex(현재 vertex와 인접한 vertex)

			if (!visited[next])
			{						  // false인 경우, 즉 다음 vertex가 방문하지 않았다면
				visited[next] = true; // 방문할 것이므로 true

				int k = 0; // 마지막 방문이면 "->"가 출력되지 않아야 하므로 이를 판단하기 위한 변수
				for (int j = 0; j < graph->getSize(); j++)
				{ // 해당 그래프에서 방문한 횟수 판단
					if (visited[j] == true)
						k++;
				}

				if (k == graph->getSize())
				{ // 해당 그래프에서 모든 vertex를 방문했으면
					fout << " -> " << next << endl;
					fout<<"====================="<<endl<<endl;
					return true;
				}

				s.push(current); // current를 다시 push하는 이유는 인접한 vertex가 next뿐만 아니라 여러개 있을 수도 있기 때문
				s.push(next);	 // 다음 반복시 top이 next가 됨(next의 next를 위해)
				fout << " -> " << next;
				break;
			}
		}
		delete m;
	}
	fout<<endl;
	fout<<"====================="<<endl<<endl;

	return true;
}





bool DFS_R(Graph *graph, bool visit[], int path[], int vertex)
{
	if(findVertexInGraph(graph, vertex)==false)
		return false;

	ofstream fout;
	fout.open("log.txt", ios::app);

	if(firstPrint==true){
		fout<<"======== DFS_R ========"<<endl;
		fout<<"startvertex: "<<vertex<<endl;
		firstPrint=false;
	}

	visit[vertex] = true; // 방문했으므로 true

	path[order]=vertex;
	order++;

	map<int, int> *m = new map<int, int>; // map 동적 할당
	graph->getAdjacentEdges(vertex, m);	  // 해당 vertex에 인접한 vertex들을 map에 담음

	map<int, int> *temp = m;

	for (map<int, int>::iterator iter = temp->begin(); iter != temp->end(); iter++)
	{
		int next = iter->first; // 다음 vetex(현재 vertex와 인접한 vertex)

		if (!visit[next])
		{
			fout.close();
			DFS_R(graph, visit, path, next);
		}
	}

	return true;
}

// 특정 원소가 속한 집합을 찾기
int findParent(int x, int parent[])
{
	// 루트 노드가 아니라면, 루트 노드를 찾을 때까지 재귀적으로 호출
	if (x == parent[x])
		return x;
	else
		return parent[x] = findParent(parent[x], parent);
}

// 두 원소가 속한 집합을 합치기
void unionParent(int a, int b, int parent[])
{
	a = findParent(a, parent);
	b = findParent(b, parent);
	if (a < b)
		parent[b] = a;
	else
		parent[a] = b;
}

bool Kruskal(Graph *graph)
{
	ofstream fout;
	fout.open("log.txt", ios::app);

	int v;
	int parent[100000];
	int cost = 0;

	vector<pair<int, pair<int, int>>> *edges = new vector<pair<int, pair<int, int>>>;

	v = graph->getSize();
	for (int i = 1; i <= v; i++)
	{
		parent[i] = i;
	}

	for (int i = 0; i < v; i++)
	{
		map<int, int> *m = new map<int, int>;
		if(graph->getSize()!=1 && graph->getAdjacentEdges(i, m)==false) // MST를 생성할 수 없는 경우(연결 안 된 vertex 존재)
			return false;

		map<int, int> *temp = m;
		for (map<int, int>::iterator iter = temp->begin(); iter != temp->end(); iter++)
		{
			edges->push_back({iter->second, {i, iter->first}});
		}
		delete m;
	}

	QuickSort(edges, 0, edges->size()-1);

	map<int, int> *m_List = new map<int, int>[v];
	vector<pair<int, pair<int, int>>>::iterator edgeIter = edges->begin(); 

	int j = 0;

	for (edgeIter = edges->begin(); j < v - 1; edgeIter++)
	{
		// second.first: 시작점 second.second: 도착점 edgeIter->first: 비용
		m_List[edgeIter->second.first].insert(pair<int, int>(edgeIter->second.second, edgeIter->first));
		m_List[edgeIter->second.second].insert(pair<int, int>(edgeIter->second.first, edgeIter->first));
		j++;
	}

	edgeIter = edges->begin();
	
	for (int i = 0; i < edges->size(); i++)
	{
		int tempCost, a, b;
		if(i==0){
			tempCost = edgeIter->first;
			a=edgeIter->second.first;	// 시작
			b=edgeIter->second.second; // 도착
		}
		else{
			++edgeIter;
			tempCost = edgeIter->first;
			a=edgeIter->second.first;	// 시작
			b=edgeIter->second.second; // 도착
		}
			// 사이클이 발생하지 않는 경우에만 집합에 포함
			if (findParent(a, parent) != findParent(b, parent))
			{
				unionParent(a, b, parent);
				cost += tempCost;
			}
	}

	fout<<"====== Kruskal ======="<<endl;

	for (int i = 0; i < v; i++)
	{
		fout << "[" << i << "] ";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
		{
			fout << it_->first << "(" << it_->second << ") ";
		}
		fout << endl;
	}
	fout << "cost: " << cost << endl;
	fout<<"====================="<<endl<<endl;

	delete edges;

	return true;
}


void QuickSort(vector<pair<int, pair<int, int>>> *a, const int low, const int high)
{
	int i, j, pivot;
	int segment_size = high-low+1;
	    if(low < high){
        if(segment_size<=6){
            InsertionSort(a, low, high);
        }
        else{
            pair<int, pair<int, int>> forSwap;
			pivot = partition(a, low, high);
            i = low + 1;
            j = high;
			do{
        		 do i++; while (a->at(i).first<pivot);
        		 do j--; while (a->at(j).first>pivot);
         		 if (i <= j){
					forSwap=a->at(i);
					a->at(i)=a->at(j);
					a->at(j)=forSwap;
				 } //swap(arr[i], arr[j]);
      		}while(i < j);
            forSwap = a->at(low);
            a->at(low) = a->at(j);
            a->at(j) = forSwap;

            QuickSort(a, low, pivot - 1);
            QuickSort(a, pivot + 1, high);
        }

    }
}

int partition(vector<pair<int, pair<int, int>>> *a, int low, int high)
{
	return a->at(low).first;
}

void InsertionSort(vector<pair<int, pair<int, int>>>* a, int low, int high){
	int j;
    pair<int, pair<int, int>> forSwap;
    for (int i = low + 1; i <= high; i++){
        forSwap = a->at(i);
        for (j = i - 1; j >= low; j--){ 
            if(a->at(j).first > forSwap.first)
                a->at(j + 1) = a->at(j);
            else
                break;
        }
        a->at(j+1) = forSwap;
    }
}

bool Dijkstra(Graph *graph, int vertex)
{
	if(findVertexInGraph(graph, vertex)==false)
		return false;
		
	ofstream fout;
	fout.open("log.txt", ios::app);
	int v, weight;

	int size = graph->getSize(); // v는 graph의 size
	list<pair<int, int>>* adj=new list<pair<int, int>>[size]; // 특정 노드에서 인접한 노드 및 weight 저장
	//list<int>* prev=new list<int>[size]; // 경로 저장용
	vector<int>*shortestPath = new vector<int>(graph->getSize()); // 경로 저장용
	
	for(int i=0; i<size; i++){ // adj에 다 담는 과정
		map<int, int>*m=new map<int, int>;
		graph->getAdjacentEdges(i, m);

		map<int, int> *temp = m;
		for(auto iter = temp->begin(); iter!=temp->end(); iter++){
			if(iter->second<0)
				return false;
			adj[i].push_back(make_pair(iter->first, iter->second)); // second가 weight
		}
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 우선 순위 큐 사용

	vector<int> dist(graph->getSize(), INF); // 특정 노드에서 모든 다른 노드에 대한 거리를 무한대로 초기화

	pq.push(make_pair(0, vertex)); // 처음에 시작 노드를 push함(weight는 0으로)
	dist[vertex]=0; // 시작 vertex는 어차피 자신에 대한 최후의 최단 경로는 0임

	while(!pq.empty()){ 
		int u = pq.top().second; // first는 weght(거리), second는 vertex
		pq.pop();

		list<pair<int, int>>::iterator i;
		for(i = adj[u].begin(); i != adj[u].end(); ++i){ // u는 특정 노드
			v = (*i).first; // v는 특정 노드에 인접한 노드
			weight = (*i).second; // weight는 특정 노드->인접 노드의 weight

			if(dist[v] > dist[u] + weight){ // 기존에 v노드로 가는 거리보다 
				dist[v] = dist[u] + weight;
				//prev[v].push_back(u);
				(*shortestPath)[v]=u;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	fout<<"========= Dijkstra ========="<<endl;
	fout<<"startvertex: "<<vertex<<endl;
	fout.close();
	// 0부터 각 정점까지의 경로 출력
    for (int i = 0; i < size; i++) {
		if(i == vertex)
       		continue;
		fout.open("log.txt", ios::app);
		fout<<"["<<i<<"] ";
		fout.close();
	    if(dist[i] == INF){
			fout.open("log.txt", ios::app);
            fout<<"x";
            fout<<endl;
			fout.close();
            continue;
        }
		printPath(0, i, vertex, shortestPath);
		fout.open("log.txt", ios::app);
		fout<<i<<" ("<<dist[i]<<")";
		
        fout<<endl;
		fout.close();
    }

	fout.open("log.txt", ios::app);
	fout<<"=========================="<<endl<<endl;
	fout.close();

	return true;
}

void printPath(int start, int i, int vertex, vector<int>* from) {
	ofstream fout;
	fout.open("log.txt", ios::app);
    // 기저 조건 : 시작점과 목적지가 같은 경우  
    if ((*from)[i] == start) {
		if(vertex!=0 && start==0)
			return;
        fout << start << " -> ";
        return;
    }

    // 재귀호출을 통해 정점 e전의 정점에 대한 경로를 출력한다..  
    printPath(start, (*from)[i], vertex, from);
    
    // 최단경로에서 정점 e 바로 이전의 정점를 화면에 출력한다.  
    fout << (*from)[i] << " -> ";
	fout.close();
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex)
{
   if(findVertexInGraph(graph, s_vertex)==false || findVertexInGraph(graph, e_vertex)==false)
      return false;

   ofstream fout;
   fout.open("log.txt", ios::app);
   int size=graph->getSize();

   list<pair<int, int>>* adj=new list<pair<int, int>>[size]; // 특정 노드에서 인접한 노드 및 weight 저장

   	for(int i=0; i<size; i++){ // adj에 다 담는 과정
		map<int, int>*m=new map<int, int>;
		graph->getAdjacentEdges(i, m);

		map<int, int> *temp = m;
		for(auto iter = temp->begin(); iter!=temp->end(); iter++){
			if(s_vertex!=iter->first)
				adj[i].push_back(make_pair(iter->first, iter->second)); // second가 weight
		}
	}

   vector<int>*shortestPath = new vector<int>(size); // 경로 저장용
   vector<int> dist(graph->getSize(), INF);

   dist[s_vertex]=0;

   for(int n=0; n<size-1; n++){
	for(int i=0; i<size; i++){
		for(auto iter=adj[i].begin(); iter!=adj[i].end(); iter++){
			int v=iter->first;
			int weight=iter->second;

			if(dist[i]!=INF && dist[v]>dist[i]+weight){
				(*shortestPath)[v]=i;
				dist[v]=dist[i]+weight;
			}
		}
	}
   }

   for(int i=0; i<size; i++){
	for(auto iter=adj[i].begin(); iter!=adj[i].end(); iter++){
			int v=iter->first;
			int weight=iter->second;

			if(dist[i]!=INF && dist[v]>dist[i]+weight)
				fout<<"음의 사이클"<<endl;
	}
   }

	fout<<"====== Bellman-Ford ======"<<endl;

	if(dist[e_vertex]==INF)
		fout<<"x"<<endl;
	else{
		printPath(0, e_vertex, s_vertex, shortestPath);

		fout<<e_vertex<<endl;
		fout<<"cost: "<<dist[e_vertex]<<endl;
	}
	
	fout<<"=========================="<<endl<<endl;

	fout.close();

    return true;
}

void find_path(int s, int e, int dist[], int prev[]) {
    ofstream fout;
    fout.open("log.txt", ios::app);
    if (s == e) {
        return;
    }
    find_path(s, prev[e], dist, prev);
    cout << " -> " << e;
    fout << " -> " << e;
    return;
}

bool FLOYD(Graph *graph)
{
	ofstream fout;
	fout.open("log.txt", ios::app);

	int size=graph->getSize(); // get graph's size
	int** length = new int*[size]; //선언하고자 하는 이차원 배열의 행의 수 만큼 동적 할당
    for(int i = 0; i < size; i++){ //각각의 인덱스에 선언하고자 하는 배열의 크기만큼을 가르키게 함.
       length[i] = new int[size];
    }

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			length[i][j]=INF;
		}
	}
	for(int i=0; i<size; i++){
        map<int, int> *m=new map<int, int>;
        graph->getAdjacentEdges(i, m);
        for(auto it = m->begin(); it!=m->end(); it++){
            	length[i][it->first] = it->second;
        }
    }

	for(int i=0; i<size; i++)
		length[i][i]=0;


	int** dist = new int*[size]; //선언하고자 하는 이차원 배열의 행의 수 만큼 동적 할당
    for(int i = 0; i < size; i++){ //각각의 인덱스에 선언하고자 하는 배열의 크기만큼을 가르키게 함.
       dist[i] = new int[size];
    }

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			dist[i][j]=length[i][j];
		}
	}

	for (int p = 0; p < size; p++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (dist[i][p] + dist[p][j] < dist[i][j]) {
					dist[i][j] = dist[i][p] + dist[p][j];
				}
			}
		}
	}
	
	for(int i=0; i<size; i++){
		if(dist[i][i]<0)
			return false;
	}

	fout<<"======== FLOYD ========"<<endl;
	fout<<'\t';
	for(int i=0; i<size; i++)
	{
		fout<<"["<<i<<"]"<<'\t';
	}
	fout<<endl;

	for(int i=0; i<size; i++)
	{
		fout<<"["<<i<<"]";
		for(int j=0; j<size && fout<<'\t'; j++)
		{
			if(dist[i][j]==INF)
				fout<<"x";
			else
				fout<<dist[i][j];
		}
		fout<<endl;
	}
	fout<<"====================="<<endl<<endl;

	return true;

}


bool findVertexInGraph(Graph *graph, int vertex){
	int initialVertex=0;
	int lastVertex=graph->getSize()-1;
	if(vertex>=initialVertex && vertex<=lastVertex){
		return true;
	}
	else
		return false;
}