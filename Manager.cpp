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
	if(load){
		delete graph;
		delete undigraph;
	}

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
			if(textfile==NULL){
				printErrorCode(100);
				continue;
			}
				
			LOAD(textfile);
		}
		else if(commandFromtxt=="PRINT"){
			PRINT();
		}
		else if(commandFromtxt=="BFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){
				printErrorCode(300);
				continue;
			}
			int start=atoi(vertex);
			mBFS(start);
		}
		else if(commandFromtxt=="DFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){
				printErrorCode(400);
				continue;
			}
				
			int start=atoi(vertex);
			mDFS(start);
		}
		else if(commandFromtxt=="DFS_R"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){
				printErrorCode(500);
				continue;
			}
				

			int start=atoi(vertex);
			mDFS_R(start);
		}
		else if(commandFromtxt=="KRUSKAL"){
			mKRUSKAL();
		}
		else if(commandFromtxt=="DIJKSTRA"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){
				printErrorCode(700);
				continue;
			}
				
			int start=atoi(vertex);
			mDIJKSTRA(start);
		}
		else if(commandFromtxt=="BELLMANFORD"){
			char* charStart, *charEnd;
			charStart=strtok(NULL, " ");
			charEnd=strtok(NULL, "\n");

			if(charStart==NULL || charEnd==NULL){
				printErrorCode(800);
				continue;
			}
			
			int start=atoi(charStart);
			int end=atoi(charEnd);

			mBELLMANFORD(start, end);
		}
		else if(commandFromtxt=="FLOYD"){
			mFLOYD();
		}
		else if(commandFromtxt=="EXIT"){
			return;
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
	if(load>=1){
		delete undigraph;
		delete graph;
	}

	string strGraphFormat, strGraphSize, forGetLine;
	int graphSize=0;
	char* ptr1, *ptr2, *ptr3;
	char*ptr;
	int from=0, to=0, weight=0;
	string strFileName=filename;

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
			undigraph=new MatrixGraph(0, graphSize); // 0은 list graph를 의미

			while(!graphLtxt.eof()){
				getline(graphLtxt, forGetLine, '\n'); // 0
				char temp[200];
				strcpy(temp, forGetLine.c_str());
				to=0;
				weight=0;
				ptr1=strtok(temp, " ");
				ptr2=strtok(NULL, "\n"); // "\n" 아니면 " "

				if(ptr2==NULL){ // 2번째 인자가 없는 경우
					from=atoi(ptr1); // from 생성
					graph->insertEdge(from, to, weight);
				}
				else{ // 2번째 인자가 있으면 to, weightrjk
					to=atoi(ptr1);
					weight=atoi(ptr2);
					graph->insertEdge(from, to, weight);
					undigraph->insertEdge(from, to, weight);
					undigraph->insertEdge(to, from, weight);
					ptr1=NULL;
					ptr2=NULL;
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
	else{
		printErrorCode(100);
		return false;
	}
	printSuccessCode("LOAD");
	load++;
}

bool Manager::PRINT()
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(200);
		return false;
	}
	if(graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(300);
		return false;
	}
	if(BFS(undigraph, vertex)==false)
		printErrorCode(300);
}

bool Manager::mDFS(int vertex) // dfs
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(400);
		return false;
	}
	if(DFS(undigraph, vertex)==false)
		printErrorCode(400);
}


bool Manager::mDFS_R(int vertex)
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(500);
		return false;
	}	
	bool visited[undigraph->getSize()]; // 방문했는지 체크하는 bool형 배열
	for(int i=0; i<undigraph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i]=false;
	
	int path[undigraph->getSize()]; // 경로를 담아가지고 오는 용도
	for(int i=0; i<undigraph->getSize(); i++)
		path[i]=-1;

	if(DFS_R(undigraph, visited, path, vertex)==false){
		printErrorCode(500);
		return false;
	}

	for(int i=0; i<undigraph->getSize(); i++){
		if(path[++i]==-1){
			--i;
			fout<<path[i]<<endl;
			break;
		}
			
		i--;
		if(i==undigraph->getSize()-1){
			fout<<path[i];
			break;
		}
		fout<<path[i]<<" -> ";
	}

	fout<<endl;
	fout<<"====================="<<endl<<endl;	

	return true;
}

bool Manager::mKRUSKAL()
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(600);
		return false;
	}
	if(Kruskal(graph)==false)
		printErrorCode(600);
}

bool Manager::mDIJKSTRA(int vertex)
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(700);
		return false;
	}
	if(Dijkstra(graph, vertex)==false)
		printErrorCode(700);
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(800);
		return false;
	}
	if(Bellmanford(graph, s_vertex, e_vertex)==false)
		printErrorCode(800);
}

bool Manager::mFLOYD()
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(900);
		return false;
	}
	if(FLOYD(graph)==false)
		printErrorCode(900);
}

void Manager::printSuccessCode(string command) {// SUCCESS CODE PRINT 
	fout<<"======== "<<command<<" ========"<<endl;
	fout << "Success" << endl;
	fout << "=======================" << endl<<endl;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl<<endl; 
}
