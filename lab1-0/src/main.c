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
    sample[strlen(sample) - 1] = 0;
    BMSearchState state;
    strToSearchState(sample, &state);

    char textPart[TEXTBUFFER_LEN] = "";
    unsigned int startPos = 0;
    unsigned int textLen = 0;
    unsigned int shift = 0;
    do {
        textLen = readNextPart(textPart, textLen, textLen - shift);
        shift = findSubString(&state, textPart, textLen, startPos);
        startPos += shift;
    } while (textLen == TEXTBUFFER_LEN);
    return EXIT_SUCCESS;
}
