#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "NameBSTNode.h"
#include "TermsBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;
	ofstream flog;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	char* calculate_end_date(char* start, char type);
	// insert
	void INSERT(MemberQueueNode data);
	// search
	NameBSTNode* SEARCH(char* name);
	// print

	void FILEOPEN();
	void FILECLOSE();

	void PRINT(NameBSTNode* node);
	// delete
	MemberQueueNode* DELETE_BY_NAME(char* name);
	void DELETE_BY_DATE(char* name); // delete by Termslist
	
	void DELETE_ALL(NameBSTNode* node); // delete by exit code
};