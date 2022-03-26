#include <stdio.h>
#include <string.h>
#include "TopSort.h"

void writeEdge(AdjTable* at, unsigned int frm, unsigned int to) {
	size_t i = frm * at->size + to;
	(at->table)[i / 8] |= 0x80 >> (i % 8);
	++(at->enterCount[to]);
}

static void deleteNode(AdjTable* at, unsigned int node) {
	size_t row = node * at->size;
	for (size_t col = 0; col < at->size; ++col) {
		if (0 != ((at->table)[(row + col) / 8] & (0x80 >> ((row + col) % 8))) && col != row) {
			(at->table)[(row + col) / 8] &= (~0x80u >> ((row + col) % 8));
			--(at->enterCount[col]);
		}
	}
}

#if 1
static void reverse(char* str, size_t size) {
	size_t i = 0;
	while (i < size / 2) {
		char c = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = c;
		++i;
	}
}

static size_t writeUIntToBuf(unsigned int a, char* buffer) {
	int i = 0;
	do {
		buffer[i] = (a % 10) + '0';
		a /= 10;
		++i;
	} while (a > 0);
	reverse(buffer, i);
	return i;
}
#endif

int topSortAT(AdjTable* at, char* buf) {
	size_t passedCount = 0;
	for (size_t count = 0; count < at->size; ++count) {
		for (size_t i = 0; i < at->size; ++i) {
			if (at->enterCount[i] == 0 && at->passed[i] == NOT_PASSED) {
				at->passed[i] = PASSED;
				buf += writeUIntToBuf(i + 1, buf);
				*buf = ' ';
				++buf;
				++passedCount;
				deleteNode(at, i);
				break;
			}
		}
		if (passedCount != count + 1) {
			puts("impossible to sort");
			return 0;
		}
	}
	*buf = 0;
	return 1;
}
