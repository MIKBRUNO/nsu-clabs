#pragma once
#include <stdio.h>

#define BUFSIZE 4096  // >= 320

void encode(FILE* out, FILE* in,  int arg);

void decode(FILE* out, FILE* in, int arg);
