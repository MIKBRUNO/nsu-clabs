#pragma once
#include <stdlib.h>

typedef struct Stack_s Stack;
struct Stack_s {
	int* first;
	size_t size;
};

extern inline void push(Stack* stack, int val);
extern inline int pop(Stack* stack);
extern inline int head(Stack* stack);
extern inline int isEmpty(Stack* stack);
