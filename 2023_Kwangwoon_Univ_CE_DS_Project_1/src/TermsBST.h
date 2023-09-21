#pragma once
#include "TermsBSTNode.h"
#include <stdio.h>

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	char* calculate_end_date(char* start, char type);

	// insert
	void _insert(MemberQueueNode data);
	// print
	void _print(TermsBSTNode* ptr);
	// delete
	void find(TermsBSTNode*& ptr, TermsBSTNode*& par, char* str);
	void data_copy(TermsBSTNode* first, TermsBSTNode* second);
	void _delete(char* str);
	void _delete_all(TermsBSTNode* ptr);
};