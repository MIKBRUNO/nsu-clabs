#include "Stack.h"

inline void push(Stack* stack, int val) {
	stack->first[stack->size] = val;
	++(stack->size);
}

inline int pop(Stack* stack) {
	--(stack->size);
	return stack->first[stack->size];
}

inline int head(Stack* stack) {
	return stack->first[stack->size - 1];
}

inline int isEmpty(Stack* stack) {
	return ((stack->size) == 0);
}
