#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
		
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}
	
	string cmd; // command
	while(getline(fin, cmd)) {
		// load command
		if(cmd.find("LOAD") != string::npos) {
			// If the factor is insufficient
			if(cmd.find(" ") != string::npos) {
				printErrorCode(100);
				continue;
			}

			int pos = cmd.find(" ");
			pos++;
	
			if(LOAD(cmd.substr(pos).c_str())) {
				fout << "========LOAD=======" << endl;
				fout << "Success" << endl;
				fout << "====================" << endl << endl;
			}
			else printErrorCode(100);
		}
		else if(cmd.find("PRINT") != string::npos) {
			if(!PRINT()) printErrorCode(200);
		}
		else if(cmd.find("BFS") != string::npos) {

		}
		else if(cmd.find("DFS") != string::npos) {

		}
		else if(cmd.find("KRUSKAL") != string::npos) {

		}
		else if(cmd.find("DIJKSTRA") != string::npos) {

		}
		else if(cmd.find("BELLMANFORD") != string::npos) {

		}
		else if(cmd.find("FLOYD") != string::npos) {

		}
		else if(cmd.find("KWANGWOON") != string::npos) {

		}
		else if(cmd.find("EXIT") != string::npos) {

		}
		// an invalid command
		else printErrorCode(1000);
	}	


	fin.close();
	return;
}

bool Manager::LOAD(const char* filename)
{
	ifstream data;
	data.open(filename);

	// If a text file does not exist
	if(!data) return false;

	char type;
	data >> type;

	int size;
	data >> size;

	if(graph) delete graph;

	if(type == 'L') { // graph_L
		graph = new ListGraph(0, size);

		string str;
		int from;

		while(getline(data, str)) {
			if(str.find(" ") != string::npos) {
				from = stoi(str);
			}
			else {
				int to, weight;
				int pos = str.find(" ");

				to = stoi(str.substr(0, pos++));
				weight = stoi(str.substr(pos));

				graph->insertEdge(from, to, weight);
			}
		}
	}

	else {	// graph_M
		graph = new MatrixGraph(1, size);

		string str;
		int from = 0;

		while(getline(data, str)) {
			int to = 0;
			int pos= 0;

			while(str.find(" ", pos) != string::npos) {
				int index = str.find(" ", pos);
				int weight = stoi(str.substr(pos, index-pos));
				graph->insertEdge(from, to++, weight);
				pos++;
			}
			from++;
		}
	}

	return true;
}

bool Manager::PRINT()	
{
	if(!graph) return false;

	if(!graph->printGraph(&fout)) return false;
	else return  true;
}

bool Manager::mBFS(char option, int vertex)	
{
	
}

bool Manager::mDFS(char option, int vertex)	
{
	
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	
}

bool Manager::mKRUSKAL()
{
 	
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	
}

bool Manager::mFLOYD(char option)
{
	
}

bool Manager::mKwoonWoon(int vertex) {
	
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


