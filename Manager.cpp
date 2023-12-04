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
			if(cmd.find(" ") == string::npos) {
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
		// print command
		else if(cmd.find("PRINT") != string::npos) {
			if(!PRINT()) printErrorCode(200);
		}

		// BFS command
		else if(cmd.find("BFS") != string::npos) {
			int pos = cmd.find(" "); // position of blank
			int index = pos+ 1;	
			
			// If vertex is not entered
			if(cmd.find(" ", index) == string::npos) {
				printErrorCode(300);
				continue;
			}

			char d = cmd[index];
			pos = cmd.find(" ", index);
			pos++;

			int v = stoi(cmd.substr(pos));

			if(!mBFS(d, v)) printErrorCode(300);
		}
		else if(cmd.find("DFS") != string::npos) {
			int pos = cmd.find(" "); // position of blank
			int index = pos + 1;

			// If vertex is not entered
			if (cmd.find(" ", index) == string::npos) {
				printErrorCode(400);
				continue;
			}

			char d = cmd[index];
			pos = cmd.find(" ", index);
			pos++;

			int v = stoi(cmd.substr(pos));

			if (!mDFS(d, v)) printErrorCode(400);
		}
		else if(cmd.find("KRUSKAL") != string::npos) {
			if (mKRUSKAL()); // success
			else printErrorCode(500); // fail
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

	string str;
	if(!getline(data, str)) return false; // file is empty
	
	char type = str[0];

	getline(data, str);

	int size = stoi(str);

	if(graph) delete graph;

	if(type == 'L') { // graph_L
		graph = new ListGraph(0, size);

		int from = 0;

		while(getline(data, str)) {
			if(str.find(" ") == string::npos) {
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
				pos = index + 1;
			}

			// last vertex
			int index = str.find(" ", pos);
			int weight = stoi(str.substr(pos, index - pos));
			graph->insertEdge(from, to++, weight);
			pos = index + 1;

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
	if(!graph) return false;

	if(BFS(graph, option, vertex, &fout)) return true;
	else return false;
}

bool Manager::mDFS(char option, int vertex)	
{
	if (!graph) return false;

	if (DFS(graph, option, vertex, &fout)) return true;
	else return false;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	return true;
}

bool Manager::mKRUSKAL()
{
	if (Kruskal(graph, &fout)) return true;
	else return false;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool Manager::mFLOYD(char option)
{
	return true;
}

bool Manager::mKwoonWoon(int vertex) {
	return true;
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


