#include <iostream>

#define TreeSize 20

typedef struct Element {
// whatever data
	int key;
};

class Loser {
public:
	Loser(Element*, int);
private:
	int* loser; // stores only k-1 internal nodes
	int k; // size of winner
};

Loser::Loser(Element *R, int sz = TreeSize)
{
	k = sz;
	int winner, l;
	loser = new int[k]; // loser[0] contains winner : 최종 winner를 저장
	for (int i = 0; i < k; i++) loser[i] = -1; // 일단 모두 -1로 초기화 하는 걸로

	int j = k;
	// Play a series of tournaments starting at the leaf, going up the
	// tree as long as an opponet is available
	for (int i = k - 1; i >= k / 2 && j != 1; i--) {
		// Play tournament at leaf
		if (R[j].key > R[j - 1].key) { // winner는 loser[]에 저장되는 것의 반대로
			loser[i] = j;
			winner = j - 1;
		}
		else {
			loser[i] = j - 1;
			winner = j;
		}

		j -= 2; // 두 칸 씩 옮기기 

		// Go up the tree
		l = i / 2;
		while (loser[l] != -1) {
			if (R[loser[l]].key < R[winner].key) {
				int temp = winner;
				winner = loser[l];
				loser[l] = temp;
			}
			l /= 2;
		}
		loser[l] = winner;
	}

	if (j == 1) {
		winner = 1; // R[1]이 이미 이겼다고 가정
		l = k / 2; // k/2의 상위만 훑어본다.
		
		while (loser[l] != -1) {
			if (R[loser[l]].key < R[winner].key) {
				int temp = winner;
				winner = loser[l];
				loser[l] = temp;
			}
			l /= 2;
		}

		loser[l] = winner;
	}
}
