#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <string>

using namespace std;

class Manager
{
private:

	ifstream	fcmd;
	ofstream	flog;

	MemberQueue queue;
	TermsBST Termsbst;


public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	void print_info(string str);

	// LOAD
	void LOAD();
	// ADD
	void ADD(string str);
	// QPOP
	void QPOP();
	// SEARCH
	void SEARCH(string str);
	// PRINT
	// DELETE
};
