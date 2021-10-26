#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BoyerMoore.h"

int main(void) {
    char sample[SAMPLE_LEN + 2] = "";
    fgets(sample, SAMPLE_LEN + 2, stdin);
    unsigned int sampleLen = strlen(sample) - 1;
    sample[sampleLen] = 0;

    char textPart[TEXTBUFFER_LEN] = "";
    unsigned int startPos = sampleLen - 1;
    unsigned int textLen = 0;
    do {
        textLen = readNextPart(textPart, textLen, TEXTBUFFER_LEN, SAMPLE_LEN - 1);
        startPos = findSubString(sample, textPart, textLen, startPos);
    } while (textLen == TEXTBUFFER_LEN);
    return EXIT_SUCCESS;
}
