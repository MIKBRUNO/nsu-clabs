#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dijkstra.h"

#define INNER  1
#define OUTER  0

static inline int calcPath(int path, int edge) {
	if (OVER_INT_MAX == path || INT_MAX - path < edge)
		return OVER_INT_MAX;
	else
		return path + edge;
}

int D_shortestPath(int* adjm, int* shortestPaths, unsigned short* prevNodeTable,
					unsigned int st, unsigned int fin,
					unsigned int vcount) {
	unsigned char* mark = malloc(vcount);
	if (NULL == mark) {
		puts("cant allocate");
		return ERR;
	}
	memset(mark, OUTER, vcount);

	unsigned int altExist = 0;

	unsigned int minV = st;
	shortestPaths[minV] = 0;
	prevNodeTable[minV] = minV;
	while (OUTER == mark[minV]) {
		mark[minV] = INNER;

		unsigned int altPathCount = 0;
		for (unsigned int v = 0; v < vcount; ++v)
			if (-1 != adjm[minV * vcount + v]) {
				if (OUTER == mark[v]) {
					int altPath = calcPath(shortestPaths[minV], adjm[minV * vcount + v]);
					if (INF == shortestPaths[v] || OVER_INT_MAX == shortestPaths[v]
						|| (OVER_INT_MAX != altPath && shortestPaths[v] > altPath))
					{
						prevNodeTable[v] = minV;
						shortestPaths[v] = altPath;
					}
				}
				else if (minV != v)
					altPathCount += 1;
			}
		if (1 < altPathCount)
			altExist = 1;

		for (unsigned int v = 0; v < vcount; ++v)
			if (OUTER == mark[v] && INF != shortestPaths[v] &&
				(INNER == mark[minV] || OVER_INT_MAX == shortestPaths[minV] ||
					(OVER_INT_MAX != shortestPaths[v] && shortestPaths[v] < shortestPaths[minV])
					)
				) {
				minV = v;
			}
	}

	if (OUTER == mark[fin]) {
		free(mark);
		return NOPATH;
	}
	free(mark);
	if (OVER_INT_MAX == shortestPaths[fin] && altExist) {
		return OVERFLOW;
	}
	return 0;

}
