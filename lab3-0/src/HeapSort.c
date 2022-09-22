#include <stdlib.h>

static inline void mySwap(int* a, int* b) {
	*a += *b;
	*b = *a - *b;
	*a = *a - *b;
}

static void restoreHeapAtRoot(int* heap, size_t heapSize, size_t rootIdx) { // will return idx to updated leaf or to root
	while ((rootIdx < heapSize) && (rootIdx * 2 + 1 < heapSize)) {
		if (rootIdx * 2 + 2 >= heapSize) {
			if (heap[rootIdx] < heap[rootIdx * 2 + 1])
				mySwap(heap + rootIdx, heap + rootIdx * 2 + 1);
			return;
		}
		if ((heap[rootIdx * 2 + 1] >= heap[rootIdx * 2 + 2]) && (heap[rootIdx * 2 + 1] > heap[rootIdx])) {
			mySwap(heap + rootIdx * 2 + 1, heap + rootIdx);
			rootIdx = rootIdx * 2 + 1;
		}
		else if ((heap[rootIdx * 2 + 2] > heap[rootIdx * 2 + 1]) && (heap[rootIdx * 2 + 2] > heap[rootIdx])) {
			mySwap(heap + rootIdx * 2 + 2, heap + rootIdx);
			rootIdx = rootIdx * 2 + 2;
		}
		else
			return;
	}
}

void heapSort(int* arr, size_t size) {
	for (int i = (int)size / 2 - 1; 0 <= i; --i) {
		restoreHeapAtRoot(arr, size, (size_t)i);
	}

	for (size_t i = 1; i < size; ++i) {
		mySwap(arr, arr + size - i);
		restoreHeapAtRoot(arr, size - i, 0);
	}
}
