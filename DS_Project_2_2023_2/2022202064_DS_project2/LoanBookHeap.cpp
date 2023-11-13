#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) { // heap insert

    LoanBookHeapNode* ptr = pN, *Parent = pN->getParent();
    LoanBookData* tmp = ptr->getBookData();

    if (!root) return;

    while (ptr != root && Parent->getBookData()->getName() > tmp->getName()) {
        ptr->setBookData(Parent->getBookData());
        ptr = Parent;
        Parent = ptr->getParent();
    }

    ptr->setBookData(tmp);

}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) { // heap delete
    
    if(!root) return;

    delete root->getBookData(); // deallocation
    LoanBookData *tmp = pN->getBookData();

    if(pN != root) {
       

        root->setBookData(tmp);

        // delete min element

        if (pN->getParent()->getLeftChild() == pN)
            pN->getParent()->setLeftChild(nullptr);
        else
            pN->getParent()->setRightChild(nullptr);

        pN->setParent(nullptr);

        delete pN;
        pN = nullptr;
    }

    else { // remove last element from heap
        delete root;
        root = nullptr;
        return;
    }



    // trickle down
    LoanBookHeapNode* cur = root, *child = root->getLeftChild(); // root & a child of currentNode
    
    while (child) {

        LoanBookHeapNode* Rchild = cur->getRightChild();

        // set child to larger child of currentNode
        if (Rchild) {
            if (Rchild->getBookData()->getName() < child->getBookData()->getName()) child = Rchild;
        }

        // can we put lastE in currentNode?
        if (tmp->getName() <= child->getBookData()->getName()) break; // yes

        // no
        cur->setBookData(child->getBookData()); // move child up
        cur = child;                            // move down a level
        child = child->getLeftChild();         
    }
    
    cur->setBookData(tmp);

}

bool LoanBookHeap::Insert(LoanBookData* data) { // insert the data

    if (!root) {
        root = new LoanBookHeapNode();
        root->setBookData(data);
        size = 1;
        return true;
    }

    else {

        LoanBookHeapNode* ptr = root, * prev = nullptr;

        int level = floor(log2(++size));

        string str;

        int cnt = size;

        // find the location of lastE(last element)
        for(int i=0; i<=level; i++) {
            str.push_back(cnt % 2 + '0');
            cnt /= 2;
        }

        str.pop_back();

        int length = str.length() - 1;

        while (length >= 0) {
            prev = ptr;
            if (str[length--] == '0') {
                ptr = ptr->getLeftChild();
            }
            else {
                ptr = ptr->getRightChild();
            }
        }
        

        LoanBookHeapNode* lastE = new LoanBookHeapNode();

        if (str[0] == '0') prev->setLeftChild(lastE);
        else prev->setRightChild(lastE);

        lastE->setParent(prev);
        lastE->setBookData(data);
        heapifyUp(lastE);

    }
    

    return false;
}

void LoanBookHeap::Delete() { // delete the data
    LoanBookHeapNode* ptr = root;

    if (!root) return;

    int level = floor(log2(size));

    string str;

    int cnt = size--;

    for (int i = 0; i <= level; i++) {
        str.push_back(cnt % 2 + '0');
        cnt /= 2;
    }

    str.pop_back();

    int length = str.length() - 1;

    // find the location of lastE(last element)
    while (length >= 0) {
        if (str[length--] == '0') {
            ptr = ptr->getLeftChild();
        }
        else {
            ptr = ptr->getRightChild();
        }
    }

    heapifyDown(ptr); // rearrange
    ptr = nullptr;
}

// void LoanBookHeap::DELETE_HEAP_NODES(LoanBookHeapNode* ptr) {
//    if(!ptr) return;

//    DELETE_HEAP_NODES(ptr->getLeftChild());
//    DELETE_HEAP_NODES(ptr->getRightChild());
//    delete ptr;
//    ptr = nullptr;
// }
