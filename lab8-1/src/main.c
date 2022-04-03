#define READ_FILE
#ifdef READ_FILE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Prim.h"

#define BUFSIZE 1024

int main(void) {
	char buf[BUFSIZE];

	FILE* in = stdin;
#ifdef READ_FILE
	in = fopen("in.txt", "rt");
#endif

	if (NULL == fgets(buf, BUFSIZE, in)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int N = atoi(buf);
	if (5000 < N) {
		puts("bad number of vertices");
		return 0;
	}

	if (NULL == fgets(buf, BUFSIZE, in)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int M = atoi(buf);
	if (M > N * (N - 1) / 2) {
		puts("bad number of edges");
		return 0;
	}

	int* adjm = malloc(N * N * sizeof(int));
	if (NULL == adjm)
		return 0;
	for (size_t i = 0; i < N * N; ++i)
		adjm[i] = -1;

	for (size_t i = 0; i < M; ++i) {
		if (NULL == fgets(buf, BUFSIZE, in)) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		char* b1 = strchr(buf, ' ') + 1;
		if (NULL == b1) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		char* b2 = strchr(b1, ' ') + 1;
		if (NULL == b2) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		int v0 = atoi(buf);
		if ((int)N < v0 || 1 > v0) {
			puts("bad vertex");
			free(adjm);
			return 0;
		}
		v0 -= 1;
		int v1 = atoi(b1);
		if ((int)N < v1 || 1 > v1) {
			puts("bad vertex");
			free(adjm);
			return 0;
		}
		v1 -= 1;
		adjm[v0 * N + v1] = atoi(b2);
		if (0 > adjm[v0 * N + v1] ||
			strlen(b2) > 11 ||
			(strlen(b2) == 11 && strcmp("2147483647\n", b2) < 0) ){
			puts("bad length");
			free(adjm);
			return 0;
		}
		adjm[v1 * N + v0] = adjm[v0 * N + v1];
	}

	unsigned short* res = malloc(2 * M * sizeof(unsigned short));
	if (NULL == res) {
		free(adjm);
		return 0;
	}
	memset(res, 0, 2 * M * sizeof(unsigned short));

	int resc = minSpanningTree(adjm, res, N);
	if (-1 == resc)
		puts("no spanning tree");
	else
		for (size_t i = 0; i < (size_t)resc; i += 2)
			printf("%u %u\n", res[i] + 1, res[i + 1] + 1);

	free(adjm);
	free(res);
	return 0;
}
