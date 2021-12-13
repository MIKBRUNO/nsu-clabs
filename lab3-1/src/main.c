#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QuickSort.h"

int main(void) {
	unsigned int n;
	if (!scanf("%ud", &n)) {
		exit(EXIT_SUCCESS);
	}

	int* arr;
	if (NULL == (arr = malloc(sizeof(int) * n)))
		exit(EXIT_SUCCESS);
	for (size_t i = 0; i < n; ++i) {
		if (!scanf("%d", arr + i)) {
			exit(EXIT_SUCCESS);
		}
	}

	quickSort(arr, n);
	for (size_t i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}

	return EXIT_SUCCESS;
}
