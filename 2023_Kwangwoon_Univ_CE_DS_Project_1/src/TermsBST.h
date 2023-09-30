#pragma once
#include "TermsBSTNode.h"
#include <fstream>
#include <stdio.h>

class TermsBST
{
private:
	TermsBSTNode* root;
	fstream flog;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	char* calculate_end_date(char* start, char type);

	// insert
	void INSERT(MemberQueueNode data);
	// print
	void PRINT(TermsBSTNode* ptr);

	// delete
	void data_copy(TermsBSTNode* first, TermsBSTNode* second);

	char* DELETE_(char* str);
	void DELETE(MemberQueueNode* node); // Delete node by namebst
	void DELETE_all(TermsBSTNode* ptr);

	void FILEOPEN();
	void FILECLOSE();
};