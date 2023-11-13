#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <cmath>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    int size;

public:
    LoanBookHeap() {
        this->root = nullptr;
        size = 0;
    };
    ~LoanBookHeap() {
       //DELETE_HEAP_NODES(root);
    }
    
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
    void Delete();
    
    //void DELETE_HEAP_NODES(LoanBookHeapNode* ptr);

};