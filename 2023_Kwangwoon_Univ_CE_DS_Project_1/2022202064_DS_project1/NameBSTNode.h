#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "MemberQueue.h"

class NameBSTNode
{
private:

	char name[21] = { 0 };
	int age = 0;
	char date[11] = { 0 };
	char end_date[11] = { 0 };
	char condition_type = 0;

	NameBSTNode*	left = nullptr;
	NameBSTNode*	right = nullptr;
	

public:
	NameBSTNode() {}
	~NameBSTNode() {}

	char* get_name() { return name; }
	int get_age() { return age; }
	char* get_date() { return date; }
	char* get_end_date() { return end_date; }
	char get_condition_type() { return condition_type; }

	void set_name(char* str) // set name
	{
		strcpy(name, str);
	}
	void set_age(int num) { age = num; } // set age
	void set_date(char* str) // set date
	{
		strcpy(date, str);
	}
	void set_end_date(char* str) //set end date
	{
		strcpy(end_date, str);
	}
	void set_condition_type(char c) { // set condition type
		condition_type = c;
	}


	NameBSTNode*	getLeft()			{ return left; }
	NameBSTNode*	getRight()			{ return right; }

	void setLeft(NameBSTNode* left)						{ this->left = left; }
	void setRight(NameBSTNode* right)					{ this->right = right; }


};