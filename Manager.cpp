#include "Manager.h"

Manager::Manager() // contructor
{
	graph = nullptr;
	undigraph=nullptr;
	fout.open("log.txt", ios::app); // print to log.txt
	load = 0;
}

Manager::~Manager() // destructor
{
	if(load){ // if load is true
		delete graph; // delete graph
		delete undigraph; // delete undigraph
	}

	fout.close(); // close file
}

void Manager::run(const char* command_txt){ // for function logic
	ifstream fin;
	fin.open(command_txt);
	string commandFromtxt; // for getline and save command
	char ptr[100]; // commandFromtxt(string to char*)
	char *command; // strtok for ptr
	char* str=NULL; // first argument
	char* str2=NULL; // second argument

	if(!fin) // print error code for command_txt
	{
		printErrorCode(100); // print error code
		return;
	}
	while(!fin.eof()){
		getline(fin, commandFromtxt, '\n'); // get the line of command.txt file
		if(commandFromtxt.empty()==true) // if command line is empty
			break;
		
		strcpy(ptr, commandFromtxt.c_str()); // copy
		command = strtok(ptr, " "); // save to char*
		commandFromtxt=command; // save to string

		if(commandFromtxt=="LOAD"){ // if command is LOAD
			char* textfile;
			textfile=strtok(NULL, "\n");
			if(textfile==NULL){  // exception handling
				printErrorCode(100); // print error code 100
				continue;
			}
				
			LOAD(textfile); // execute with textfile
		}
		else if(commandFromtxt=="PRINT"){ // if command is PRINT
			PRINT();
		}
		else if(commandFromtxt=="BFS"){ // if command is BFS
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){ // exception handling
				printErrorCode(300); // print error code 200
				continue;
			}
			int start=atoi(vertex);
			mBFS(start);
		}
		else if(commandFromtxt=="DFS"){ // if command is DFS
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){  // exception handling
				printErrorCode(400); // print error code 400
				continue;
			}
				
			int start=atoi(vertex);
			mDFS(start);
		}
		else if(commandFromtxt=="DFS_R"){ // if command is DFS_R
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){  // exception handling
				printErrorCode(500); // print error code 500
				continue;
			}
			
			int start=atoi(vertex); // char to int
			mDFS_R(start);
		}
		else if(commandFromtxt=="KRUSKAL"){ // if command is KRUSKAL
			mKRUSKAL();
		}
		else if(commandFromtxt=="DIJKSTRA"){
			char*vertex;
			vertex=strtok(NULL, "\n");
			if(vertex==NULL){  // exception handling
				printErrorCode(700); // print error code 700
				continue;
			}
				
			int start=atoi(vertex); // char to int
			mDIJKSTRA(start);
		}
		else if(commandFromtxt=="BELLMANFORD"){ // if command is BELLMANFORD
			char* charStart, *charEnd; // declare
			charStart=strtok(NULL, " ");
			charEnd=strtok(NULL, "\n");

			if(charStart==NULL || charEnd==NULL){  // exception handling
				printErrorCode(800); // print error code 800
				continue;
			}
			
			int start=atoi(charStart); // char to int
			int end=atoi(charEnd); // char to int

			mBELLMANFORD(start, end);
		}
		else if(commandFromtxt=="FLOYD"){ // if command is FLOYD
			mFLOYD(); 
		}
		else if(commandFromtxt=="EXIT"){ // if command is EXIT
			return; // return
		}
	}
	fin.close(); // close the file
}

