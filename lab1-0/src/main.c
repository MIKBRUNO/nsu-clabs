#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    unsigned int textLen = fread(&textPart, sizeof(char), TEXTBUFFER_LEN, stdin);
    unsigned int startPos = findSubString(&state, textPart, textLen, sampleLen - 1);
    while (textLen == TEXTBUFFER_LEN) {
        textLen = readNextPart(textPart, TEXTBUFFER_LEN, SAMPLE_LEN - 1);
        startPos = findSubString(&state, textPart, textLen, startPos);
    }
    return EXIT_SUCCESS;
}
