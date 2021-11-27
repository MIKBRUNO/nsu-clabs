#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dijkstra.h"

int main(void) {
	char perm[MAX_P_LEN];
	if (!fgets(perm, MAX_P_LEN, stdin))
		return EXIT_SUCCESS;
	size_t len = strlen(perm) - 1;
	perm[len] = 0;
	
	char buf[12];
	if (!fgets(buf, 12, stdin))
		return EXIT_SUCCESS;
	unsigned int N = atoi(buf);

	printNNextPermutation(perm, len, N);

	return EXIT_SUCCESS;
}