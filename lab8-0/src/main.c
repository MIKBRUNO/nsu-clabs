#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Kruskal.h"

#define BUFSIZE 1024

static int cmpEdges(const void* a, const void* b) {
	return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int main(void) {
	char buf[BUFSIZE];
	
	if (NULL == fgets(buf, BUFSIZE, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int N = atoi(buf);
	if (5000 < N) {
		puts("bad number of vertices");
		return 0;
	}

	if (NULL == fgets(buf, BUFSIZE, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int M = atoi(buf);
	if (M > N * (N - 1) / 2) {
		puts("bad number of edges");
		return 0;
	}

	Edge* edges = malloc(M * sizeof(Edge));
	if (NULL == edges)
		return 0;
	memset(edges, 0, M * sizeof(Edge));
	for (size_t i = 0; i < M; ++i) {
		if (NULL == fgets(buf, BUFSIZE, stdin)) {
			puts("bad number of lines");
			free(edges);
			return 0;
		}
		char* b1 = strchr(buf, ' ') + 1,
			* b2 = strchr(b1, ' ') + 1;
		if (NULL == b1 || NULL == b2) {
			puts("bad number of lines");
			free(edges);
			return 0;
		}
		edges[i].v[0] = (unsigned short)atoi(buf) - 1;
		if (N - 1 < edges[i].v[0]) {
			puts("bad vertex");
			free(edges);
			return 0;
		}
		edges[i].v[1] = (unsigned short)atoi(b1) - 1;
		if (N - 1 < edges[i].v[1]) {
			puts("bad vertex");
			free(edges);
			return 0;
		}
		edges[i].weight = atoi(b2);
		if (0 > edges[i].weight || strlen(b2) > 11 || (strlen(b2) == 11 && strcmp("2147483647\n", b2) < 0)) {
			puts("bad length");
			free(edges);
			return 0;
		}
	}

	qsort(edges, M, sizeof(Edge), cmpEdges);

	unsigned short* colors = malloc(N * sizeof(unsigned short));
	if (NULL == colors) {
		free(edges);
		return 0;
	}
	for (size_t i = 0; i < N; ++i)
		colors[i] = (unsigned short)i;

	unsigned short* res = malloc(sizeof(unsigned short) * M * 2);
	if (NULL == res) {
		free(edges);
		free(colors);
		return 0;
	}
	memset(res, 0, sizeof(unsigned short) * M * 2);

	int resCount = minSpanningTree(edges, M, colors, N, res);
	if (-1 != resCount)
		for (size_t i = 0; i < (size_t)resCount; i += 2)
			printf("%u %u\n", res[i] + 1, res[i + 1] + 1);
	else
		puts("no spanning tree");

	free(edges);
	free(colors);
	return 0;
}
