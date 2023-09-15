#pragma once
#include "MemberQueueNode.h"
#include <string>
#include <iostream>
#include <cstring>

class MemberQueue
{
private:
	MemberQueueNode * head = nullptr, * tail = nullptr;
	int size = 0;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string str);
	MemberQueueNode pop();
	MemberQueueNode front();
};

