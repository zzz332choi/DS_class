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
char *TermsBST::calculate_end_date(char *start, char type)
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

	if (root)
	{
		TermsBSTNode *ptr = root;

		while (1)
		{
			if (strcmp(ptr->get_end_date(), node->get_end_date()) < 0)
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
void TermsBST::_print(TermsBSTNode *ptr)
{ // print node by in-order
	if (ptr)
	{
		_print(ptr->getLeft());
		// printf("%s/%02d/%s/%s\n", ptr->get_name(), ptr->get_age(), ptr->get_date(), ptr->get_end_date());
		//  output is using file stream not console windows
		_print(ptr->getRight());
	}
}

TermsBSTNode *TermsBST::find(const char *str, TermsBSTNode *ptr)
{ // find node by in-order
	if (ptr)
	{
		find(str, ptr->getLeft());
		if (!strcmp(str, ptr->get_end_date()))
			return ptr;
		find(str, ptr->getRight());
	}

	return nullptr;
}
void TermsBST::data_copy(TermsBSTNode *first, TermsBSTNode *second)
{ // first data copies second node's data
	first->set_age(second->get_age());
	first->set_date(second->get_date());
	first->set_end_date(second->get_end_date());
	first->set_name(second->get_name());
}
// delete
void TermsBST::_delete(char *str)
{
	TermsBSTNode *ptr = find(str, root);
	while (ptr)
	{
		if (ptr->getLeft())
		{
			if (ptr->getRight())
			{ // ptr has both child
				TermsBSTNode *node = ptr->getRight(), *pre_node = ptr;

				while (node->getLeft()) // move to the left until leftchild does not exist
				{
					pre_node = node;
					node = node->getLeft();
				}

				if (node->getRight())
				{
					data_copy(ptr, node);
					pre_node->setLeft(node->getRight());
					delete node;
				}
				else
				{
					data_copy(ptr, node);
					delete node;
					pre_node->setLeft(nullptr);
				}
			}
			else
			{ // ptr has only left child
				TermsBSTNode *node = ptr->getLeft(), *pre_node = ptr;

				while (node->getRight()) // move to the right untill rightchild does not exist
				{
					pre_node = node;
					node = node->getRight();
				}

				if (node->getLeft())
				{
					data_copy(ptr, node);
					pre_node->setRight(node->getLeft());
					delete node;
				}
				else
				{
					data_copy(ptr, node);
					delete node;
					pre_node->setRight(nullptr); 
				}
			}
		}
		else
		{
			if (ptr->getRight())
			{ // ptr has only right child
				TermsBSTNode* node = ptr->getRight(), * pre_node = ptr;

				while(node->getLeft()){ // move to the left untill left child does not exist.
					pre_node =node;
					node = node->getLeft();
				}

				if(node->getRight()) {
					data_copy(ptr, node);
					pre_node->setLeft(node->getRight());
					delete node;
				}
				else{
					data_copy(ptr, node);
					pre_node ->setLeft(nullptr);
					delete node;
				}
			}
			else
			{ // ptr doesn't have child
				TermsBSTNode* x =  &ptr;
			}
		}

		ptr = find(str, root);
	}
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