#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "BoyerMoore.h"

int main(void) {
    char sample[SAMPLE_LEN + 2] = "";
    if (!fgets(sample, SAMPLE_LEN + 2, stdin))
        return EXIT_SUCCESS;
    unsigned int sampleLen = strlen(sample) - 1;
    sample[sampleLen] = 0;
    BMSearchState state;
    strToSearchState(sample, &state);

    char textPart[TEXTBUFFER_LEN] = "";
    unsigned int startPos = sampleLen - 1;
    unsigned int textLen = 0;
    do {
        textLen = readNextPart(textPart, textLen, TEXTBUFFER_LEN, SAMPLE_LEN - 1);
        startPos = findSubString(&state, textPart, textLen, startPos);
    } while (textLen == TEXTBUFFER_LEN);
    return EXIT_SUCCESS;
}
