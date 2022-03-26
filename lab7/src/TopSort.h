#pragma once
#include <stdlib.h>

#define PASSED 1
#define NOT_PASSED 0

typedef struct AdjTable_st AdjTable;
struct AdjTable_st {
	unsigned char* table;
	unsigned int* enterCount;
	unsigned int* passed;
	size_t size;
};

void writeEdge(AdjTable* at, unsigned int frm, unsigned int to);
int topSortAT(AdjTable* at, char* buffer);
