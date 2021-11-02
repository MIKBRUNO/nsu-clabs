#pragma once

enum {
	SAMPLE_LEN = 16,
	TEXTBUFFER_LEN = 128
};

extern unsigned int findSubString(const char* sample, const char* text, unsigned int textLen, unsigned int startPos);
extern int readNextPart(char* part, unsigned int partLen, unsigned int maxLen, unsigned int overlap);
