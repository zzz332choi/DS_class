#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "NameBSTNode.h"

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
	MemberQueueNode* DELETE(char* name);
	void DELETE_(char* name); // delete by Termslist
	//NameBSTNode* pre(NameBSTNode* ptr, char* date, NameBSTNode*& prev);

};