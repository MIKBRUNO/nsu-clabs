#include <stdio.h>
#include <stdlib.h>

void assert(unsigned cond) {
	if (!cond) {
		puts("bad input");
		exit(0);
	}
}
