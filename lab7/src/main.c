#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TopSort.h"

int main(void) {
	char buf[11];
	int N = 0,
		M = 0;
	if (NULL == fgets(buf, 6, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	N = atoi(buf);

	if (NULL == fgets(buf, 9, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	M = atoi(buf);
	if (N > 2000 || N < 0) {
		fputs("bad number of vertices", stdout);
		return 0;
	}
	if (M > N * (N - 1) / 2 || N < 0) {
		fputs("bad number of edges", stdout);
		return 0;
	}

	AdjTable at;
	at.size = N;

	unsigned int* enter = malloc(N * sizeof(unsigned int));
	if (NULL == enter)
		return 0;
	memset(enter, 0, N * sizeof(unsigned int));
	at.enterCount = enter;

	unsigned char* passed = malloc(N * sizeof(unsigned char));
	if (NULL == passed)
		return 0;
	memset(passed, 0, N * sizeof(unsigned char));
	at.passed = passed;
	
	size_t byteSize;
	byteSize = (N * N / 8) + (0 != N % 8);
	unsigned char* table = malloc(byteSize * sizeof(unsigned char));
	if (NULL == table)
		return 0;
	memset(table, 0, byteSize * sizeof(unsigned char));
	at.table = table;

	for (size_t i = 0; i < (size_t)M; ++i) {
		int a,
			b;
		if (NULL == fgets(buf, 11, stdin)) {
			puts("bad number of lines");
			free(table);
			free(enter);
			free(passed);
			return 0;
		}
		a = atoi(buf);
		b = atoi(strchr(buf, ' ') + 1);
		if (a < 1 || a > N || b < 1 || b > N) {
			puts("bad vertex");
			free(table);
			free(enter);
			free(passed);
			return 0;
		}
		writeEdge(&at, (unsigned int)a - 1, (unsigned int)b - 1);
	}
#if 0
	char buffer[9216];
	memset(buffer, 0, 9216);
	if (1 == topSortAT(&at, buffer))
		puts(buffer);
#else
	unsigned int buffer[2000];
	memset(buffer, 0, 2000 * sizeof(unsigned int));
	if (1 == topSortAT(&at, buffer))
		for (size_t i = 0; i < (unsigned int)N; ++i) {
			printf("%d ", buffer[i]);
		}
#endif
	free(table);
	free(enter);
	free(passed);

	return 0;
}
