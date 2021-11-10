#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoyerMoore.h"

unsigned int readNextPart(char* part, unsigned int partLen, unsigned int overlap) {
	if (partLen > overlap) {
		memcpy(part, part + partLen - overlap, overlap);
		return fread(part + overlap, sizeof(char), TEXTBUFFER_LEN - overlap, stdin) + overlap;
	}
	else
		return fread(part, sizeof(char), TEXTBUFFER_LEN, stdin);
}

void strToSearchState(const char* str, BMSearchState* state) {
	state->sample = str;
	unsigned int len = strlen(str);
	state->len = len;
	unsigned int* shift = state->shift;
	unsigned int i = 0;
	while (i < 256) {
		shift[i] = len;
		++i;
	}
	i = 0;
	while (i < len - 1) {
		shift[(unsigned char)(str[i])] = len - i - 1;
		++i;
	}
}

static inline unsigned int localIdx(unsigned int globalIdx, unsigned int overlap) {
	return globalIdx < TEXTBUFFER_LEN ? globalIdx : (globalIdx - TEXTBUFFER_LEN) % (TEXTBUFFER_LEN - overlap) + overlap;
}

static char* utoa10(unsigned int u, char* buf) {
	int i = 0;
	buf[9] = 0;
	while (u > 0) {
		buf[8 - i] = '0' + (u % 10);
		u /= 10;
		++i;
	}
	return buf + 9 - i;
}

unsigned int findSubString(const BMSearchState* state, const char* text, unsigned int textLen, unsigned int startPos) {
	unsigned int sampleIdx = state->len - 1;
	unsigned int shift = 0;
	while (sampleIdx < textLen) {
		unsigned int i = 0;
		while (i < state->len) {
			char buf[10];
			fputs(utoa10(sampleIdx + startPos - i + 1, buf), stdout);
			fputs(" ", stdout);
			if (!(text[sampleIdx - i] == state->sample[state->len - i - 1]))
				break;
			++i;
		}
		if (i == state->len) {
			shift = state->len;
			sampleIdx += shift;
		}
		else {
			shift = state->shift[(unsigned char)(text[sampleIdx])];
			sampleIdx += shift;
		}
	}
	return sampleIdx + 1 - state->len;
}
