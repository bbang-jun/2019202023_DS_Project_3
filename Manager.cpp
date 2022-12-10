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
			if(textfile==NULL)
				printErrorCode(100);
			LOAD(textfile);
			printSuccessCode("LOAD");
		}
		else if(commandFromtxt=="PRINT"){
			PRINT();
		}
		else if(commandFromtxt=="BFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL)
				printErrorCode(300);
				
			int start=atoi(vertex);
			fout<<"======== BFS ========"<<endl;
			fout<<"startvertex: "<<start<<endl;
			mBFS(start);
			fout<<"====================="<<endl<<endl;
		}
		else if(commandFromtxt=="DFS"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL)
				printErrorCode(400);

			int start=atoi(vertex);
			fout<<"======== DFS ========"<<endl;
			fout<<"startvertex: "<<start<<endl;
			mDFS(start);
			fout<<"====================="<<endl<<endl;
		}
		else if(commandFromtxt=="DFS_R"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL)
				printErrorCode(500);

			int start=atoi(vertex);
			fout<<"======== DFS_R ========"<<endl;
			fout<<"startvertex: "<<start<<endl;

			mDFS_R(start);
			fout<<endl;
			fout<<"====================="<<endl<<endl;
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
}

bool Manager::PRINT()
{
	if(graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	BFS(undigraph, vertex);
}

bool Manager::mDFS(int vertex) // dfs
{
	DFS(undigraph, vertex);
}


bool Manager::mDFS_R(int vertex)
{			
	bool visited[undigraph->getSize()]; // 방문했는지 체크하는 bool형 배열
	for(int i=0; i<undigraph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i]=false;
	

	DFS_R(undigraph, visited, vertex);

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
	fout << "=======================" << endl<<endl;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl<<endl; 
}
