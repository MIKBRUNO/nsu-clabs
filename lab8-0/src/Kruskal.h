#pragma once
#include <stdlib.h>

typedef struct Edge_st Edge;
struct Edge_st {
	int weight;
	unsigned short v[2];
};

int minSpanningTree(Edge* sortedEdges, size_t ecount,
							 unsigned short* colors, size_t vcount,
							 unsigned short* res);
