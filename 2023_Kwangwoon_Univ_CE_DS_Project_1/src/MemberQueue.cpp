#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
}
MemberQueue::~MemberQueue()
{
}

bool MemberQueue::empty()
{
    return head == tail;
}
bool MemberQueue::full()
{
    return ((tail + 1) % 101 == head);
}
void MemberQueue::push(string str)
{
    if (!full()) // it's ready for adding node
    {
        tail = (tail + 1) % 101;

        MemberQueueNode *node = &circular_queue[tail];
        char *s = new char[str.length() + 1];
        strcpy(s, str.c_str()); // copy str
        const char *p = strtok(s, " ");

        node->setting_name(p); // setting name
        p = strtok(NULL, " ");

        node->setting_age(atoi(p)); // setting age
        p = strtok(NULL, " ");

        node->setting_date(p); // setting date
        p = strtok(NULL, " ");

        node->setting_condition_type(p[0]); // setting condtion_type
    }

    else
        exit(0); // program shut down if queue is full
}
MemberQueueNode MemberQueue::pop()
{
    if (!empty()) {// queue must not be empty
        head = (head + 1) % 101;
        return circular_queue[head];
    }
    else
        exit(0); // program shut down if queue is empty
}
MemberQueueNode MemberQueue::front()
{
    if (!empty()) // queue must not be empty
        return circular_queue[(head + 1) % 101];
    else
        exit(0);
}