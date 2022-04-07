#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prim.h"

#define INNER  0
#define OUTER  1

static void freePtrArr(Edge** parr, size_t count) {
	if (NULL == parr)
		return;
	
}

int minSpanningTree(int* adjm, FILE* res, size_t vcount) {
	if (0 == vcount)
		return -1;

	Edge** outEdges = malloc(vcount * sizeof(Edge*));
	if (NULL == outEdges) {
		puts("cant allocate");
		return -1;
	}
	memset(outEdges, 0, vcount * sizeof(Edge*));

	unsigned int oecount = 0;
	for (unsigned short v = 1; v < vcount; ++v) {
		if (-1 != adjm[v]) {
			outEdges[v] = malloc(sizeof(Edge));
			if (NULL == outEdges[v]) {
				puts("cant allocate");
				freePtrArr(outEdges, vcount);
				free(outEdges);
				return -1;
			}
			outEdges[v]->v[0] = 0;
			outEdges[v]->v[1] = v;
			outEdges[v]->weight = adjm[v];
			++oecount;
		}
	}
	
	unsigned char* mark = malloc(vcount);
	if (NULL == mark) {
		puts("cant allocate");
		freePtrArr(outEdges, vcount);
		free(outEdges);
		return -1;
	}
	memset(mark, OUTER, vcount);
	mark[0] = INNER;

	size_t resi = 0;
	unsigned short minV = 0;
	while (0 != oecount) {
		for (unsigned short v = 0; v < vcount; ++v)
			if (NULL != outEdges[v] &&
				(INNER == mark[minV] || outEdges[minV]->weight > outEdges[v]->weight))
				minV = v;

		fprintf(res, "%u %u\n", (unsigned int)outEdges[minV]->v[0] + 1, (unsigned int)outEdges[minV]->v[1] + 1);
		resi += 1;
		free(outEdges[minV]);
		outEdges[minV] = NULL;
		mark[minV] = INNER;
		--oecount;

		for (unsigned short v = 0; v < vcount; ++v) {
			if (-1 != adjm[minV * vcount + v] && OUTER == mark[v]) {
				if (NULL == outEdges[v]) {
					outEdges[v] = malloc(sizeof(Edge));
					if (NULL == outEdges[v]) {
						puts("cant allocate");
						freePtrArr(outEdges, vcount);
						free(outEdges);
						return -1;
					}
					outEdges[v]->v[1] = v;
					++oecount;
				}
				else if (outEdges[v]->weight <= (unsigned int)adjm[minV * vcount + v])
					continue;
				outEdges[v]->v[0] = minV;
				outEdges[v]->weight = adjm[minV * vcount + v];
			}
		}
	}

	freePtrArr(outEdges, vcount);
	free(outEdges);

	for (size_t v = 0; v < vcount; ++v)
		if (OUTER == mark[v]) {
			free(mark);
			return -1;
		}
	free(mark);
	return resi;
}
