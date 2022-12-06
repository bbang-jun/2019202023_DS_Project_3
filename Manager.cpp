#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	undigraph=nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		delete graph;
		delete undigraph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
	string commandFromtxt; // for getline and save command
	char ptr[100]; // commandFromtxt(string to char*)
	char *command; // strtok for ptr
	char* str=NULL; // first argument
	char* str2=NULL; // second argument

	if(!fin) // print error code for command_txt
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	while(!fin.eof()){
		getline(fin, commandFromtxt, '\n'); // get the line of command.txt file
		if(commandFromtxt.empty()==true) // if command line is empty
			break;
		
		strcpy(ptr, commandFromtxt.c_str());
		command = strtok(ptr, " ");
		commandFromtxt=command;

		if(commandFromtxt=="LOAD"){
			char* textfile;
			textfile=strtok(NULL, "\n");
			LOAD(textfile);
		}
		else if(commandFromtxt=="PRINT"){
			PRINT();
		}
		else if(commandFromtxt=="BFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			int start=atoi(vertex);
			mBFS(start);
		}
		else if(commandFromtxt=="DFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			int start=atoi(vertex);
			fout<<"======== DFS ========"<<endl;
			fout<<"startvertex: "<<start<<endl;
			mDFS(start);
			fout<<"====================="<<endl;
		}
		else if(commandFromtxt=="DFS_R"){
			//mDFS_R();
		}
		else if(commandFromtxt=="KRUSKAL"){
			//mDIJKSTRA();
		}
		else if(commandFromtxt=="DIKSTRA"){
			//mDIJKSTRA();
		}
		else if(commandFromtxt=="BELLMANDFORD"){
			//mBELLMANFORD();
		}
		else if(commandFromtxt=="FLOYD"){
			//mFLOYD();
		}
		else if(commandFromtxt=="EXIT"){
			
		}
	}
	// char buf[129]={0};

	// while(fin.getline(buf, 128))
	// {

	// }	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	string strGraphFormat, strGraphSize, forGetLine;
	int graphSize=0;
	char* ptr1, *ptr2, *ptr3;
	char*ptr;
	int from=0, to=0, weight=0;
	string strFileName=filename;

	bool judge=true;

	if(strFileName=="graph_L.txt"){
		ifstream graphLtxt;
		graphLtxt.open("graph_L.txt", ios::app);

		if(!graphLtxt){ // if file occurs error
			printErrorCode(100);
			return false;
		}
		else{
			getline(graphLtxt, strGraphFormat, '\n');
			getline(graphLtxt, strGraphSize, '\n');
			graphSize=stoi(strGraphSize);
			graph=new ListGraph(0, graphSize); // 다형성?
			undigraph=new ListGraph(0, graphSize); // 0은 list graph를 의미

			while(!graphLtxt.eof()){
				getline(graphLtxt, forGetLine, '\n'); // 0
				char temp[200];
				strcpy(temp, forGetLine.c_str());

				ptr1=strtok(temp, " ");
				ptr2=strtok(NULL, "\n"); // "\n" 아니면 " "

				if(ptr2==NULL){ // 2번째 인자가 없는 경우
					from=atoi(ptr1); // from 생성
					if(judge==false){
						// edge가 없는 그래프 구현 해야 함
						to=-1;
						weight=-1;
						graph->insertEdge(from, to, weight);  // 여기서부터 3개 아래는 사실상 지금 의미 x
						undigraph->insertEdge(from, to, weight);
						undigraph->insertEdge(to, from, weight);
					}
					
					judge=false;
				}
				else{ // 2번째 인자가 있으면 to, weight임
					to=atoi(ptr1);
					weight=atoi(ptr2);
					graph->insertEdge(from, to, weight);
					undigraph->insertEdge(from, to, weight);
					undigraph->insertEdge(to, from, weight);
					ptr1=NULL;
					ptr2=NULL;
					judge=true;
				}
			}
		}
	}
	else if(strFileName=="graph_M.txt"){
		ifstream graphMtxt;
		graphMtxt.open("graph_M.txt", ios::app);

		if(!graphMtxt){ // if file occurs error
			printErrorCode(100);
			return false;
		}
		else{
			getline(graphMtxt, strGraphFormat, '\n');
			getline(graphMtxt, strGraphSize, '\n');
			graphSize=stoi(strGraphSize);
			graph=new MatrixGraph(1, graphSize); // 상속
			undigraph=new MatrixGraph(1, graphSize);
			
			int i=0, j=0;
			while(!graphMtxt.eof()){
				getline(graphMtxt, forGetLine, '\n');
				char temp[200];
				strcpy(temp, forGetLine.c_str());
				ptr=strtok(temp, " ");
				weight=atoi(ptr);
				graph->insertEdge(i, 0, weight);
				if(weight!=0){
					undigraph->insertEdge(i, 0, weight);
					undigraph->insertEdge(0, i, weight);
				}

				for(j=1; j<graphSize; j++){
					ptr=strtok(NULL, " ");
					weight=atoi(ptr);
					graph->insertEdge(i, j, weight);
					if(weight!=0){
						undigraph->insertEdge(i, j, weight);
						undigraph->insertEdge(j, i, weight);
					}

				}
				i++;
			}
		}
	}
}

