#pragma once
#include "TermsBST.h"
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;


public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	void INSERT(MemberQueueNode data);
	// search
	void SEARCH();
	// delete
	void DELETE(string str);
};
