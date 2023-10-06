#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
	TermsLIST termslist;
	NameBST namebst;


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
	void SEARCH(char* str);
	// PRINT
	void PRINT(char* str);
	// DELETE
	void DELETE(char* str1, char* str2);
};
