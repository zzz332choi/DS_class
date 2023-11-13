#include "BpTree.h"
#include <queue>

#define endl '\n'

BpTree::~BpTree() {
	DELETE_ALL_NODES();
}

bool BpTree::Insert(LoanBookData* newData) {

	string name = newData->getName();

	 // check the same name 
	BpTreeNode* ptr = searchDataNode(name);


	if(ptr) { // BpTree aleady has same data
		ptr->getDataMap()->find(name)->second->updateCount();
		delete newData;
		return true;
	}

	else {
		if(root) {// root aleady exists

			BpTreeNode* pcur = root, *prev = nullptr;

			while(pcur->getMostLeftChild()) {

				if(name < pcur->getIndexMap()->begin()->first) { // move to the left
					pcur = pcur->getMostLeftChild();
				}

				else {
					auto it = pcur->getIndexMap()->begin();
					it++;

					if(it == pcur->getIndexMap()->end()) { // the map only has one data
						pcur = pcur->getIndexMap()->begin()->second; // move to the right
					}

					else { // the map has two nodes
						if(name < it->first) { // move to the middle
							pcur = pcur->getIndexMap()->begin()->second;
						}
						else {	// move to the right
							pcur = it->second;
						}
					}
				}
			}

			pcur->insertDataMap(name, newData); // insert the data
			if(excessDataNode(pcur)) splitDataNode(pcur); // split
		}

		else {	// root doesn't exist
			root = new BpTreeDataNode();
			root->insertDataMap(name, newData);
		}

	}

	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) { // Function to split data nodes

	BpTreeNode* leftchild = new BpTreeDataNode();
	string name(pDataNode->getDataMap()->begin()->first);

	leftchild->insertDataMap(name, pDataNode->getDataMap()->begin()->second);
	pDataNode->deleteMap(name);

	// set doubly linked list
	if(pDataNode->getPrev()) {
		pDataNode->getPrev()->setNext(leftchild);
	}
	
	leftchild->setPrev(pDataNode->getPrev());
	leftchild->setNext(pDataNode);
	pDataNode->setPrev(leftchild);

	BpTreeNode* Parent = pDataNode->getParent();

	if(Parent) { // index nodes exisist
		leftchild->setParent(Parent);

		Parent->insertIndexMap(pDataNode->getDataMap()->begin()->first, pDataNode);

		if(leftchild->getDataMap()->begin()->first < Parent->getIndexMap()->begin()->first) { // update leftchild	
			Parent->setMostLeftChild(leftchild);
		}
		else {
			if (Parent->getIndexMap()->size() == 2) {
				Parent->getIndexMap()->begin()->second = leftchild;
			}
			else {
				auto it = Parent->getIndexMap()->begin();
				it++;

				if (pDataNode->getDataMap()->begin()->first == it->first) {
					Parent->getIndexMap()->begin()->second = leftchild;
				}

				else {
					it->second = leftchild;
				}

			}
		}
		
		// more 
		if(excessIndexNode(Parent)) splitIndexNode(Parent);

	}

	else { // the level of Bptree is one
		BpTreeNode* Parent = new BpTreeIndexNode();

		Parent->insertIndexMap(pDataNode->getDataMap()->begin()->first, pDataNode);

		root = Parent;

		leftchild->setParent(Parent);
		pDataNode->setParent(Parent);

		Parent->setMostLeftChild(leftchild);

	}

}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) { // Function to split index nodes
	BpTreeNode* leftchild = new BpTreeIndexNode();
	string name(pIndexNode->getIndexMap()->begin()->first);

	// link to child (parent -> child)
	leftchild->insertIndexMap(name, pIndexNode->getIndexMap()->begin()->second);
	leftchild->setMostLeftChild(pIndexNode->getMostLeftChild());
	
	// linck to parent (child -> parent)
	leftchild->getMostLeftChild()->setParent(leftchild);
	pIndexNode->getIndexMap()->begin()->second->setParent(leftchild);

	pIndexNode->deleteMap(name);

	BpTreeNode* parent = pIndexNode->getParent();
	
	if(!parent) { // increase height & update root
		parent = new BpTreeIndexNode();
		root = parent;
	}

	auto it = pIndexNode->getIndexMap()->begin();

	parent->insertIndexMap(it->first, pIndexNode);

	leftchild->setParent(parent);
	pIndexNode->setParent(parent);

	if (leftchild->getIndexMap()->begin()->first < parent->getIndexMap()->begin()->first) { // update Mostleftchild
		parent->setMostLeftChild(leftchild);
	}

	else {
		if (parent->getIndexMap()->size() == 2) {
			parent->getIndexMap()->begin()->second = leftchild;
		}

		else {
			auto iter = parent->getIndexMap()->begin();
			iter++;

			if (leftchild->getIndexMap()->begin()->first < iter->first) parent->getIndexMap()->begin()->second = leftchild;
			else iter->second = leftchild;
		}
	}

	pIndexNode->setMostLeftChild(it->second);
	pIndexNode->deleteMap(it->first);

	if(excessIndexNode(parent)) splitIndexNode(parent);
}

