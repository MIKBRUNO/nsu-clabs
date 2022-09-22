#pragma once
#include <stdlib.h>

typedef struct Stack_s Stack;
struct Stack_s {
	int* first;
	size_t size;
};

extern void push(Stack* stack, int val);
extern int pop(Stack* stack);
extern int head(Stack* stack);
extern int isEmpty(Stack* stack);
