#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;

   // SelectionTreeNode* Run[8] = {nullptr};

public:
    SelectionTree(ofstream* fout) {
        this->root = nullptr;
        this->fout = fout; 
    }
    ~SelectionTree() {
        Delete_selection_tree();
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    void INIT();

    void Delete_selection_tree();
    void Delete_post(SelectionTreeNode* ptr);
};