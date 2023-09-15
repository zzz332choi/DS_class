#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
}
MemberQueue::~MemberQueue()
{
}

bool MemberQueue::empty()
{
    return size; // if size > 0 return 1
}
bool MemberQueue::full()
{
    return size == 100;
}
void MemberQueue::push(string str)
{
    if (!full())
    {
        MemberQueueNode *node = new MemberQueueNode;
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

        // it's ready for adding node

        if (!empty())
        {           // if queue isn't empty
            size++; // queue size is increased
            tail->setting_next(node);
            tail = node; // now next_node is tail
        }
//asdfasdfasdf
        else
        {
            size++;             // The queue'size is 1
            head = tail = node; // first adding
        }
    }

    else
        exit(0); // program shut down if queue is full
}
MemberQueueNode MemberQueue::pop()
{
    if (!empty()) // queue must not be empty
    {
        MemberQueueNode *ptr = head;
        head = head->get_next();

        return *ptr;
    }
}
MemberQueueNode MemberQueue::front()
{
    return *head;
}