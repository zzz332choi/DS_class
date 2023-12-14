template <class T>
void Merge(T* initList, T* mergedList, const int l, const int m, const int n) {
	// initList[1:m] and initList[m+1:n] are sorted lists.
	// They are merged to obtain the sorted list mergedList[1:n]
	// i1, i2, and iResult are list positions.
	int i1, i2, iResult;
	for(i1 = 1, iResult = 1, i2 = m+1; 
		i1 <= m && i2 <= n; // neither input list is exhausted.
		iResult++)
		if (initList[i1] <= initList[i2]) {
			mergedList[iResult] = initList[i1];
			i1++;
		}
		else {
			mergedList[iResult] = initList[i2];
			i2++;
		}

	// copy remaining records, if any, of the first list
	copy(initList + i1, initList + m + 1, mergedList + iResult);

	// copy remaining records, if any, of the first list
	copy(initList + i2, initList + n + 1, mergedList + iResult);
}

template <class T> 
void MergePass(T* initList, T* resultList, const int n, const int s) {
	// Adjacent pairs of sublists of size s are merge from
	// ininList to resultList. n is the numver of records in iniList
	for (int i = 1; // i is first position in first of the sublists being merged
		i <= n - 2 * s + 1; // enough elements for two sublists of length s?
		i += 2 * s)
		Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);

	// merge remainng list of size <2*s
	if ((i + s - 1) < n) Merge(initList, resultList, i, i + s - 1, n);
	else copy(initList + i, initList + n + 1, resultList + i)
}

template <class T>
void MergeSort(T* a, const int n) {
	// sort a[1:n] into nondecreasing order.
	T* tempList = new T[n + 1];
	// l is the length of the sublist currently being merged
	for (int l = 1; l < n; l *= 2) {
		MergePass(a, tempList, n, 1);
		l *= 2;
		MergePass(tempList, a, n, 1); // interchange role of a and tempList
	}

	delete[] tempList;
}