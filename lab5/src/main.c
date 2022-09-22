#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Archiver.h"

int main(int argc, char** argv) {
	FILE* in,
		* out;
	if (3 <= argc) {
		out = fopen(argv[1], "wb");
		in = fopen(argv[2], "rb");
	}
	else {
		out = fopen("./out.txt", "wb");
		in = fopen("./in.txt", "rb");
	}

	int mode;
	if (argc == 4) {
		mode = argv[3][0];
	}
	else {
		mode = fgetc(in);
		if (EOF == mode) {
			fputs("bad input", out);
			fclose(in);
			fclose(out);
			return 0;
		}
	}

	if ('c' == mode) {
		encode(out, in, argc);
	}
	else if ('d' == mode) {
		decode(out, in, argc);
	}
	fclose(in);
	fclose(out);
	return 0;
}
