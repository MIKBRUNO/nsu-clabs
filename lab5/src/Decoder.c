#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Archiver.h"

static size_t decodeTree(unsigned char* buffer, size_t* bytep, size_t bitp, Node** cur) {
	*cur = malloc(sizeof(Node));
	if (NULL == *cur)
		exit(0);
	(*cur)->link[0] = NULL;
	(*cur)->link[1] = NULL;
	if (buffer[*bytep] & (0x80 >> bitp)) {
		*bytep += (bitp + 1) / 8;
		bitp = (bitp + 1) % 8;
		bitp = decodeTree(buffer, bytep, bitp, &(*cur)->link[0]);
		bitp = decodeTree(buffer, bytep, bitp, &(*cur)->link[1]);
	}
	else {
		*bytep += (bitp + 1) / 8;
		bitp = (bitp + 1) % 8;
		(*cur)->value = buffer[*bytep] << bitp;
		++(*bytep);
		(*cur)->value += buffer[*bytep] >> (8 - bitp);
	}
	return bitp;
}

static unsigned int readIntBytes(FILE* in) {
	unsigned char buf[4];
	if (fread(buf, 1, 4, in))
		exit(0);
	unsigned int res = 0;
	res += (unsigned int)buf[0] << 24;
	res += (unsigned int)buf[1] << 16;
	res += (unsigned int)buf[2] << 8;
	res += buf[3];
	return res;
}

void decode(FILE* out, FILE* in, int arg) {
	fseek(in, (4 == arg) ? 0 : 1, SEEK_SET);
	unsigned int count = readIntBytes(in);
	
	if (0 == count) {
		exit(0);
	}
	
	unsigned char buffer[BUFSIZE];
	size_t len = fread(buffer, 1, BUFSIZE, in);  // max tree space ~ 320B;
	Node* tree = NULL;
	size_t bytep = 0;
	unsigned char mask = 0x80 >> decodeTree(buffer, &bytep, 0, &tree);
	memmove(buffer, buffer + bytep, len - bytep);
	if (BUFSIZE == len)
		len = BUFSIZE - bytep + fread(buffer + BUFSIZE - bytep, 1, bytep, in);
	bytep = 0;
	unsigned char outbuffer[BUFSIZE];
	memset(outbuffer, 0, BUFSIZE);
	for (size_t i = 0; i < count; ++i) {
		if ((0 == i % BUFSIZE) && (0 < i)) {
			fwrite(outbuffer, 1, BUFSIZE, out);
			memset(outbuffer, 0, BUFSIZE);
		}
		Node* cur = tree;
		while (NULL != cur->link[0]) {
			if (bytep == len) {
				len = fread(buffer, 1, BUFSIZE, in);
				bytep = 0;
			}
			cur = cur->link[(buffer[bytep] & mask) ? 1 : 0];
			mask >>= 1;
			if (0 == mask) {
				++bytep;
				mask = 0x80;
			}
		}
		outbuffer[i % BUFSIZE] = cur->value;
	}
	if ((0 == count % BUFSIZE) && (0 < count))
		fwrite(outbuffer, 1, BUFSIZE, out);
	else
		fwrite(outbuffer, 1, count % BUFSIZE, out);
}