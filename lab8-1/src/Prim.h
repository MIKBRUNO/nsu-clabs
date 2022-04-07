#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct Edge_st Edge;
struct Edge_st {
	unsigned short v[2];
	unsigned int weight;
};

int minSpanningTree(int* adjm, FILE* res, size_t vcount);
