#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		delete graph;
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
		command = strtok(ptr, "\t");
		commandFromtxt=command;

		if(commandFromtxt=="LOAD"){
			char* textfile;
			textfile=strtok(NULL, "\t");
			LOAD(textfile);
		}
		else if(commandFromtxt=="PRINT"){
			//PRINT();
		}
		else if(commandFromtxt=="BFS"){
			//mBFS();
		}
		else if(commandFromtxt=="DFS"){
			//mDFS();
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

}

bool Manager::PRINT()
{
	if(graph->printGraph())
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{

}

bool Manager::mDFS(int vertex)
{

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

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
