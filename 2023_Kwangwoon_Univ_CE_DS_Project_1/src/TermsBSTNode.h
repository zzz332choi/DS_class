#pragma once
#include <cstring>
#include "MemberQueue.h"
using namespace std;

class TermsBSTNode
{
private:
	char *name = nullptr;
	int age = 0;
	char *date = nullptr;
	char *end_date = nullptr;

	TermsBSTNode *left = nullptr;
	TermsBSTNode *right = nullptr;

public:
	TermsBSTNode() {}
	~TermsBSTNode() {
		delete[] name;
		delete[] date;
		delete[] end_date;
	}

	char *get_name() { return name; } 
	int get_age() { return age; }
	char *get_date() { return date; }
	char *get_end_date() { return end_date; }

	void set_name(char *str) // set name
	{
		name = new char[strlen(str) + 1];
		strcpy(name, str);
	}
	void set_age(int num) { age = num; } // set age
	void set_date(char *str) // set date
	{
		date = new char[strlen(str) + 1];
		strcpy(date, str);
	}
	void set_end_date(char *str) //set end date
	{
		end_date = new char[strlen(str) + 1];
		strcpy(end_date, str);
	}

	TermsBSTNode *getLeft() { return left; }
	TermsBSTNode *getRight() { return right; }

	void setLeft(TermsBSTNode *left) { this->left = left; }
	void setRight(TermsBSTNode *right) { this->right = right; }
};