#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Archiver.h"
#include "Huffman.h"

typedef struct Data_st Data;
struct Data_st {
	FILE* out;
	char** codes;
	char* currentCode;
	size_t codeIdx;
	unsigned char* buf;
	size_t bitp;
	size_t bytep;
};

typedef struct Freq_st Freq;
struct Freq_st {
	unsigned int table[256];
	unsigned int count;
};

static unsigned int getFreq(Freq* freq, FILE* in) {
	unsigned char buffer[BUFSIZE];
	unsigned int count = 0;
	size_t len = 0;
	do {
		len = fread(buffer, 1, BUFSIZE, in);
		for (size_t i = 0; i < len; ++i) {
			freq->count += (0 == freq->table[buffer[i]]) ? 1 : 0;
			++freq->table[buffer[i]];
		}
		count += len;
	} while (BUFSIZE == len);
	return count;
}

static void onNode(Data* dt) {
	dt->buf[dt->bytep] |= 0x80u >> dt->bitp;
	dt->bytep += (dt->bitp + 1) / 8;
	dt->bitp = (dt->bitp + 1) % 8;

	dt->currentCode[dt->codeIdx] = '0';
	dt->currentCode[dt->codeIdx + 1] = 0;
	++(dt->codeIdx);
}

static void onLeaf(Data* dt, const Node* cur) {
	dt->bytep += (dt->bitp + 1) / 8;
	dt->bitp = (dt->bitp + 1) % 8;	// writing 0
	dt->buf[dt->bytep] |= cur->value >> dt->bitp;	// writing first part of value
	++dt->bytep;
	dt->buf[dt->bytep] = cur->value << (8 - dt->bitp);  // writing second part of byte

	dt->codes[cur->value] = malloc(dt->codeIdx + 1);
	if (NULL == dt->codes[cur->value])
		exit(0);
	memmove(dt->codes[cur->value], dt->currentCode, dt->codeIdx + 1);
	size_t i = 0;
	while (dt->currentCode[dt->codeIdx - i] != '0' && (0 < dt->codeIdx - i))
		++i;
	if ('0' == dt->currentCode[dt->codeIdx - i]) {
		dt->currentCode[dt->codeIdx - i] = '1';
		dt->currentCode[dt->codeIdx - i + 1] = 0;
		dt->codeIdx -= i - 1;
	}
}

static void encodeMessage(FILE* out, FILE* in, char** codes, unsigned char* obuf, size_t bp) {
	unsigned char	ibuf[BUFSIZE];
	size_t	len = 0;
	do {
		len = fread(ibuf, 1, BUFSIZE, in);
		for (size_t i = 0; i < len; ++i) {
			char* code = codes[ibuf[i]];
			size_t sym = 0;
			while (code[sym] != 0) {
				if ('1' == code[sym])
					obuf[bp / 8] |= 0x80u >> (bp % 8);
				++bp;
				++sym;
				if (BUFSIZE * 8 == bp) {
					bp = 0;
					fwrite(obuf, 1, BUFSIZE, out);
					memset(obuf, 0, BUFSIZE);
				}
			}
		}
	} while (BUFSIZE == len);
	fwrite(obuf, 1, (bp / 8), out);
	if (0 != bp % 8)
		fputc(obuf[bp / 8], out);
}

static void encodeFile(FILE* out, FILE* in, Node* tree, unsigned int count, int arg) {
	Data data;
	unsigned char buf[BUFSIZE];  // max tree space ~ 320B; 
	memset(buf, 0, BUFSIZE);
	data.buf = buf;
	data.out = out;
	data.bitp = 0;
	data.bytep = 0;
	
	char* codes[256];
	data.codes = codes;
	memset(data.codes, 0, sizeof(size_t) * 256);
	data.codeIdx = 0;
	data.currentCode = malloc(count);
	if (NULL == data.currentCode) {
		exit(0);
	}
	*data.currentCode = 0;
	
	treeTraversal(tree, &data, onNode, onLeaf); // tree encoding + codes table
	fwrite(data.buf, 1, data.bytep, out);
	memmove(buf, buf + data.bytep, BUFSIZE - data.bytep);
	memset(buf + BUFSIZE - data.bytep, 0, data.bytep);
	free(data.currentCode);

	fseek(in, (4 == arg) ? 0 : 1, SEEK_SET); // arg == argc from main; arg - global var
	encodeMessage(out, in, codes, buf, data.bitp);

	for (size_t i = 0; i < 256; ++i)
		free(data.codes[i]);  // NULL ptr will do nothing
}

void encode(FILE* out, FILE* in, int arg) {
	Freq freq;
	freq.count = 0;
	memset(freq.table, 0, sizeof(unsigned int) * 256);
	unsigned int count = getFreq(&freq, in);
	fwrite(&count, sizeof(unsigned int), 1, out);
	Node* place = malloc(sizeof(Node) * (freq.count * 2 - 1));
	if (NULL == place)
		exit(0);
	Node* tree = createTree(place, freq.table, freq.count);
	
	encodeFile(out, in, tree, freq.count, arg);

	free(place);
}
