#include <iostream>

#define TreeSize 20

typedef struct Element {
// whatever data
	int key;
};

class Winner {
public:
	Winner(Element*, int);
private:
	int* winner; // stores only k-1 internal nodes
	int k; // size of winner
};

Winner::Winner(Element* R, int sz = TreeSize) // min winner tree
{
	k = sz;
	winner = new int[k]; // Don't want to use winner[0]
	for (int i = 1; i < k; i++) winner[i] = -1; // initial -1

	int j = k;
	for (int i = k - 1; i >= k / 2 && j != -1; i--) { // 작은게 이기는 거임
		// Play a tournament at each leaf of the tree
		if (R[j].key > R[j - 1].key) winner[i] = j - 1;
		else winner[i] = j;
		j -= 2; // 두 칸씩 건너 뛴다. 
	}

	if (j == 1) { // k가 홀수 // 부전승의 개념 이용 일단 R1만 남는데 이미 이겼다고 보고 그의 왼쪽 자노드(즉, leaf node중 k-1과 k 중 이긴 element와 대결
		// The tree contains a node which has one child
		// Play a tournamet at this node
		winner[k / 2] = 1;
		int challenger = winner[k / 2 * 2]; // leaf node중 k-1th or kth 이긴 애가 위치한 곳: k/2 th node의 왼쪽 자노드
		if (R[challenger].key < R[1].key) winner[k / 2] = challenger; // R1을 이긴 취급했다가 왼쪽 자노드가 더 작은 애였던거임(그 자노드가 winner임)
	}

	for (int i = k / 2 - 1; i >= 1; i--) { // 하위 k/2개는 다 insert함. 이제 남은 상위에 대해서 하며 배열의 0 칸은 비워놓는다.
		// Play a tournament at each internal node of the tree starting
		// from the bottom adn moving towards the root
		j = 2 * i;
		if (R[winner[j]].key > R[winner[j + 1]].key) winner[i] = winner[j + 1]; // 오른쪽 자노드가 이긴 경우
		else winner[i] = winner[j];												// 왼쪽 자노드가 이긴 경우
	}
}
