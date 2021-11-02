#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoyerMoore.h"

unsigned int readNextPart(char* part, unsigned int partLen, unsigned int maxLen, unsigned int overlap) {
	unsigned int count = maxLen;
	if (partLen > overlap) {
		size_t j = 0;
		while (j < overlap) {
			part[j] = part[partLen - overlap + j];
			++j;
		}
		count = maxLen - overlap;
		return fread(part + j, sizeof(char), count, stdin) + overlap;
	}
	else
		return fread(part, sizeof(char), count, stdin);
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
		shift[(int)(str[i])] = len - i - 1;
		++i;
	}
}

static inline unsigned int localIdx(unsigned int globalIdx, unsigned int overlap) {
	return globalIdx < TEXTBUFFER_LEN ? globalIdx : (globalIdx - TEXTBUFFER_LEN) % (TEXTBUFFER_LEN - overlap) + overlap;
}

unsigned int findSubString(const BMSearchState* sampleState, const char* text, unsigned int textLen, unsigned int startPos) {
	BMSearchState state = *sampleState;
	unsigned int globalIdx = startPos;
	unsigned int sampleIdx = localIdx(globalIdx, state.len - 1);
	sampleIdx = sampleIdx >= state.len - 1 ? sampleIdx : state.len - 1;
	while (sampleIdx < textLen) {
		unsigned int i = 0;
		while (i < state.len) {
			printf("%u ", globalIdx - i + 1u);
			if (!(text[sampleIdx - i] == state.sample[state.len - i - 1]))
				break;
			++i;
		}
		if (i == state.len) {
			sampleIdx += state.len;
			globalIdx += state.len;
		}
		else {
			globalIdx += state.shift[(int)(text[sampleIdx])];
			sampleIdx += state.shift[(int)(text[sampleIdx])];
		}
	}
	return globalIdx;
}
