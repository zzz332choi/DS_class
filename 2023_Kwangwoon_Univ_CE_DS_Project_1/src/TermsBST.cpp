#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{
}
TermsBST::~TermsBST()
{
	_delete_all(root); // dynamic deallocation
}

TermsBSTNode *TermsBST::getRoot()
{
	return root;
}

// calculate end date
char *calculate_end_date(char *start, char type)
{
	char *p = strtok(start, "-");
	int y = atoi(p);
	p = strtok(NULL, "-");
	int m = atoi(p);
	p = strtok(NULL, "-");
	int d = atoi(p);

	switch (type)
	{
	case 'A':
		m += 5;
		y += (m + 1) / 13; // y add 1 if m is over 12
		m %= 12;		   // m's value is 0 ~ 11
		m++;			   // m must keep the form of the month.
		break;
	case 'B':
		y += 1;
		break;
	case 'C':
		y += 2;
		break;
	case 'D':
		y += 3;
		break;
	defalut:
		break;
	}

	char *s = new char[strlen(start) + 1];
	sprintf(s, "%04d-%02d-%02d", y, m, d);

	return s;
}

// insert
void TermsBST::_insert(MemberQueueNode data)
{

	TermsBSTNode *node;
	node->set_name(data.get_name());
	node->set_age(data.get_age());
	node->set_date(data.get_date());
	node->set_end_date(calculate_end_date(node->get_date(), data.get_condition_type()));

	if (root) {
		TermsBSTNode *ptr = root;

		while (1) {
			if (strcmp(ptr->get_end_date(), node->get_end_date()) < 0) {  
				if (ptr->getLeft())
					ptr = ptr->getLeft();
				else {
					ptr->setLeft(node);
					break;
				}
			}
			else {
				if(ptr->getRight())
					ptr = ptr->getRight();
				else {
					ptr->setRight(node);
					break;
				}
			}
		}
	}
	else
	{
		root = node;
	}
}
// print
void TermsBST::_print(TermsBSTNode *ptr)
{ // print node by in-order
	if (ptr)
	{
		_print(ptr->getLeft());
		//printf("%s/%02d/%s/%s\n", ptr->get_name(), ptr->get_age(), ptr->get_date(), ptr->get_end_date());
		// output is using file stream not console windows 
		_print(ptr->getRight());
	}
}
// delete
void TermsBST::_delete(char *str)
{
}
void TermsBST::_delete_all(TermsBSTNode *ptr)
{ // dynamic deallocation by post-order
	if (ptr)
	{
		_delete_all(ptr->getLeft());
		_delete_all(ptr->getRight());
		delete ptr; // dynamic deallocation
	}
}