#include <stdio.h>

void assert(unsigned cond) {
	if (!cond) {
		puts("bad input");
		exit(0);
	}
}