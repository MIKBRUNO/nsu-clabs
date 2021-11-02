#pragma once

enum {
	SAMPLE_LEN = 16,
	TEXTBUFFER_LEN = 128
};

typedef struct {
	const char* sample;
	unsigned int len;
	unsigned int shift[256];
} BMSearchState;

extern unsigned int findSubString(const BMSearchState* state, const char* text, unsigned int textLen, unsigned int startPos);
extern unsigned int readNextPart(char* part, unsigned int partLen, unsigned int maxLen, unsigned int overlap);
extern void strToSearchState(const char* str, BMSearchState* state);
