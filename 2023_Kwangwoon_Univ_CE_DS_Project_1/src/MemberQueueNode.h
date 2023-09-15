#pragma once
#include <cstring>

using namespace std;

class MemberQueueNode
{
private:
	char* name = nullptr;
	int age = 0;
	char* date = nullptr;
	char condition_type;

	MemberQueueNode* next = nullptr;

public:
	MemberQueueNode() {}
	virtual ~MemberQueueNode() {
		delete[] name;
		delete[] date;
	}

	void setting_name(const char* str) {
		name = new char [strlen(str) + 1];
		name[0] = 0;
		strcpy(name, str);
	}
	void setting_age(const int num) {
		age = num;
	}
	void setting_date(const char* str) {
		date = new char [strlen(str) + 1];
		date[0] = 0;
		strcpy(date, str);
	}
	void setting_condition_type(const char c) {
		condition_type = c;
	}
	void setting_next(MemberQueueNode *node) {
		next = node;
	}

	char* get_name() const {
		return name;
	}
	int get_age() const {
		return age;
	}
	char* get_date() const {
		return date;
	}
	char get_condition_type() const {
		return condition_type;
	}
	MemberQueueNode* get_next() const{
		return next;
	}
};