#include "GraphMethod.h"
# define INF 0x3f3f3f3f // define infinite number to 0x3f3f3f3f
bool firstPrint=true;
int order=0;

bool BFS(Graph *graph, int vertex) // bfs function
{
	if(findVertexInGraph(graph, vertex)==false) // Exception Handling
		return false;

	ofstream fout;
	fout.open("log.txt", ios::app); // print to log.txt
			
	bool visited[graph->getSize()]; // for check visit
	for (int i = 0; i < graph->getSize(); i++) // initilize false
		visited[i] = false;
	visited[vertex] = true; // vertex is visit

	queue<int> q; // declare queue
	q.push(vertex); // puth vetex to q

	fout<<"======== BFS ========"<<endl;
	fout<<"startvertex: "<<vertex<<endl;

	if (graph->getSize() == 1) // if graph size is 1, print without "->"
	{
		fout << vertex << endl;
		return true;
	}
	else // print vertex
		fout << vertex;

	while (!q.empty()) // loop while q is empty
	{
		vertex = q.front(); // set vertex
		q.pop(); // pop

		map<int, int> *m = new map<int, int>; // map dynamic allocation
		graph->getAdjacentEdges(vertex, m); // get adjacent edges data to m

		map<int, int>::iterator iter;

		for (iter = m->begin(); iter != m->end(); iter++) // m's begin to end-1
		{
			int next = iter->first; // set next vertex

			if (!visited[next]) // if next vertex is not visitted
			{
				visited[next] = true; // set true

				// line 51~line 64 last visit it not print "->"
				int k = 0; 
				for (int j = 0; j < graph->getSize(); j++) // graph size
				{ // judge visit count
					if (visited[j] == true)
						k++;
				}

				if (k == graph->getSize()) // if visit count is same with graph size
				{
					fout << " -> " << next << endl; // print vertex
					fout<<"====================="<<endl<<endl;
					return true; // retur true
				}

				q.push(next); // push the next vertex
				fout << " -> " << next;
			}
		}
		delete m; // delete
	}
	fout<<endl;
	fout<<"====================="<<endl<<endl;

	return true; // return true
}

bool DFS(Graph *graph, int vertex) // DFS function
{
	if(findVertexInGraph(graph, vertex)==false) // Exception Handling
		return false;
		
	ofstream fout; // print to log.txt
	fout.open("log.txt", ios::app);

	bool visited[graph->getSize()]; // for check visit
	for (int i = 0; i < graph->getSize(); i++) // initilize false
		visited[i] = false;
	visited[vertex] = true; // vertex is visit

	stack<int> s; // use stack
	s.push(vertex); // push vertex to stack

	fout<<"======== DFS ========"<<endl;
	fout<<"startvertex: "<<vertex<<endl;

	if (graph->getSize() == 1) // 
	{ // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout << vertex << endl;
		return true;
	}
	else
		fout << vertex; // print vertex

	while (!s.empty()) // loop while stack is emtpy
	{						
		int current = s.top(); // current vertex is stack's pop
		s.pop();			   // pop

		map<int, int> *m = new map<int, int>; // map dynamic alllocation
		graph->getAdjacentEdges(current, m);  // get adjacent edges to m

		map<int, int>::iterator iter;
		for (iter = m->begin(); iter != m->end(); iter++) // loop begin to end-1
		{					// map is automatically ascending sort
			int next = iter->first; // set next vertex(this vertex is adjacent with current vertex)

			if (!visited[next]) // if next vertex is not visited
			{				
				visited[next] = true; // set true

				int k = 0; // if it is last visit, it don't print "->"
				for (int j = 0; j < graph->getSize(); j++)
				{ 
					if (visited[j] == true) // visit count
						k++;
				}

				if (k == graph->getSize()) // if visit count is same with graph's size
				{ 
					fout << " -> " << next << endl; // print
					fout<<"====================="<<endl<<endl;
					return true; // return true
				}

				s.push(current); // reason to why to push current is more vertex can exist
				s.push(next); // next repeat cycle, top is being next
				fout << " -> " << next; // print
				break;
			}
		}
		delete m; // deallocate
	}
	fout<<endl;
	fout<<"====================="<<endl<<endl;

	return true;
}

