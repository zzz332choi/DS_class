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
	void DELETE_BY_NAME(MemberQueueNode* node); // Delete by namebst
	char* DELETE_BY_DATE(char* node); // Delete by Terms

	void DELETE_ALL(); // delete all by exit command
};
