#define _CRT_SECURE_NO_WARNINGS
#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{
}
TermsBST::~TermsBST()
{
	DELETE_all(root); // dynamic deallocation
}

TermsBSTNode *TermsBST::getRoot()
{
	return root;
}

// calculate end date
char *TermsBST::calculate_end_date(char *start, char type)
{
	char* s = new char[strlen(start) + 1];
	strcpy(s, start);
	char *p = strtok(s, "-");
	int y = atoi(p);
	p = strtok(NULL, "-");
	int m = atoi(p);
	p = strtok(NULL, "-");
	int d = atoi(p);

	delete[] s;

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
	default:
		break;
	}

	s = new char[strlen(start) + 1];
	sprintf(s, "%04d-%02d-%02d", y, m, d);

	return s;
}

// insert
void TermsBST::INSERT(MemberQueueNode data)
{

	TermsBSTNode *node = new TermsBSTNode;
	node->set_name(data.get_name());
	node->set_age(data.get_age());
	node->set_date(data.get_date());
	node->set_end_date(calculate_end_date(node->get_date(), data.get_condition_type()));

	if (root)
	{
		TermsBSTNode *ptr = root;

		while (ptr)
		{
			if (strcmp(ptr->get_end_date(), node->get_end_date()) >= 0)
			{
				if (ptr->getLeft())
					ptr = ptr->getLeft();
				else
				{
					ptr->setLeft(node);
					break;
				}
			}
			else
			{
				if (ptr->getRight())
					ptr = ptr->getRight();
				else
				{
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
void TermsBST::PRINT(TermsBSTNode *ptr)
{ // print node by in-order
	if (ptr)
	{
		PRINT(ptr->getLeft());
		flog << ptr->get_name() << '/' << ptr->get_age() << '/' << ptr->get_date() << '/' << ptr->get_end_date() << endl;
		PRINT(ptr->getRight());
	}
}

void TermsBST::data_copy(TermsBSTNode *first, TermsBSTNode *second)
{ // first data copies second node's data
	first->set_age(second->get_age());
	first->set_date(second->get_date());
	first->set_end_date(second->get_end_date());
	first->set_name(second->get_name());
}


// delete
char* TermsBST::DELETE_(char *str) // parameter is end_date
{
	TermsBSTNode* ptr = root, * prev = nullptr, * prevprev = nullptr, * curr = nullptr;
	char name[21] = { 0 };

	while (ptr) { 
		if (strcmp(str, ptr->get_end_date()) >= 0) {
			strcpy(name, ptr->get_name());
			break;
		}
		else {
			prev = ptr;
			ptr = ptr->getLeft();
		}
	}

	if (!ptr) {
		strcpy(name, "END");
		return name;// not found
	}
	if (!ptr->getLeft() && !ptr->getRight()) { // ptr is leaf node
		if (!prev) root = nullptr; // tree only has root
		else if (prev->getLeft() == ptr) prev->setLeft(nullptr);
		else prev->setRight(nullptr);
		delete ptr;
	}

	else if (!ptr->getLeft()) { // ptr only has right child
		if (!prev) root = ptr->getRight();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getRight());
		else prev->setRight(ptr->getRight());
		delete ptr;
	}

	else if (!ptr->getRight()) { // ptr only has left child
		if (!prev) root = ptr->getLeft();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getRight());
		else prev->setRight(ptr->getRight());
		delete ptr;
	}

	else { // ptr has left and right child
		prevprev = ptr;
		prev = ptr->getRight();
		curr = prev->getLeft();

		// Go to the right and repeat until nullptr to the left
		while (curr) {
			prevprev = prev;
			prev = curr;
			curr = curr->getLeft();
		}

		if (prevprev == ptr) prevprev->setRight(prev->getRight()); // Repetition has not progressed
		else prevprev->setLeft(prev->getRight());

		data_copy(ptr, prev);
		delete prev;
	}

	return name; // found
}

// Delete by NameBST
void TermsBST::DELETE(MemberQueueNode* node)
{
	char end_date[11] = { 0 };
	strcpy(end_date, calculate_end_date(node->get_date(), node->get_condition_type()));
	char name[21] = { 0 };
	strcpy(name, node->get_name());

	TermsBSTNode* ptr = root, * prev = nullptr, * prevprev = nullptr, * curr = nullptr;

	while (ptr) {
		if (strcmp(end_date, ptr->get_end_date()) < 0) {
			prev = ptr;
			ptr = ptr->getLeft();
		}
		else if (strcmp(end_date, ptr->get_end_date()) > 0) {
			prev = ptr;
			ptr = ptr->getRight();
		}
		else {
			if (strcmp(name, ptr->get_name())) { 
				// If the end date is the same, but the name is different,
				// it's on the right-hand side of the node
				
				prev = ptr;
				ptr = ptr->getRight();
			}
			else break; // match
		}
	}

	if (ptr) return; //  not found

	if (!ptr->getLeft() && !ptr->getRight()) { // ptr is leaf node
		if (!prev) root = nullptr; // tree only has root
		else if (prev->getLeft() == ptr) prev->setLeft(nullptr);
		else prev->setRight(nullptr);
		delete ptr;
	}

	else if (!ptr->getLeft()) { // ptr only has right child
		if (!prev) root = ptr->getRight();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getRight());
		else prev->setRight(ptr->getRight());
		delete ptr;
	}

	else if (!ptr->getRight()) { // ptr only has left child
		if (!prev) root = ptr->getLeft();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getRight());
		else prev->setRight(ptr->getRight());
		delete ptr;
	}

	else { // ptr has left and right child
		prevprev = ptr;
		prev = ptr->getRight();
		curr = prev->getLeft();

		// Go to the right and repeat until nullptr to the left
		while (curr) {
			prevprev = prev;
			prev = curr;
			curr = curr->getLeft();
		}

		// copy info
		ptr->set_age(prev->get_age());
		ptr->set_date(prev->get_date());
		ptr->set_name(prev->get_name());
		ptr->set_end_date(prev->get_end_date());

		if (prevprev == ptr) prevprev->setRight(prev->getRight()); // Repetition has not progressed
		else prevprev->setLeft(prev->getRight());
		delete prev;
	}

	return;
}

void TermsBST::DELETE_all(TermsBSTNode *ptr)
{ // dynamic deallocation by post-order
	if (ptr)
	{
		DELETE_all(ptr->getLeft());
		DELETE_all(ptr->getRight());
		delete ptr; // dynamic deallocation
	}
}

void TermsBST::FILEOPEN()
{
	flog.open("log.txt", ios::app); //Open a file by adding
}

void TermsBST::FILECLOSE()
{
	flog.close();
}
