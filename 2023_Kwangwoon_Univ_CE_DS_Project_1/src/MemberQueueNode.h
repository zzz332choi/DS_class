#pragma once
#include <cstring>

using namespace std;

class MemberQueueNode
{
private:
	char name[21] = {0};
	int age = 0;
	char date[11] = {0};
	char condition_type;

	MemberQueueNode* next = nullptr;

public:
	MemberQueueNode() {}
	virtual ~MemberQueueNode() {}

	void setting_name(const char* str) {
		strcpy(name, str);
	}
	void setting_age(const int num) {
		age = num;
	}
	void setting_date(const char* str) {
		strcpy(date, str);
	}
	void setting_condition_type(const char c) {
		condition_type = c;
	}
	void setting_next(MemberQueueNode *node) {
		next = node;
	}

	char* get_name() {
		return name;
	}
	int get_age() const {
		return age;
	}
	char* get_date() {
		return date;
	}
	char get_condition_type() const {
		return condition_type;
	}
	MemberQueueNode* get_next() const{
		return next;
	}
};