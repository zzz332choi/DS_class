#define _CRT_SECURE_NO_WARNINGS
#include "TermsList.h"

TermsLIST::TermsLIST() : head(nullptr)
{

}
TermsLIST::~TermsLIST()
{
	delete head;
	head = nullptr;
}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
void TermsLIST::INSERT(MemberQueueNode data) {

	char condition_type = data.get_condition_type();

	if (head) { // head is not nullptr
		TermsListNode* ptr = head, * prev = nullptr;

		while (ptr) {
			prev = ptr;
			if (ptr->get_condition_type() == condition_type) { // match the condion type
				ptr->set_data(data);
				break;
			}
			else { ptr = ptr->getNext(); }
		}

		if (!ptr) { // no such condition_type
			ptr = new TermsListNode;
			ptr->set_data(data);
			ptr->set_condition_type(condition_type);
			prev->setNext(ptr);
		}

	}

	else { // There isn't linked list
		head = new TermsListNode;
		head->set_condition_type(condition_type);
		head->set_data(data);
	}

}


// search
//Returns a node in a linked list that matches condition type
TermsListNode* TermsLIST::SEARCH(char c)
{
	TermsListNode* ptr = head;
	if (ptr) {
		while (ptr) {
			if (ptr->get_condition_type() == c) { // Return node in linked list if matched
				return ptr;
			}
			else ptr = ptr->getNext(); // no match
		}
	}
	return nullptr;
}



// delete 
// Delete by namebst
void TermsLIST::DELETE(MemberQueueNode* node)
{
	TermsListNode* ptr = head, *prev = nullptr;
	char type = node->get_condition_type();

	while (ptr) {
		if (ptr->get_condition_type() != type) {
			prev = ptr;
			ptr = ptr->getNext();
		}
		else { // match
			ptr->get_root()->DELETE(node);
			ptr->set_cnt(ptr->get_cnt() - 1);

			if (ptr->get_cnt());
			else { // Zero nodes corresponding to type
				if (prev) { // delete except for the head
					prev->setNext(ptr->getNext());
					delete ptr;
				}
				else { // delete head
					head = head->getNext();
					delete ptr;
				}
			}

			break;
		}
	}
}

// Delete by Terms
char* TermsLIST::DELETE_(char* str)
{
	TermsListNode* ptr = head, * prev = nullptr;
	char name[21] = { 0 };

	while (ptr) {
		strcpy(name, ptr->get_root()->DELETE_(str));
		if (strcmp(name, "END")) { // Reducing the number of people after performing deletion
			ptr->set_cnt(ptr->get_cnt() - 1);
			break;
		}

		ptr = ptr->getNext();
	}

	ptr = head;
	while (ptr) { //Operation node deletion when zero members
		if (!ptr->get_cnt()) {
			if (!prev) {
				head = head->getNext();
				delete ptr;
				ptr = head;
			}
			else {
				prev->setNext(ptr->getNext());
				delete ptr;
				ptr = prev;
			}
		}

		else {
			prev = ptr;
			ptr = ptr->getNext();
		}
	}

	return name;
}
