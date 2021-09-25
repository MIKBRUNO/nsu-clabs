#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "baseConversion.h"
#include "badInputAssert.h"

int main(int argc, char* argv[]) {
    unsigned b1 = 0;
    unsigned b2 = 0;
    char str[14];
    char* repr = str;
    if (4 == argc) {
        b1 = atoi(argv[1]);
        b2 = atoi(argv[2]);
        repr = argv[3];
    }
    else {
        assert(scanf("%ud", &b1));
        assert(scanf("%ud", &b2));
        assert(scanf("%s", repr));
    }
    BigFloat value;
    reprToValue(&value, repr, b1);
    char res[128];
    valueToRepr(res, &value, b2);
    printf("%s", res);

    return EXIT_SUCCESS;
}
