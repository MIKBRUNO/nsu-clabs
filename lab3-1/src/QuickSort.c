#include <stdlib.h>

void quickSort(int* arr, size_t size) {
	while (1 < size) {
		size_t l = 0u,
			r = size - 1u;
		int m = (arr[r] + arr[l]) / 2;
		while (arr[l] < m)
			++l;
		while (arr[r] > m)
			--r;
		while (l < r) {
			if (arr[l] != arr[r]) {
				arr[l] += arr[r];
				arr[r] = arr[l] - arr[r];
				arr[l] -= arr[r];
			}
			--r;
			++l;
			while (arr[l] < m)
				++l;
			while (arr[r] > m)
				--r;
		}
		if (0 == size - r - 1)
			return;
		if (r + 1 < size - r - 1) {
			quickSort(arr, r + 1);
			arr += r + 1;
			size -= r + 1;
		}
		else {
			quickSort(arr + r + 1, size - r - 1);
			size = r + 1;
		}
	}
}
