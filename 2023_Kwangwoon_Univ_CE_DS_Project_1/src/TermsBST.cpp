#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{
}
TermsBST::~TermsBST()
{
	//_delete_all(root); // dynamic deallocation
}

TermsBSTNode *TermsBST::getRoot()
{
	return root;
}

// insert
void TermsBST::_insert(MemberQueueNode data) {
	if(root){

	}
	else{
		root = new TermsBSTNode;
		
	}
}
// print
void TermsBST::_print(TermsBSTNode *ptr) { // print node by in-order
	if(ptr){
		_print(ptr->getLeft());
		printf("%s/%02d/%s/%s\n", ptr->get_name(), ptr->get_age(), ptr->get_date(), ptr->get_end_date());
		_print(ptr->getRight());
	}
}
// delete
void TermsBST::_delete(char *str) {

}
void TermsBST::_delete_all(TermsBSTNode* ptr){ // dynamic deallocation by post-order
	if(ptr){
		_delete_all(ptr->getLeft());
		_delete_all(ptr->getRight());
		delete ptr; // dynamic deallocation
	}
}