bool Manager::LOAD(char* filename) // LOAD function
{
	if(load>=1){ // deallocate
		delete undigraph; 
		delete graph;
	}

	string strGraphFormat, strGraphSize, forGetLine; // declare
	int graphSize=0;
	char* ptr1, *ptr2, *ptr3;
	char*ptr;
	int from=0, to=0, weight=0;
	string strFileName=filename;

	if(strFileName=="graph_L.txt"){ // if file name is graph_L.txt
		ifstream graphLtxt;
		graphLtxt.open("graph_L.txt", ios::app); // open file

		if(!graphLtxt){ // if file occurs error
			printErrorCode(100); // print error code 100
			return false;
		}
		else{
			getline(graphLtxt, strGraphFormat, '\n'); 
			getline(graphLtxt, strGraphSize, '\n');
			graphSize=stoi(strGraphSize); // string to int
			graph=new ListGraph(0, graphSize); // directed graph
			undigraph=new MatrixGraph(0, graphSize); // 0 means list graph

			while(!graphLtxt.eof()){ // while file end
				getline(graphLtxt, forGetLine, '\n'); // getline
				char temp[200];
				strcpy(temp, forGetLine.c_str());
				to=0;
				weight=0;
				ptr1=strtok(temp, " "); // ptr1 is to vertex
				ptr2=strtok(NULL, "\n"); // ptr2 is weight

				if(ptr2==NULL){ // if second argumnet is NULL
					from=atoi(ptr1); // get from char to int
					graph->insertEdge(from, to, weight); // insert to edge
				}
				else{ // if second grgument is exist
					to=atoi(ptr1); // to vertex (char to int)
					weight=atoi(ptr2); // weight (char to in)
					graph->insertEdge(from, to, weight); // insert to edge
					undigraph->insertEdge(from, to, weight); // insert to undirected graph
					undigraph->insertEdge(to, from, weight); // insert to undigrected graph
					ptr1=NULL; // for next
					ptr2=NULL; // for next
				}
			}
		}
	}
	else if(strFileName=="graph_M.txt"){ // if file name is graph_M.txt
		ifstream graphMtxt;
		graphMtxt.open("graph_M.txt", ios::app); // open file

		if(!graphMtxt){ // if file occurs error
			printErrorCode(100); // print error code
			return false;
		}
		else{
			getline(graphMtxt, strGraphFormat, '\n'); // getline
			getline(graphMtxt, strGraphSize, '\n'); // getline
			graphSize=stoi(strGraphSize); // string to int
			graph=new MatrixGraph(1, graphSize); // inheritance
			undigraph=new MatrixGraph(1, graphSize); // inheritance
			
			int i=0, j=0;
			while(!graphMtxt.eof()){ // while file end
				getline(graphMtxt, forGetLine, '\n'); // getline
				char temp[200];
				strcpy(temp, forGetLine.c_str());
				ptr=strtok(temp, " ");
				weight=atoi(ptr); // wegith (char to int)
				graph->insertEdge(i, 0, weight); // insert edge
				if(weight!=0){ // if weight is not 0
					undigraph->insertEdge(i, 0, weight); // make undigraph
					undigraph->insertEdge(0, i, weight); // make undigraph
				}

				for(j=1; j<graphSize; j++){ // 
					ptr=strtok(NULL, " ");
					weight=atoi(ptr);
					graph->insertEdge(i, j, weight); // insert edge
					if(weight!=0){ // if weight is not 10
						undigraph->insertEdge(i, j, weight); // make undigraph
						undigraph->insertEdge(j, i, weight); // make undigraph
					}

				}
				i++;
			}
		}
	}
	else{
		printErrorCode(100); // if file name is not exit
		return false;
	}
	printSuccessCode("LOAD"); // prnit success code to LOAD
	load++;
}

bool Manager::PRINT() // PRINT graph
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(200); // print error code 200
		return false;
	}
	if(graph->printGraph()) // execute print function
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if(graph==NULL||undigraph==NULL){ // graph is not exist
		printErrorCode(300); // print error code
		return false;
	}
	if(BFS(undigraph, vertex)==false) // if vertex is not exit in graph
		printErrorCode(300);
}

bool Manager::mDFS(int vertex) // dfs
{
	if(graph==NULL||undigraph==NULL){ // graph is not exist
		printErrorCode(400);
		return false;
	}
	if(DFS(undigraph, vertex)==false) // if vertex is not exit in graph
		printErrorCode(400);
}


bool Manager::mDFS_R(int vertex)
{
	if(graph==NULL||undigraph==NULL){
		printErrorCode(500); // graph is not exist
		return false;
	}	
	bool visited[undigraph->getSize()]; // check for visit
	for(int i=0; i<undigraph->getSize(); i++) // 방문하지 않았으면 false이므로 초기화
		visited[i]=false; // initialize
	
	int path[undigraph->getSize()]; // get path
	for(int i=0; i<undigraph->getSize(); i++)
		path[i]=-1; // initialize

	if(DFS_R(undigraph, visited, path, vertex)==false){ // execute DFS_R function
		printErrorCode(500); // print error code
		return false;
	}

	for(int i=0; i<undigraph->getSize(); i++){ // print visit order result
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

bool Manager::mKRUSKAL() // kruskal
{
	if(graph==NULL||undigraph==NULL){ // if graph is not exist
		printErrorCode(600); // print error code
		return false;
	}
	if(Kruskal(graph)==false)  // if vertex is not exit in graph
		printErrorCode(600); // print error code
}

bool Manager::mDIJKSTRA(int vertex)
{
	if(graph==NULL||undigraph==NULL){ // if graph is not exist
		printErrorCode(700); // print error code
		return false;
	}
	if(Dijkstra(graph, vertex)==false) // if vertex is not exit in graph
		printErrorCode(700); // print error code
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if(graph==NULL||undigraph==NULL){ // if graph is not exist
		printErrorCode(800); // print error code
		return false;
	}
	if(Bellmanford(graph, s_vertex, e_vertex)==false) // if vertex is not exit in graph
		printErrorCode(800); // print error code
}

bool Manager::mFLOYD()
{
	if(graph==NULL||undigraph==NULL){ // if graph is not exist
		printErrorCode(900); // print error code
		return false;
	}
	if(FLOYD(graph)==false) // if vertex is not exit in graph
		printErrorCode(900); // print error cde
}

void Manager::printSuccessCode(string command) {// SUCCESS CODE PRINT 
	fout<<"======== "<<command<<" ========"<<endl;
	fout << "Success" << endl;
	fout << "=======================" << endl<<endl;
}

void Manager::printErrorCode(int n) // PRINT ERROR CODE
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl<<endl; 
}
