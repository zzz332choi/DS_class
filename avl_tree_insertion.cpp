#include <iostream>

template <class K, class E> class AVL;

template<class K, class E>
class AvlNode{
	friend class AVL<K, E>;

public:
	AvlNode(const K& k, const E& e) {
		key = k; element = e; bf = 0; leftChild = rightChild = NULL;
	}

private:
	K key;
	E element;
	int vf;
	AvlNode<K, E>* leftChild, * rightChild;
};

template <class K, class E>
class AVL {
public:
	AVL() : root(NULL) {};
	void Insert(const K&, const E&);

private:
	AvlNode<K, E>* root;
};

template<class K, class E>
void AVL<K, E>::Insert(const K&, const E&)
{
	if (root == NULL) { // special case: empty tree
		root = new AvlNode<K, E>(k, e);
		return;
	}

	// Phase1: Locate insertion point for e
	AvlNode<K, E>* a = root,	// most recent node with bf +- 1 // 불균형이 발생할 가능성이 높은 아이
				* pa = NULL,	// parent of a
				* p = root,	// p moves through the tree
				* pp = NULL,	// parent of p
				* rootSub = NULL;

	while (p != NULL) {									// 캐치 하고 leaf node에 밑까지 탐색해서 pp가 결국 leaf node를 가지게 됨
		if (p->bf != 0) { a = p; pa = pp; }				// 군형이 무너질 수 있는 애 부터 캐치 
		if (k < p->key) { pp = p; p = p->leftChild; }	// take left branch
		else if (k > p->key) { pp = p; p = p->right; }	// tack right branch
		else { p->element = e; return; } // k is aleady in tree. update e
	}	// end of while

	
	// 새로 들어오는 애 추가 : y
	// Phase2: insert and rebalance. k is not in the tree and
	// may be inserted as the appropriate child of pp
	AvlNode<K, E>* y = new AvlNode<K, E>(k, e);
	if (k < pp->key) pp->leftChild = y; // insert as left child
	else pp->rightChild = y;			// insert as right child

	// Adjust balance factors of nodes on path from a to pp. By the defnition
	// of a, all nodes on this path presently have a balane factor of 0. Their new
	// balance factor will be +-1. d = +1 implies that k is inserted in the left subtree
	// of a. d= -1 implies that k is inserted in the right subtree of a.

	// d가 +1 이면 왼쪽 서브트리에 추가된 것. d가 -1 이면 오른쪽 서브트리로 추가된 것.

	int d;
	AvlNode<K, E>* b, // child of a
				 * c;	// child of b

	if (k > a->key) { b = p = a->rightChild; d = -1; }
	else { b = p = a->leftChild; d = 1; }

	while (p != y) {
		if (k > p->key) { // height of right increases by 1
			p->bf = -1; p = p->rightChild; // 오른쪽에 추가된 것이니 모든 경로에서 balance factors -1 감소
		}
		else {			// hight of left increases by 1
			p->bf = 1; p = p->leftChild;  // 왼쪽에 추가된 것이니 모든 경로에서 balance factors 1
		}
	}

	// Is tree unbalanced?
	if (a->bf == 0 || a->bf + d == 0) { // tree still balanced
		a->bf += d; return;
	}

	// tree unbalanced, determine rotiaion type
	if (d == 1) { // left imbalance
		if (b->bf == 1) { // rotation type LL
			a->leftChild = b->rightChild;
			b->rightChild = a; a->bf = 0; b->bf = 0;
			rootSub = b; // b is the new root of the subtree
		}
		else { // rotation type LR
			c = b->rightChild;
			b->rightChild = c->leftChild;
			a->leftChild = c->rightChild;
			c->leftChild = b;
			c->rightChild = a;
			switch (c->bf) {
			case 0:	// node c가 balance한 경우					
				b->bf = 0; a->bf = 0;
				break;
			case 1:	// node c의 left subtree의 높이가 더 큼(왼쪽으로 자식 들어옴)
				a->bf = -1; b->bf = 0;
				break;
			case -1: // node c의 right subtree의 높이가 더 큼(오른쪽으로 자식 들어옴)
				b->bf = 1; a->bf = 0;
				break;
			}
			c->bf = 0; rootSub = c; // c is the new root of the subree
		} // end of LR
	}	//end of left imbalance

	else { // right imbalance: this is symmetric to left imbalance
		if (b->bf == -1) {	// rotation type RR
			a->rightChild = b->leftChild;
			b->leftChild = a; a->bf = 0; b->bf = 0;
			rootSub = b; // b is the new root of the subtree
		}
		else { // rotation type RL
			c = b->leftChild;
			b->leftChild = c->rightChild;
			a->rightChild = c->leftChild;
			c->rightChild = b;
			c->leftChild = a;
			switch (c->bf) {
			case 0: // node c가 balance한 경우
				b->bf = 0; a->bf = 0;
				break;
			case 1: // node c의 left subtree의 높이가 더 큼
				b->bf = -1; a->bf = 0;
				break;
			case -1: // node c의 right subree의 높이가 더 큼
				a->bf = 1; b->bf = 0;
				break;
			}
			c->bf = 0; rootSub = c; // c is the new root of the subree
		} // end of RL

	}

	// Subtree whit root b has been rebalanced
	if (pa == NULL) root = rootSub;
	else if (a == pa->leftChild) pa->leftChild = rootSub;
	else pa->rightChild = rootSub;
	return;

} // end of AVL::insert
