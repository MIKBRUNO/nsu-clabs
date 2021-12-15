#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "RPNCalc.h"
#include "Stack.h"

#define syntaxErr() { fputs("syntax error", stdout); exit(EXIT_SUCCESS); }

static inline int isop1(int c) {
	return ((c == '+') || (c == '-'));
}

static inline int isop2(int c) {
	return ((c == '*') || (c == '/'));
}

static inline int eval(int a, int b, int action) {
	if (action == '+')
		return a + b;
	else if (action == '-')
		return a - b;
	else if (action == '*')
		return a * b;
	else if (action == '/')
		if (b != 0) {
			return a / b;
		}
		else {
			fputs("division by zero", stdout);
			exit(EXIT_SUCCESS);
		}
	else
		syntaxErr();
}

#if 0
static inline void syntaxErr() {
	fputs("syntax error", stdout);
	exit(EXIT_SUCCESS);
}
#endif

void createRPN(char* src, char* dst, size_t size) {
	int stack[BUF_SIZE]; stack[0] = 0;
	Stack op = { stack, 0 };
	size_t di = 0;
	for (size_t i = 0; i < size; ++i) {
		if (isdigit(src[i])) {
			dst[di++] = src[i];
		}
		else if (isop1(src[i]) || isop2(src[i])) {
			dst[di++] = SEP;
			if (
				!isEmpty(&op) &&
				(head(&op) != '(') &&
				(isop2(head(&op)) || isop1(src[i]))  // op1 pops any op, op2 pops only op2's | op2 has greater priority
				)
			{
				dst[di++] = (char)pop(&op);
				dst[di++] = SEP;
			}
			push(&op, src[i]);
		}
		else if (src[i] == '(') {
			push(&op, '(');
			if ((i == size - 1) ||
				(src[i + 1] == ')') ||
				(
					(i != 0) &&
					!(isop1(src[i - 1]) || isop2(src[i - 1]) || (src[i-1] == '('))
				))
			{
				syntaxErr();
			}
		}
		else if (src[i] == ')') {
			if (isEmpty(&op)) {
				syntaxErr();
			}
			int c = pop(&op);
			while (!isEmpty(&op) && (c != '(')) {
				dst[di++] = SEP;
				dst[di++] = (char)c;
				c = pop(&op);
			}
			if ('(' != c) {
				syntaxErr();
			}
		}
		else {
			syntaxErr();
		}
	}
	while (!isEmpty(&op)) {
		dst[di++] = SEP;
		int c = pop(&op);
		dst[di++] = (char)c;
		if ('(' == c) {
			syntaxErr();
		}
	}
	dst[di] = 0;
}

int evalRPN(char* rpn, size_t size) {
	int arr[BUF_SIZE]; arr[0] = 0;
	Stack stack = { arr, 0 };
	size_t i = 0;
	while (i < size) {
		if (isdigit(rpn[i])) {
			char buf[16];
			size_t j = 0;
			while ((rpn[i] != ',') && (rpn[i] != 0)) {
				buf[j++] = rpn[i++];
			}
			buf[j] = 0;
			++i;																// skipping SEP
			push(&stack, atoi(buf));
		}
		else {
			if (stack.size > 1) {
				int a = eval(pop(&stack), pop(&stack), rpn[i]);
				push(&stack, a);
				i += 2;
			}
			else {
				syntaxErr();
			}

		}
	}
	int res = pop(&stack);
	if (!isEmpty(&stack))
		return 1;
	return res;
}
