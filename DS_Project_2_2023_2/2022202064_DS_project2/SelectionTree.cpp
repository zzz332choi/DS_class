#include "SelectionTree.h"

#define endl '\n'

bool SelectionTree::Insert(LoanBookData* newData) { // Insert
    if(!root) INIT(); // initialization

    string str;

    int cnt = 8 + newData->getCode()/100;

    // find the location of lastE(last element)
    for (int i = 0; i <= 3; i++) {
        str.push_back(cnt % 2 + '0');
        cnt /= 2;
    }

    str.pop_back();

    int length = str.length() - 1;

    SelectionTreeNode* ptr = root, * prev = nullptr;

    // find the right location (position of run)
    while (length >= 0) {
        prev = ptr;
        if (str[length--] == '0') {
            ptr = ptr->getLeftChild();
        }
        else {
            ptr = ptr->getRightChild();
        }
    }

    LoanBookHeap* heap = nullptr;

    if (str[0] == '0') heap = ptr->getHeap();
    else heap = ptr->getHeap();
        
    if (heap) { // heap exists
        heap->Insert(newData);
    }

    else {  // heap doesn't exist
        heap = new LoanBookHeap();
        heap->Insert(newData);
        ptr->setHeap(heap);
    }

    // sotre bookdata
    ptr->setBookData(heap->getRoot()->getBookData());

	SelectionTreeNode* parent = ptr->getParent();

    // store bookdata from leaf to root
	while (parent) {
		if (parent->getBookData())
			if (parent->getBookData()->getName() < ptr->getBookData()->getName()) break;

		parent->setBookData(ptr->getBookData());
		ptr = parent;
		parent = parent->getParent();
	}

    return true;
}

bool SelectionTree::Delete() { // Delete the root's data and rearrange the selection tree

    SelectionTreeNode* ptr = root, *prev = nullptr;

    if (!root) return false;

    if(!root->getBookData()) return false;

    // delete(deallocation) from root to leafnode
    while (ptr->getLeftChild()) {
        prev = ptr;

        SelectionTreeNode* Lchild = ptr->getLeftChild(), * Rchild = ptr->getRightChild();

        if (Lchild->getBookData() && Rchild->getBookData()) {
            if (ptr->getBookData()->getCode() == Lchild->getBookData()->getCode()) ptr = ptr->getLeftChild();
            else ptr = ptr->getRightChild();
        }
        else if (Lchild->getBookData()) ptr = ptr->getLeftChild();
        else if (Rchild->getBookData()) ptr = ptr->getRightChild();
        else return false; // data doesn't exist. tree is empty

        prev->setBookData(nullptr);
    }

    ptr->getHeap()->Delete();

    if (!ptr->getHeap()->getRoot()) { // root doesn't exist
        ptr->setBookData(nullptr);
        delete ptr->getHeap();
        ptr->setHeap(nullptr);
    }
    // the root of heap is remained
    else    ptr->setBookData(ptr->getHeap()->getRoot()->getBookData());

	SelectionTreeNode* parent = ptr->getParent();

    // store from leafnode to root
	while (parent) {

		SelectionTreeNode* Lchild = parent->getLeftChild(), * Rchild = parent->getRightChild();

		if (Lchild->getBookData() && Rchild->getBookData()) {
			if (Lchild->getBookData()->getName() < Rchild->getBookData()->getName()) parent->setBookData(Lchild->getBookData());
			else parent->setBookData(Rchild->getBookData());
		}
		else if (Lchild->getBookData()) parent->setBookData(Lchild->getBookData());
		else if (Rchild->getBookData()) parent->setBookData(Rchild->getBookData());


		parent = parent->getParent();
	}

    return true;
}

bool SelectionTree::printBookData(int bookCode) { // print all data from Heap corresponding to bookcode

    if (!root) return false;

    string str;

    int cnt = 8 + bookCode / 100;

    // find the location of lastE(last element)
    for (int i = 0; i <= 3; i++) {
        str.push_back(cnt % 2 + '0');
        cnt /= 2;
    }

    str.pop_back();

    int length = str.length() - 1;

    SelectionTreeNode* ptr = root;

    // find the right location (position of run)
    while (length >= 0) {
        if (str[length--] == '0') {
            ptr = ptr->getLeftChild();
        }
        else {
            ptr = ptr->getRightChild();
        }
    }

    LoanBookHeap* heap = nullptr;

    heap = ptr->getHeap();


    if (!heap) return false; // no heap
  
    vector <LoanBookData*> v;

    while (heap->getRoot()) { // Store heap information in vectors
        LoanBookData* data = new LoanBookData(heap->getRoot()->getBookData()); // copy data from heap to vector
        v.push_back(data); // push info
        heap->Delete(); // delete operation 
    }

    if (v.empty()) return false; // no data

    *fout << "========PRINT_ST========" << endl;

    
    // print 
    while (!v.empty()) {
        if (v[0]->getCode()) {
            *fout << v[0]->getName() << '/' << v[0]->getCode() << '/'
                << v[0]->getAuthor() << '/' << v[0]->getYear() << '/'
                << v[0]->getLoanCount() << endl;
        }
        else {
            *fout << v[0]->getName() << '/' << "000" << '/'
                << v[0]->getAuthor() << '/' << v[0]->getYear() << '/'
                << v[0]->getLoanCount() << endl;
        }

        // insert heap
        heap->Insert(v[0]);
        v.erase(v.begin());
    }

    *fout << "==========================" << endl << endl;

    return true;
}

void SelectionTree::INIT() { // initialization

    // tree init
    SelectionTreeNode *arr[15] = {nullptr};
    
    for (int i = 0; i < 15; i++) arr[i] = new SelectionTreeNode();

    // allocate
    for (int i = 1; i < 8; i++) {
        arr[i - 1]->setLeftChild(arr[2 * i - 1]);
        arr[i - 1]->setRightChild(arr[2 * i]);
        arr[2 * i - 1]->setParent(arr[i - 1]);
        arr[2 * i]->setParent(arr[i - 1]);
    }

    root = arr[0];

}

void SelectionTree::Delete_selection_tree() // Delete all nodes in the selection tree
{
    if (!root) return;

    while (root->getBookData()) Delete();

    Delete_post(root);

    root = nullptr;
}

void SelectionTree::Delete_post(SelectionTreeNode* ptr) // delete nodes post-order
{
    if (ptr) {
        Delete_post(ptr->getLeftChild());
        Delete_post(ptr->getRightChild());
        if(ptr->getBookData()) delete ptr->getBookData();
        if(ptr->getHeap()) delete ptr->getHeap();
        delete ptr;
    }
}
