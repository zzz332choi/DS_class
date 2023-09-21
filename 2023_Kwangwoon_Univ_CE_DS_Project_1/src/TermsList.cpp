#include "TermsList.h"

TermsLIST::TermsLIST(): head(nullptr)
{

}
TermsLIST::~TermsLIST()
{

}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
void TermsLIST::INSERT(MemberQueueNode data) {

	char condition_type = data.get_condition_type();
	
	if(head){ // head is not nullptr
		TermsListNode* ptr = head, *prev = nullptr;

		while(ptr) {
			prev = ptr;
			if(ptr->get_condition_type() == condition_type){ // match the condion type
				ptr->set_data(data);	
			}
			else { ptr = ptr->getNext(); }
		}

		if(!ptr) { // no such condition_type
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

// delete
void TermsList::DELETE(string str) {
	TermsListNode* ptr = head;

	while(ptr){
		TermsBST* root_ = ptr->get_root();
		root_->_delete(str);

		
	}
}