BpTreeNode* BpTree::searchDataNode(string name) { // search node
	if (root) {

		BpTreeNode* pCur = root;

		while (pCur->getMostLeftChild()) {

			if (name < pCur->getIndexMap()->begin()->first)
				pCur = pCur->getMostLeftChild(); // move to the left
			else {
				if (pCur->getIndexMap()->size() == 1)
				{ // move to the middle
					pCur = pCur->getIndexMap()->begin()->second;
				}
				else
				{
					auto it = pCur->getIndexMap()->begin();
					it++;

					if (name < it->first)
						pCur = pCur->getIndexMap()->begin()->second; // move to the middle
					else
						pCur = it->second; // move to the right
				}
			}
		}

		if (pCur->getDataMap()->find(name) != pCur->getDataMap()->end()) {
			return pCur; // found
		}
		else {
			return nullptr;
		}
	}

	return nullptr; // not found
}

bool BpTree::searchBook(string name) { // search book 

	BpTreeNode* ptr = searchDataNode(name);

	if(!ptr) return false; // not found
	
	LoanBookData* data = ptr->getDataMap()->find(name)->second;

	// print
	*fout << "========SEARCH_BP========" << endl;
	if(data->getCode()) { // If the code is 000
		*fout << data->getName() << '/' << data->getCode() << '/'
			  << data->getAuthor() << '/' << data->getYear() << '/'
			  << data->getLoanCount() << endl;
	}
	else {				// other case 
		*fout << data->getName() << '/' << "000" << '/'
			  << data->getAuthor() << '/' << data->getYear() << '/'
			  << data->getLoanCount() << endl;		
	}
	*fout << "==========================" << endl << endl;

}

