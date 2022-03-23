#pragma once
#include <stdio.h>

#define BUFSIZE 4096  // >= 320

typedef struct Node_st Node;
struct Node_st {
	Node* link[2];

	unsigned char value;
	unsigned int freq;
};

void encode(FILE* out, FILE* in,  int arg);

void decode(FILE* out, FILE* in, int arg);