bool Manager::PRINT()
{
	if(graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if(graph->getType()==0){ // if graph format is List
		
	}
	else if(graph->getType()==1){ // if graph format is Matrix

	}
}

bool Manager::mDFS(int vertex) // dfs
{
	bool check[undigraph->getSize()]; // 방문했는지 체크하는 bool형 배열
	for(int i=0; i<undigraph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		check[i]=false;
	
	s.push(vertex); // stack에 push(시작 vertex)
	check[vertex]=true; // 방문했으므로 true
	if(undigraph->getSize()==1) // graph에 노드가 하나만 있으면 "->" 없이 출력(처음 노드 출력)
		fout<<vertex;
	else // 처음 노드 출력
		fout<<vertex<<" -> ";

	while(!s.empty()){ // stack이 empty일 때까지 반복
		int current = s.top(); // 현재 vertex는 stack의 top
		s.pop(); // pop

		map<int, int>*m = new map<int, int>; // map 동적 할당
		undigraph->getAdjacentEdges(current, m); // 해당 vertex에 인접한 vertex들을 map에 담음

		map<int, int>::iterator iter; 
		for(iter=m->begin(); iter!=m->end(); iter++){ // 해당 vertex에 인접한 모든 vertex(map) - map은 오름차순 자동 정렬
			int next=iter->first; // 다음 vetex(현재 vertex와 인접한 vertex)

			if(!check[next]){ // false인 경우, 즉 다음 vertex가 방문하지 않았다면
				check[next]=true; // 방문할 것이므로 true

				int k=0; // 마지막 방문이면 "->"가 출력되지 않아야 하므로 이를 판단하기 위한 변수
				for(int j=0; j<undigraph->getSize(); j++){ // 해당 그래프에서 방문한 횟수 판단
					if(check[j]==true)
						k++;
				}

				if(k==undigraph->getSize()) // 해당 그래프에서 모든 vertex를 방문했으면
					fout<<next; // "->" 없이 출력
				else // 아직 모든 vertex를 방문하지 않았으면
					fout<<next<<" -> "; // "->" 있도록 출력
			
				s.push(current); // current를 다시 push하는 이유는 인접한 vertex가 next뿐만 아니라 여러개 있을 수도 있기 때문
				s.push(next); // 다음 반복시 top이 next가 됨(next의 next를 위해)
				break;
			}
		}
	}

	fout<<endl;
}


bool Manager::mDFS_R(int vertex)
{

}

bool Manager::mDIJKSTRA(int vertex)
{

}

bool Manager::mKRUSKAL()
{

}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{

}

bool Manager::mFLOYD()
{

}

void Manager::printSuccessCode(string command) {// SUCCESS CODE PRINT 
	fout<<"======== "<<command<<" ========"<<endl;
	fout << "Success" << endl;
	fout << "=======================" << endl;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl; 
}
