#pragma once
#include <stdlib.h>

typedef struct Node_s Node;
struct Node_s {
	Node* link[2];
	size_t height;
	int value;
};

size_t height(Node* elem);
Node* insert(Node* elem, Node* tree);
