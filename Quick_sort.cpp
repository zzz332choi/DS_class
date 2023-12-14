#include <iostream>
#include <algorithm>

// in-place but not stable(= unstable)
// Timecomplexity: average	=> O(nlog n)
//				   worst	=> O(n^2)

// worst case happens whe the pibot is always the smallest element. 
// For the worst-case time, T(n) = n + T(n-1), n > 1 => T(n) = (n^2)/2 - 1 = O(n^2)
// For the best-case time, T(n) = n + 2T(n/2) => O(nlog n)
// For the average-case time, T(n) = n + T(i) + T(n - i - 1), n > 1

// space complexity : worts -> O(n), best & average -> O(log n)

template<class T>
void QuickSort(T* a, const int left, const int right) {
	// Sort a[left:right] into nondecreasing order
	// a[left] is arbitrarily chosen as the pivot.
	// Variables i and j are used to partition the subarray
	// so that at any time a[m] <= pivot, m < i
	// and a[m] >= pivot, m > j.
	// It is assumed that a[left] <= a[right + 1].

	if (left < right) {
		int i = left;
		int j = right + 1;
		int pivot = a[left];

		do {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j) swap(a[i], a[j]);
		} while (i < j);

		swap(pivot, a[j]);

		QuickSort(a, left, pivot - 1);
		QuickSort(a, pivot + 1, right);
	}
}