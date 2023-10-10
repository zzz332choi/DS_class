#include "NameBST.h"

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
	return root;
}


// insert
void NameBST::INSERT(MemberQueueNode data)
{

	NameBSTNode* node = new NameBSTNode;
	node->set_name(data.get_name());
	node->set_age(data.get_age());
	node->set_date(data.get_date());
	
	char *p = calculate_end_date(data.get_date(), data.get_condition_type());
	node->set_end_date(p);
	delete p;

	node->set_condition_type(data.get_condition_type());

	if (root)
	{
		NameBSTNode* ptr = root;

		while (ptr)
		{
			if (strcmp(ptr->get_name(), node->get_name()) > 0)
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


// calculate end date
char* NameBST::calculate_end_date(char* start, char type)
{
	char* s = new char[strlen(start) + 1];
	strcpy(s, start);
	char* p = strtok(s, "-");
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

	char *date = nullptr;
	date = new char [11];
	date[0] = 0;
	
	date[0] = y / 1000 + '0'; // the seat of a thousand
	y %= 1000;
	date[1] = y / 100 + '0'; // the seat of a hundred
	y %= 100;
	date[2] = y / 10 + '0'; // the seat of a ten
	y %= 10;
	date[3] = y + '0'; // the seat of a one

	date[4] = '-';

	date[5] = m / 10 + '0'; // the seat of a ten
	date[6] = m % 10 + '0'; // the seat of a one

	date[7] = '-';

	date[8] = d / 10 + '0'; // the seat of a ten
	date[9] = d % 10 + '0'; // the seat of a one

	return date;
}
// search
NameBSTNode* NameBST::SEARCH(char* name)
{
	NameBSTNode* ptr = root, * prev = nullptr;

	while (ptr) {
		if (strcmp(name, ptr->get_name()) < 0) {
			prev = ptr;
			ptr = ptr->getLeft();
		}
		else if (strcmp(name, ptr->get_name()) > 0) {
			prev = ptr;
			ptr = ptr->getRight();
		}
		else break; // node is found 
	}

	return ptr;
}

void NameBST::FILEOPEN()
{
	flog.open("log.txt", ios::app);
}

void NameBST::FILECLOSE()
{
	flog.close();
}

//print
void NameBST::PRINT(NameBSTNode* node) // Print by in-order
{
	if (node) {
		PRINT(node->getLeft());
		flog << node->get_name() << '/' << node->get_age() << '/' << node->get_date() << '/' << node->get_end_date() << endl;
		PRINT(node->getRight());
	}
}


// delete
MemberQueueNode* NameBST::DELETE_BY_NAME(char* name)
{
	NameBSTNode* ptr = root, * prev = nullptr, * pprev = nullptr, * curr = nullptr;
	MemberQueueNode* node = new MemberQueueNode;

	while (ptr) {
		if (strcmp(name, ptr->get_name()) < 0) {
			prev = ptr;
			ptr = ptr->getLeft();
		}
		else if (strcmp(name, ptr->get_name()) > 0) {
			prev = ptr;
			ptr = ptr->getRight();
		}
		else { // match name
			// copy info before return 
			node->setting_age(ptr->get_age());
			node->setting_condition_type(ptr->get_condition_type());
			node->setting_date(ptr->get_date());
			node->setting_name(ptr->get_name());
			break;
		}
	}
	
	if (!ptr) {
		delete node;
		return nullptr; //not found
	}

	fstream fff;
	fff.open("log2.txt", ios::app);
	fff << "delete by name: "<< name << endl;
	fff.close();

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
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getLeft());
		else prev->setRight(ptr->getLeft());
		delete ptr;
	}

	else { // ptr has left and right child
		pprev = ptr;
		prev = ptr->getRight();
		curr = prev->getLeft();

		// Go to the right and repeat until nullptr to the left
		while (curr) {
			pprev = prev;
			prev = curr;
			curr = curr->getLeft();
		}

		// copy infomation
		ptr->set_age(prev->get_age());
		ptr->set_condition_type(prev->get_condition_type());
		ptr->set_date(prev->get_date());
		ptr->set_name(prev->get_name());
		ptr->set_end_date(prev->get_end_date());

		if (pprev == ptr) pprev->setRight(prev->getRight()); // Repetition has not progressed
		else pprev->setLeft(prev->getRight());
		delete prev;
	}

	return node;
}

void NameBST::DELETE_BY_DATE(char* name)
{
	NameBSTNode* ptr = root, * prev = nullptr, * prevprev = nullptr, * curr = nullptr;

	while (ptr) {
		if (strcmp(name, ptr->get_name()) > 0) {
			prev = ptr;
			ptr = ptr->getRight();
		}
		else if (strcmp(name, ptr->get_name()) < 0) {
			prev = ptr;
			ptr = ptr->getLeft();
		}
		else break;
	}

	if (!ptr) {
		return;// not found
	}

	fstream fff;
	fff.open("log2.txt", ios::app);
	fff << "delete by date: "<<name << endl;
	fff.close();

	if (!ptr->getLeft() && !ptr->getRight()) { // ptr is leaf node
		if (!prev) root = nullptr; // tree only has root
		else if (prev->getLeft() == ptr) prev->setLeft(nullptr);
		else prev->setRight(nullptr);
		delete ptr;
	}

	else if (!ptr->getLeft() && ptr->getRight()) { // ptr only has right child
		if (!prev) root = ptr->getRight();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getRight());
		else prev->setRight(ptr->getRight());
		delete ptr;
	}

	else if (ptr->getLeft() && !ptr->getRight()) { // ptr only has left child
		if (!prev) root = ptr->getLeft();
		else if (prev->getLeft() == ptr) prev->setLeft(ptr->getLeft());
		else prev->setRight(ptr->getLeft());
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

		ptr->set_age(prev->get_age());
		ptr->set_condition_type(prev->get_condition_type());
		ptr->set_date(prev->get_date());
		ptr->set_end_date(prev->get_end_date());
		ptr->set_name(prev->get_name());

		delete prev;
	}

	return; // found
}

void NameBST::DELETE_ALL(NameBSTNode* node) // delte by exit code 
{
	if (node) { // post-order delete
		DELETE_ALL(node->getLeft());
		DELETE_ALL(node->getRight());
		delete node;
	}
	return;
}
