#pragma once
#include "MemberQueueNode.h"
#include <string>
#include <iostream>
#include <cstring>

class MemberQueue
{
private:
	MemberQueueNode circular_queue[101];
	int head = 0, tail = 0; // front, rear position

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string str);
	MemberQueueNode pop();
	MemberQueueNode front();
};