bool BpTree::searchRange(string start, string end) { // search within range
	
	BpTreeNode* ptr = root;

	if (!ptr) return false;

	// move to DataNode
	while(ptr->getMostLeftChild()) {
		if(start < ptr->getIndexMap()->begin()->first) { // move to the left
			ptr = ptr->getMostLeftChild();
		}
		else {											// move to the middle & right
			if(ptr->getIndexMap()->size() == 1) {		// move to the right
				ptr = ptr->getIndexMap()->begin()->second;
			}
			else {
				auto it = ptr->getIndexMap()->begin();
				it++;

				if(start < it->first) { // move to the middle
					ptr = ptr->getIndexMap()->begin()->second;
				}
				else ptr = it->second;	// move to the right
			}
		} 
	}

	bool flag = 0;

	BpTreeNode* pointer = ptr;

	while (pointer) {
		// Detect when it violates the conditions
		for (auto it = pointer->getDataMap()->begin(); it != pointer->getDataMap()->end(); it++) {
			if (start <= it->first && strncmp(it->first.c_str(), end.c_str(), end.length()) <= 0) {
				flag = 1;
				break;
			}
		}
		pointer = pointer->getNext();
	}
	
	if(!flag) return 0;

	*fout << "========SEARCH_BP========" << endl;

	while(strncmp(ptr->getDataMap()->begin()->first.c_str(), end.c_str(), strlen(end.c_str())) <= 0) {

		for (auto it = ptr->getDataMap()->begin(); it != ptr->getDataMap()->end(); it++) {
			if (start <= it->first && strncmp(it->first.c_str(), end.c_str(), end.length()) <= 0) {
				LoanBookData* data = it->second;

				// print
				if (data->getCode()) {
					*fout << data->getName() << '/' << data->getCode() << '/'
						<< data->getAuthor() << '/' << data->getYear() << '/'
						<< data->getLoanCount() << endl;
				}
				else {
					*fout << data->getName() << '/' << "000" << '/'
						<< data->getAuthor() << '/' << data->getYear() << '/'
						<< data->getLoanCount() << endl;
				}

			}
		}

		ptr = ptr->getNext(); // ptr moves to next ptr

		if (!ptr) break; // The next pointers do not exist or violate the conditions

	}

	*fout << "==========================" << endl << endl;

	return 1;

}

void BpTree::Delete(string name) { // Delete data that moves to selection tree

	BpTreeNode* ptr = searchDataNode(name);

	if (!ptr) return; // not found

	delete ptr->getDataMap()->find(name)->second;
	ptr->getDataMap()->find(name)->second = nullptr;
	ptr->deleteMap(name);

}

bool BpTree::PRINT_BP() { // print all information that exists on the data node in the B+-tree
	BpTreeNode* ptr = root;

	if(!root) return false;

	while(ptr->getMostLeftChild()) ptr = ptr->getMostLeftChild();

	if(!ptr) return false;

	BpTreeNode* test = ptr;

	bool flag = 0;

	while(test) {
		if(test->getDataMap()->size()) {
			flag = 1;
			break;
		}
		test = test->getNext();
	}

	if(!flag) return false;

	*fout << "========PRINT_BP========" << endl;

	while(ptr) {
		auto M = ptr->getDataMap();

		for(auto it = M->begin(); it != M->end(); it++) {
			LoanBookData* data = it->second;
			
			// print 
			if(data->getCode()) { // if the code is 000
				*fout << data->getName() << '/' << data->getCode() << '/'
					  << data->getAuthor() << '/' << data->getYear() << '/'
					  << data->getLoanCount() << endl;
			}
			else {				// the others
				*fout << data->getName() << '/' << "000" << '/'
					  << data->getAuthor() << '/' << data->getYear() << '/'
					  << data->getLoanCount() << endl;		
			}
		}

		ptr = ptr->getNext(); // ptr moves to the next pointer
	}

	*fout << "==========================" << endl << endl;

	return true;
}

void BpTree::DELETE_ALL_NODES() { // deallocation, free nodes
	
	BpTreeNode* ptr = root;
	queue <BpTreeNode*> q;

	while(ptr->getMostLeftChild()) ptr = ptr->getMostLeftChild(); // move to the leaf node

	BpTreeNode* leaf = ptr;

	q.push(root);
	ptr = q.front();
	q.pop();

	while(ptr) {	// delete index nodes
		if(ptr->getMostLeftChild()) {
			q.push(ptr->getMostLeftChild());
			for(auto iter = ptr->getIndexMap()->begin(); iter != ptr->getIndexMap()->end(); iter++){
				q.push(iter->second);
			}

			delete ptr;
		}

		if(q.empty()) break;

		ptr = q.front();
		q.pop(); 
	}
	

	while(leaf) { // delete data nodes
		BpTreeNode* x = leaf;
		leaf = leaf->getNext();
		for(auto iter = x->getDataMap()->begin(); iter != x->getDataMap()->end(); iter++) {
			delete iter->second;
		}
		delete x;
	}

}
