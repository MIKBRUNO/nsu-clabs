#pragma once

#define	SAMPLE_LEN  16u
#define	TEXTBUFFER_LEN 1024u

typedef struct BMSearchState_s BMSearchState;
struct BMSearchState_s {
	const char* sample;
	unsigned int len;
	unsigned int shift[256];
};

extern unsigned int findSubString(const BMSearchState* state, const char* text, unsigned int textLen, unsigned int startPos);
extern unsigned int readNextPart(char* part, unsigned int partLen, unsigned int overlap);
extern void strToSearchState(const char* str, BMSearchState* state);