bool DFS_R(Graph *graph, bool visit[], int path[], int vertex) // DFS_R function
{
	if(findVertexInGraph(graph, vertex)==false) // exception handling
		return false; // return false

	ofstream fout; // print to log.txt
	fout.open("log.txt", ios::app);

	if(firstPrint==true){ // if it is firstprint
		fout<<"======== DFS_R ========"<<endl;
		fout<<"startvertex: "<<vertex<<endl;
		firstPrint=false;
	}

	visit[vertex] = true; // set true

	path[order]=vertex; // save path
	order++;

	map<int, int> *m = new map<int, int>; // map allocate
	graph->getAdjacentEdges(vertex, m);	  // get adjacent edges to m

	map<int, int> *temp = m;

	for (map<int, int>::iterator iter = temp->begin(); iter != temp->end(); iter++) // iterator
	{
		int next = iter->first; // set next vertex

		if (!visit[next])
		{
			fout.close();
			DFS_R(graph, visit, path, next); // recursive
		}
	}

	return true; // return true
}

int findOperation(int x, int parent[]) // find certain vertex's set
{
	if (x == parent[x])
		return x;
	else
		return parent[x] = findOperation(parent[x], parent); // find while root
}

void unionOperation(int a, int b, int parent[]) // union two sets
{
	a = findOperation(a, parent);
	b = findOperation(b, parent);
	if (a < b) // think reverse
		parent[b] = a; // b's parent is a
	else
		parent[a] = b; // a's parent is b
}

bool Kruskal(Graph *graph) // Kruskal algorithm
{
	ofstream fout; // print for log.txt
	fout.open("log.txt", ios::app);

	int parent[99999]; // declare parent array
	int size=graph->getSize(); // size is graph's size
	for (int i = 1; i <= size; i++) // 
		parent[i] = i;
	int cost = 0; // cost

	vector<pair<int, pair<int, int>>> *edges = new vector<pair<int, pair<int, int>>>; // dynamic allocation

	for (int i = 0; i < size; i++)
	{
		map<int, int> *m = new map<int, int>; // allocate map
		if(graph->getSize()!=1 && graph->getAdjacentEdges(i, m)==false) // exception handling(not generate MST-exist not connected vertex) 
			return false; // return false

		map<int, int> *temp = m; 
		for (map<int, int>::iterator iter = temp->begin(); iter != temp->end(); iter++) // loop with iterator
			edges->push_back({iter->second, {i, iter->first}}); // push to edges(adjacent edge)
		delete m; // deallocate
	}

	QuickSort(edges, 0, edges->size()-1); // use quick sort

	map<int, int> *m_List = new map<int, int>[size]; // allocate m_list
	vector<pair<int, pair<int, int>>>::iterator edgeIter = edges->begin(); // set iterator 

	int j = 0;

	for (edgeIter = edges->begin(); j < size - 1; edgeIter++) // loop with iterator
	{
		// second.first: start second.second: end edgeIter->first: cost
		m_List[edgeIter->second.first].insert(pair<int, int>(edgeIter->second.second, edgeIter->first)); // set m_List
		m_List[edgeIter->second.second].insert(pair<int, int>(edgeIter->second.first, edgeIter->first)); // set m_List
		j++;
	}

	edgeIter = edges->begin(); // use edgeIterator
	
	for (int i = 0; i < edges->size(); i++) // loop until edges->size()-1
	{
		int tempCost, a, b;
		if(i==0){
			tempCost = edgeIter->first; // save tempcost(for calculate)
			a=edgeIter->second.first;	// start
			b=edgeIter->second.second; // end
		}
		else{
			++edgeIter;
			tempCost = edgeIter->first; // save tempcost(for calculate)
			a=edgeIter->second.first;	// start
			b=edgeIter->second.second; // end
		}

		if (findOperation(a, parent) != findOperation(b, parent)) // if not generate cycle
		{
			unionOperation(a, b, parent); // use union
			cost += tempCost; // renewal cost
		}
	}

	fout<<"====== Kruskal ======="<<endl; // print kruskal

	for (int i = 0; i < size; i++) // while size-1
	{
		fout << "[" << i << "] "; // print vertex

		for (auto it = m_List[i].begin(); it != m_List[i].end(); it++) // auto iterator
		{
			fout << it->first << "(" << it->second << ") "; // destination vertex and cost
		}
		fout << endl;
	}
	fout << "cost: " << cost << endl; // fout cost
	fout<<"====================="<<endl<<endl;

	delete edges;

	return true;
}


