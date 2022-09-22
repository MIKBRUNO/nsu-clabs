#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Dijkstra.h"

#define VISITED		1
#define NOT_VISITED	0

static int sum(int a, int b) {
	if (INF == a || INF == b)
		return INF;
	if (OVER_INT_MAX == a || OVER_INT_MAX == b)
		return OVER_INT_MAX;
	else if (INT_MAX - a < b)
		return OVER_INT_MAX;
	else
		return a + b;
}

static int cmp(int a, int b) {
	if (INF == a || OVER_INT_MAX == a)
		return 1;
	else if (INF == b || OVER_INT_MAX == b)
		return -1;
	else
		return a - b;
}

int shortestPath_Dijkstra(int* adjm, int* shortestPaths, unsigned short* prevNodeTable,
					unsigned int st, unsigned int fin,
					unsigned int vcount) {
	unsigned char* mark = malloc(vcount);
	if (NULL == mark) {
		puts("cant allocate");
		return ERR;
	}
	memset(mark, NOT_VISITED, vcount);

	unsigned int altExist = 0;

	unsigned int curV = st;
	shortestPaths[curV] = 0;
	prevNodeTable[curV] = curV;
	while (NOT_VISITED == mark[curV]) {
		mark[curV] = VISITED;

		unsigned int altPathCount = 0;
		for (unsigned int v = 0; v < vcount; ++v)
			if (-1 != adjm[curV * vcount + v]) {
				if (NOT_VISITED == mark[v]) {
					int altPath = sum(shortestPaths[curV], adjm[curV * vcount + v]);
					if (cmp(shortestPaths[v], altPath) > 0) {
						prevNodeTable[v] = curV;
						shortestPaths[v] = altPath;
					}
				}
				else if (curV != v)
					altPathCount += 1;
			}
		if (1 < altPathCount)
			altExist = 1;

		for (unsigned int v = 0; v < vcount; ++v)
			if (NOT_VISITED == mark[v] && INF != shortestPaths[v] &&
				(VISITED == mark[curV] || cmp(shortestPaths[v], shortestPaths[curV]) < 0)) {
				curV = v;
			}
	}

	free(mark);
	if (OVER_INT_MAX == shortestPaths[fin] && altExist) {
		return OVERFLOW;
	}
	return 0;

}
