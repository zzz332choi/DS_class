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
	TermsListNode* SEARCH(char c);
	
	// delete
	void DELETE(MemberQueueNode* node); // Delete by namebst
	char* DELETE_(char* node); // Delete by Terms
};
