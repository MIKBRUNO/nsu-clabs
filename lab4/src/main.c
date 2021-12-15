#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RPNCalc.h"

int main(void) {
	char buf[BUF_SIZE],
		 rpn[BUF_SIZE*2];
	size_t size = fread(buf, 1, BUF_SIZE, stdin) - 1;
	buf[size] = 0;

	createRPN(buf, rpn, size);
	size = strlen(rpn);
	if (0 >= size) {
		fputs("syntax error", stdout);
		exit(0);
	}
	int res = evalRPN(rpn, size);
	printf("%d", res);

	return EXIT_SUCCESS;
}
