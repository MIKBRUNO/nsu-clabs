#pragma once
#include <stdlib.h>

typedef struct Edge_st Edge;
struct Edge_st {
	unsigned short v[2];
	unsigned int weight;
};

int minSpanningTree(int* adjm, unsigned short* res, size_t vcount);
