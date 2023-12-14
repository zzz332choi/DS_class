#include <iostream>

// stable & in-place
// time complexiy : O(n^2)
// space complexity : O(1)

template <class T>
void InsertionSort(T* a, const int n) {
	// sort a [1:n] into nodecreasing order.
	for (int j = 2; j <= n; j++) {
		T temp = a[j];
		Insert(temp, a, j - 1);
	}
}

template <class T>
void Insert(const T& e, T* a, int i) {
	// Insert e into the ordered sequence a[1:i] such that the
	// resulting sequence a [1:i+1] is also ordered.
	// The array a must have space allocated for at least i + 2 elements.
	// The use of a[0] enables us to simplify the while loop,
	// avoding a test for end of list (i.e., i< 1)
	a[0] = e;
	while (e < a[i]) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}