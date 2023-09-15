#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	// insert
	void _insert(MemberQueueNode data);
	// print
	void _print(TermsBSTNode* ptr);
	// delete
	void _delete(char* str);
	void _delete_all(TermsBSTNode* ptr);
};