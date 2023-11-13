#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
	int bpOrder;
public:
	Manager(int bpOrder)	//constructor
	{
		cmd = nullptr;
		bptree = nullptr;
		stree = nullptr;

		/* You must fill here */
		this->bpOrder = bpOrder;
		flog.open("log.txt", ios::app);

		if(!flog.is_open()) return;
	}

	~Manager()//destructor
	{
		/* You must fill here */
		if(flog.is_open()) flog.close();
		if(cmd) delete[] cmd;
		if(stree) delete stree;
		if(bptree) delete bptree;

	}


	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD();

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(int code);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(const char* cmd);

};

