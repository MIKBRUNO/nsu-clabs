#pragma once
#include <stdlib.h>

typedef struct Node_s Node;
struct Node_s {
	Node* link[2];
	unsigned int height;
	int value;
};

unsigned int height(Node* elem);
Node* insert(Node* elem, Node* tree);
