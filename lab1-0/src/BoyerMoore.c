#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoyerMoore.h"

int readNextPart(char* part, unsigned int partLen, unsigned int maxLen, unsigned int overlap) {
	size_t i = 0;
	unsigned int count = maxLen;
	if (partLen > overlap) {
		unsigned int j = 0;
		while (j < overlap) {
			part[j] = part[partLen - overlap + j];
			++j;
		}
		i = j;
		count = maxLen - overlap;
		return fread(part + i, sizeof(char), count, stdin) + overlap;
	}
	else
		return fread(part, sizeof(char), count, stdin);
}

typedef struct {
	const char* sample;
	unsigned int len;
	unsigned int shift[256];
} BMSearchState;

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
		shift[str[i]] = len - i - 1;
		++i;
	}
}

static inline unsigned int localIdx(unsigned int globalIdx, unsigned int overlap) {
	return globalIdx < TEXTBUFFER_LEN ? globalIdx : (globalIdx - TEXTBUFFER_LEN) % (TEXTBUFFER_LEN - overlap) + overlap;
}

unsigned int findSubString(const char* sample, const char* text, unsigned int textLen, unsigned int startPos) {
	BMSearchState state;
	strToSearchState(sample, &state);
	unsigned int globalIdx = startPos;
	unsigned int sampleIdx = localIdx(globalIdx, state.len - 1);
	sampleIdx = sampleIdx >= state.len - 1 ? sampleIdx : state.len - 1;
	while (sampleIdx < textLen) {
		unsigned int i = 0;
		while (i < state.len) {
			printf("%d ", globalIdx - i + 1);
			if (!(text[sampleIdx - i] == sample[state.len - i - 1]))
				break;
			++i;
		}
		if (i == state.len) {
			sampleIdx += state.len;
			globalIdx += state.len;
		}
		else {
			globalIdx += state.shift[text[sampleIdx]];
			sampleIdx += state.shift[text[sampleIdx]];
		}
	}
	return globalIdx;
}
