#pragma once
#include "TermsBST.h"

class TermsListNode
{
private:

	TermsBST* root = nullptr;
	int cnt = 0; // number of members
	char condition_type = 0;
	TermsListNode*	next = nullptr;


public:
	TermsListNode() {}
	~TermsListNode() {
		if(root) delete root;
	}

	TermsListNode*	getNext()		 { return next; }

	void set_condition_type(char c) { condition_type = c; }
	char get_condition_type() { return condition_type; }

	void set_data(MemberQueueNode data) { // Increase cnt when inserting data
		if (!root) root = new TermsBST;
		root->INSERT(data);
		cnt++;
	}

	int get_cnt() { return cnt; }
	void set_cnt(int cnt) { this->cnt = cnt; }

	TermsBST* get_root() { return root; }

	void setNext(TermsListNode* next)	 { this->next = next; }
};