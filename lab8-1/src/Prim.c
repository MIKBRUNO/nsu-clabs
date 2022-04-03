#include <stdlib.h>
#include <string.h>
#include "Prim.h"

#define INNER  0
#define OUTER  1

static void freePtrArr(void** parr, size_t count) {
	if (NULL == parr)
		return;
	for (size_t i = 0; i < count; ++i)
		if (NULL != parr[i])
			free(parr[i]);
}

int minSpanningTree(int* adjm, unsigned short* res, size_t vcount) {
	if (0 == vcount)
		return -1;

	Edge** outEdges = malloc(vcount * sizeof(Edge*));
	if (NULL == outEdges)
		return -1;
	memset(outEdges, 0, vcount * sizeof(Edge*));

	unsigned int oecount = 0;
	size_t minV = 0;
	for (size_t v = 0; v < vcount; ++v) {
		if (-1 != adjm[v]) {
			outEdges[v] = malloc(sizeof(Edge));
			if (NULL == outEdges[v]) {
				freePtrArr(outEdges, vcount);
				free(outEdges);
				return -1;
			}
			outEdges[v]->v[1] = v;
			outEdges[v]->weight = adjm[v];
			outEdges[v]->v[0] = 0;
			++oecount;

			if (1 == oecount || outEdges[v]->weight < outEdges[minV]->weight)
				minV = v;
		}
	}
	
	unsigned char* mark = malloc(vcount);
	if (NULL == mark) {
		freePtrArr(outEdges, vcount);
		free(outEdges);
		return -1;
	}
	memset(mark, OUTER, vcount);
	mark[0] = INNER;

	size_t resi = 0;
	while (0 != oecount) {
		res[resi] = (int)outEdges[minV]->v[0];
		res[resi + 1] = (int)outEdges[minV]->v[1];
		resi += 2;
		outEdges[minV] = NULL;
		mark[minV] = INNER;
		--oecount;

		for (size_t v = 0; v < vcount; ++v) {
			if (mark[v] == OUTER && -1 != adjm[minV * vcount + v]) {
				if (NULL == outEdges[v]) {
					outEdges[v] = malloc(sizeof(Edge));
					if (NULL == outEdges[v]) {
						freePtrArr(outEdges, vcount);
						free(outEdges);
						free(mark);
						return -1;
					}
					outEdges[v]->v[1] = v;
					++oecount;
				}
				if (outEdges[v]->weight <= adjm[minV * vcount + v])
					continue;

				outEdges[v]->weight = adjm[minV * vcount + v];
				outEdges[v]->v[0] = minV;
			}
		}

		for (size_t v = 0; v < vcount; ++v)
			if (NULL != outEdges[v] &&
				(INNER == mark[minV] || outEdges[minV]->weight > outEdges[v]->weight))
					minV = v;
	}


	freePtrArr(outEdges, vcount);
	free((void*)outEdges);

	for (size_t v = 0; v < vcount; ++v)
		if (OUTER == mark[v]) {
			free(mark);
			return -1;
		}
	free(mark);
	return resi;
}
