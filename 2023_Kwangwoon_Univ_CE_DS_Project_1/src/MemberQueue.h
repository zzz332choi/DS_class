#pragma once
#include "MemberQueueNode.h"
#include <string>
#include <iostream>
#include <cstring>

class MemberQueue
{
private:
	MemberQueueNode * front = nullptr, * rear = nullptr;
	int size = -1;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string str);
	MemberQueueNode pop();
	MemberQueueNode front();
};