void QuickSort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high) // quick sort
{
	int i, j, pivot;
	int segment_size = high-low+1; // set segment_size
	
	if(low < high){ 
	 	if(segment_size<=6) // if segment_size 6, use insertion sort
            InsertionSort(arr, low, high); // insertion sort
        else{
            pair<int, pair<int, int>> forSwap; // for sawp element
			pivot = partition(arr, low, high); // set the pivot pseudo code
            i = low + 1; // set i value
            j = high; // set j value
			do{
        		 do i++; while (arr->at(i).first<pivot); // increase i to find bigger than pivot
        		 do j--; while (arr->at(j).first>pivot); // decrease j to find smaller than pivot
         		 if (i <= j){
					forSwap=arr->at(i); // it is same with swap(arr[i], arr[j])
					arr->at(i)=arr->at(j); // swap setp
					arr->at(j)=forSwap; // swap complete
				 } //swap(arr[i], arr[j]);
      		}while(i < j);
            forSwap = arr->at(low); // swap step. set pivot
            arr->at(low) = arr->at(j);
            arr->at(j) = forSwap;

            QuickSort(arr, low, pivot - 1); // recursive
            QuickSort(arr, pivot + 1, high); // recursive
		}
	}
}

int partition(vector<pair<int, pair<int, int>>> *arr, int low, int high) // partition fuction
{
	return arr->at(low).first; // set arr's location
}

void InsertionSort(vector<pair<int, pair<int, int>>>* arr, int low, int high){ // insertion sort algorithm
	int j;
    pair<int, pair<int, int>> forSwap; // variable to use swap
    for (int i = low + 1; i <= high; i++){ // set loop range
        forSwap = arr->at(i); // set forSwap
        for (j = i - 1; j >= low; j--){  // set loop range
            if(arr->at(j).first > forSwap.first)
                arr->at(j + 1) = arr->at(j); // change j+1 with j
            else
                break;
        }
        arr->at(j+1) = forSwap; // set forSwap to arr->at(j+1)
    }
}

