#pragma once
#include <cstring>
#include "MemberQueue.h"
using namespace std;

class TermsBSTNode
{
private:
	char name[21] = {0};
	int age = 0;
	char date[11] = {0};
	char end_date[11] = {0};

	TermsBSTNode *left = nullptr;
	TermsBSTNode *right = nullptr;

public:
	TermsBSTNode() {}
	~TermsBSTNode() {
		if(left) delete left;
		if(right) delete right;
	}

	char *get_name() { return name; } 
	int get_age() { return age; }
	char *get_date() { return date; }
	char *get_end_date() { return end_date; }

	void set_name(char *str) // set name
	{
		strcpy(name, str);
	}
	void set_age(int num) { age = num; } // set age
	void set_date(char *str) // set date
	{
		strcpy(date, str);
	}
	void set_end_date(char *str) //set end date
	{
		strcpy(end_date, str);
	}

	TermsBSTNode *getLeft() { return left; }
	TermsBSTNode *getRight() { return right; }

	void setLeft(TermsBSTNode *left) { this->left = left; }
	void setRight(TermsBSTNode *right) { this->right = right; }
};