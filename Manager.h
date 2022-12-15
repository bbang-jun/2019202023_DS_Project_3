#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{
private: // private
	Graph* graph;
	ofstream fout;
	int load;
	Graph* undigraph;

public: // public
	Manager(); // constructor
	~Manager(); // destructor

	void run(const char * command_txt); // run fuction
	
	bool LOAD(char* filename); // LOAD function
	bool PRINT(); // PRINT function
	
	bool mBFS(int vertex); // mBFS function
	bool mDFS(int vertex); // mDFS function
	bool mDFS_R(int vertex); // mDFS_R function
	bool mKRUSKAL(); // mKRUSKAL function
	bool mDIJKSTRA(int vertex); // mDIJKSTRA function
	bool mBELLMANFORD(int s_vertex, int e_vertex); // mBELLMANDFOR function
	bool mFLOYD(); // mFLOYD function

	void printSuccessCode(string command); // print success code
	void printErrorCode(int n);	// print error c ode
};

#endif