bool Dijkstra(Graph *graph, int vertex) // Dijkstar algorithm
{
	if(findVertexInGraph(graph, vertex)==false) // exception handling
		return false; // return false
		
	ofstream fout; // print to log.txt
	fout.open("log.txt", ios::app);
	int v, weight; 

	int size = graph->getSize(); // v는 graph의 size
	list<pair<int, int>>* adj=new list<pair<int, int>>[size]; // certain vertx with adjacne vertex and wight
	vector<int>*shortestPath = new vector<int>(graph->getSize()); // for savving path
	
	for(int i=0; i<size; i++){ // step to get the data to m
		map<int, int>*m=new map<int, int>; // allocate
		graph->getAdjacentEdges(i, m); // getAjdacentDdge

		map<int, int> *temp = m;
		for(auto iter = temp->begin(); iter!=temp->end(); iter++){ // iterator 
			if(iter->second<0) // exception handling - Dijkstra do not have negative weight
				return false; // return false
			adj[i].push_back(make_pair(iter->first, iter->second)); // iter->second is weight
		}
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // use priority queue

	vector<int> dist(graph->getSize(), INF); // initialize certain vertex to the other vertex with weight

	pq.push(make_pair(0, vertex)); // push the vertex
	dist[vertex]=0; // first vertexs last shortest paht is 0

	while(!pq.empty()){ // loop while priority queue is empty
		int u = pq.top().second; // first is weght, second is vertex
		pq.pop(); // pop

		list<pair<int, int>>::iterator i; // iterator
		for(i = adj[u].begin(); i != adj[u].end(); ++i){ // u is ceratain vertex
			v = (*i).first; // v is adjacent vertex with certain vertex
			weight = (*i).second; // weight is weight of certain vertex to adjacent vertex

			if(dist[v] > dist[u] + weight){ // dist[v] > dist[u] + weight
				dist[v] = dist[u] + weight; // save the calculate value
				(*shortestPath)[v]=u; // renew the shortespath
				pq.push(make_pair(dist[v], v)); // push to priority queue the data
			}
		}
	}

	fout<<"========= Dijkstra ========="<<endl; // print Dijkstra
	fout<<"startvertex: "<<vertex<<endl;
	fout.close();

    for (int i = 0; i < size; i++) { // shortest path to the other vertex
		if(i == vertex) // same node is dont need distance
       		continue;
		fout.open("log.txt", ios::app); // print toe log.txt
		fout<<"["<<i<<"] ";
		fout.close();
	    if(dist[i] == INF){ // if distance of i is INFINITE
			fout.open("log.txt", ios::app);
            fout<<"x"; // print x
            fout<<endl;
			fout.close();
            continue; // continue
        }
		printPath(0, i, vertex, shortestPath); // print shortestpath to the other vertex
		fout.open("log.txt", ios::app);
		fout<<i<<" ("<<dist[i]<<")"; // print path and cost
		
        fout<<endl;
		fout.close();
    }

	fout.open("log.txt", ios::app);
	fout<<"=========================="<<endl<<endl;
	fout.close();

	return true; // return true
}

void printPath(int start, int i, int vertex, vector<int>* from) {
	ofstream fout;
	fout.open("log.txt", ios::app);
    if ((*from)[i] == start) {     // if start and end is same
		if(vertex!=0 && start==0)
			return;
        fout << start << " -> "; // print
        return;
    }

    printPath(start, (*from)[i], vertex, from); // call recursive, continuosly print the path to vertex
    
    fout << (*from)[i] << " -> "; // print shortest path vertex
	fout.close();
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex) // Bellmanford function
{
   if(findVertexInGraph(graph, s_vertex)==false || findVertexInGraph(graph, e_vertex)==false) // exception handling
      return false;

   ofstream fout; // fout is for logtxt
   fout.open("log.txt", ios::app);
   int size=graph->getSize(); // size is graph's size

   list<pair<int, int>>* adj=new list<pair<int, int>>[size]; // save the adjacent vertex and wiehgt

   	for(int i=0; i<size; i++){ // step get the data from m
		map<int, int>*m=new map<int, int>; // allocate m
		graph->getAdjacentEdges(i, m); // get adjacent edges to m

		map<int, int> *temp = m;
		for(auto iter = temp->begin(); iter!=temp->end(); iter++){ // use iterator to repeat
			if(s_vertex!=iter->first) // if start vertex is not same with iter
				adj[i].push_back(make_pair(iter->first, iter->second)); // second is weight
		}
	}

   vector<int>*shortestPath = new vector<int>(size); // declare for save shortest path
   vector<int> dist(graph->getSize(), INF); // initialize dist to infinite

   dist[s_vertex]=0; // first vertex set the 0

   for(int n=0; n<size-1; n++){ // repeat n-1
	for(int i=0; i<size; i++){ // repeat size
		for(auto iter=adj[i].begin(); iter!=adj[i].end(); iter++){ // automatical iterator for using adjacent edges
			int v=iter->first; // v is destination
			int weight=iter->second; // second is weight

			if(dist[i]!=INF && dist[v]>dist[i]+weight){ // renew the information
				(*shortestPath)[v]=i; // save shortest path
				dist[v]=dist[i]+weight; // save dist[i]+weight to dist[v]
			}
		}
	}
   }

   for(int i=0; i<size; i++){ // repeat size
	for(auto iter=adj[i].begin(); iter!=adj[i].end(); iter++){
			int v=iter->first; // set v and weight for catch the negative cycle
			int weight=iter->second;

			if(dist[i]!=INF && dist[v]>dist[i]+weight)
				return false; // exception handling to negative cycle
	}
   }

	fout<<"====== Bellman-Ford ======"<<endl;

	if(dist[e_vertex]==INF) // if shortes path is not exist
		fout<<"x"<<endl; // print x
	else{
		printPath(0, e_vertex, s_vertex, shortestPath); // print shortest path

		fout<<e_vertex<<endl; // print
		fout<<"cost: "<<dist[e_vertex]<<endl; // print cost
	}
	
	fout<<"=========================="<<endl<<endl;

	fout.close();

    return true; // return true
}

bool FLOYD(Graph *graph) // FLOYD algorithm
{
	ofstream fout; // for print
	fout.open("log.txt", ios::app);

	int size=graph->getSize(); // get graph's size
	int** length = new int*[size]; // dynamic allocation dimension 2 matrix
    for(int i = 0; i < size; i++){
       length[i] = new int[size];
    }

	for(int i=0; i<size; i++){ // initialize INFINITE number
		for(int j=0; j<size; j++){
			length[i][j]=INF;
		}
	}

	for(int i=0; i<size; i++){ // get adjacent edges and save into the length 
        map<int, int> *m=new map<int, int>;
        graph->getAdjacentEdges(i, m);
        for(auto it = m->begin(); it!=m->end(); it++){
            	length[i][it->first] = it->second;
        }
    }

	for(int i=0; i<size; i++) // same position's weight is 0
		length[i][i]=0;


	int** dist = new int*[size]; // dynamic allocation dimension 2 matrix
    for(int i = 0; i < size; i++){ 
       dist[i] = new int[size];
    }

	for(int i=0; i<size; i++){ // save dist to length
		for(int j=0; j<size; j++){
			dist[i][j]=length[i][j];
		}
	}

	for (int k = 0; k < size; k++) { // k
		for (int i = 0; i < size; i++) { // i
			for (int j = 0; j < size; j++) { // j
				if (dist[i][k] + dist[k][j] < dist[i][j]) { // save short cost
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	
	for(int i=0; i<size; i++){ // exception handling, if has negative cycle
		if(dist[i][i]<0) // <0
			return false; // return false
	}

	fout<<"======== FLOYD ========"<<endl;
	fout<<'\t'; // tab
	for(int i=0; i<size; i++) // print column
	{
		fout<<"["<<i<<"]"<<'\t';
	}
	fout<<endl;

	for(int i=0; i<size; i++) // repeat size
	{
		fout<<"["<<i<<"]"; // print row
		for(int j=0; j<size && fout<<'\t'; j++)
		{
			if(dist[i][j]==INF) // if dist is INFINITE, print the x
				fout<<"x";
			else
				fout<<dist[i][j]; // print weight
		}
		fout<<endl;
	}
	fout<<"====================="<<endl<<endl;

	return true;

}

bool findVertexInGraph(Graph *graph, int vertex){ // for exception handling
	int initialVertex=0;
	int lastVertex=graph->getSize()-1;
	if(vertex>=initialVertex && vertex<=lastVertex){ // search by range to the vertex
		return true; // return true
	}
	else
		return false; // return false
}