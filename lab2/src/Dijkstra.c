#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Dijkstra.h"

static size_t findSuffix(const char* perm, size_t size) {
	size_t i = size - 1;
	while (i > 0) {
		if (perm[i] > perm[i - 1]) {
			return i;
		}
		--i;
	}
	return 0;
}

static size_t findSup(char* arr, size_t size, int value) {
	size_t res = 0;
	for (size_t i = 0; i < size; ++i)
		if ((arr[i] > value) && (arr[i] < arr[res]))
			res = i;
	return res;
}

static inline void swap(char* dst, char* src) {
	*dst += *src;
	*src = *dst - *src;
	*dst -= *src;
}

static void reverse(char* str, size_t len) {
	for (size_t i = 0; i < len / 2; ++i)
		swap(str + i, str + len - i - 1);
}

int D_NextPermutation(char* perm, size_t size) {
	size_t suffix = findSuffix(perm, size);
	if (suffix == 0)
		return 0;
	size_t sup = findSup(perm + suffix, size - suffix, perm[suffix - 1]);
	swap(perm + suffix - 1, perm + suffix + sup);
	reverse(perm + suffix, size - suffix);
	return 1;
}

void printNNextPermutation(const char* perm, size_t size, unsigned int N) {
	size_t uniq = 0;
	for (size_t i = 0; i < size; ++i) {
		if (!isdigit(perm[i]) ||
			(uniq & (1 << (perm[i] - '0')))
			) {
			fputs("bad input", stdout);
			exit(EXIT_SUCCESS);
		}
		uniq += 1 << (perm[i] - '0');
	}
	char tmpP[MAX_P_LEN];
	strcpy(tmpP, perm);

	for (unsigned int i = 0; (i < N) && (D_NextPermutation(tmpP, size)); ++i) {
		fputs(tmpP, stdout);
		fputs("\n", stdout);
	}
}
