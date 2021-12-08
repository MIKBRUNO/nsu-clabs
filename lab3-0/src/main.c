#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "HeapSort.h"

int readInt(char* buf, FILE* stream) {
	int c = fgetc(stream);
	size_t i = 0;
	while ((c != ' ') && (c != '\n') && (c != EOF)) {
		buf[i] = (char)c;
		c = fgetc(stream);
		++i;
	}
	buf[i] = 0;
	return atoi(buf);
}

int main(void) {
	char buf[12];
	if (!fgets(buf, 12, stdin))
		return EXIT_SUCCESS;
	size_t N = atoi(buf);
	
	int* arr;
	if (NULL == (arr = malloc(sizeof(int) * N))) {
		exit(EXIT_SUCCESS);
	}
	for (size_t i = 0; i < N; ++i) {
		arr[i] = readInt(buf, stdin);
	}

	heapSort(arr, N);
	for (size_t i = 0; i < N; ++i) {
		printf("%d ", arr[i]);
	}

	free(arr);

	return EXIT_SUCCESS;
}
