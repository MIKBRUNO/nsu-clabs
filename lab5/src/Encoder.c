#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Archiver.h"

typedef struct Freq_st Freq;
struct Freq_st {
	unsigned int table[256];
	unsigned int count;
};

static Node* createTree(Node* elem, unsigned int* freq, unsigned int count) {
	Node** list;
	if (!(list = malloc(count * sizeof(Node*))))
		exit(0);
	*list = NULL;
	for (size_t i = 0; i < count; ++i) {
		elem->link[0] = NULL;
		elem->link[1] = NULL;
		elem->freq = 0;
		for (size_t j = 0; j < 256; ++j) {
			if (freq[j] && (!elem->freq || freq[j] >= elem->freq)) {
				elem->freq = freq[j];
				elem->value = (unsigned char)j;
				list[i] = elem;
			}
		}
		freq[elem->value] = 0;
		++elem;
	}
	for (size_t i = count - 1; i > 0; --i) {
		elem->link[0] = list[i];
		elem->link[1] = list[i - 1];
		elem->freq = list[i]->freq + list[i - 1]->freq;
		list[i - 1] = elem;
		list[i] = NULL;
		size_t j = i - 1;
		while ((j != 0) && (list[j]->freq > list[j - 1]->freq)) {
			Node* t = list[j - 1];
			list[j - 1] = list[j];
			list[j] = t;
			--j;
		}
		++elem;
	}
	Node* tree = list[0];
	free(list);
	return tree;
}

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

static void encodeMessage(FILE* out, FILE* in, char* codes[256], unsigned char obuf[BUFSIZE], size_t bp) {
	unsigned char ibuf[BUFSIZE];
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

static void createCodes(char* codes[256], char* curCode, Node* curNode, size_t depth) {
	if (NULL == curNode)
		return;
	if (NULL == curNode->link[0]) {
		codes[curNode->value] = malloc(depth + 1);
		if (NULL == codes[curNode->value])
			exit(0);
		memmove(codes[curNode->value], curCode, depth + 1);
	}
	else {
		curCode[depth] = '0';
		curCode[depth + 1] = 0;
		createCodes(codes, curCode, curNode->link[0], depth + 1);
		curCode[depth] = '1';
		curCode[depth + 1] = 0;
		createCodes(codes, curCode, curNode->link[1], depth + 1);
	}
}

static void encodeTree(unsigned char buf[BUFSIZE], Node* curNode, size_t* bytep, size_t* bitp) {
	if (NULL == curNode)
		return;
	if (NULL == curNode->link[0]) {
		*bytep += (*bitp + 1) / 8;
		*bitp = (*bitp + 1) % 8;	// writing 0
		buf[*bytep] |= curNode->value >> *bitp;	// writing first part of value
		++(*bytep);
		buf[*bytep] = curNode->value << (8 - *bitp);  // writing second part of byte
	}
	else {
		buf[*bytep] |= 0x80u >> *bitp;
		*bytep += (*bitp + 1) / 8;
		*bitp = (*bitp + 1) % 8;
		encodeTree(buf, curNode->link[0], bytep, bitp);
		encodeTree(buf, curNode->link[1], bytep, bitp);
	}
}

static void encodeFile(FILE* out, FILE* in, Node* tree, unsigned int count, int arg) {
	char* codes[256];
	memset(codes, 0, sizeof(size_t) * 256);
	char* currentCode = malloc(count);
	if (NULL == currentCode) {
		exit(0);
	}
	*currentCode = 0;
	createCodes(codes, currentCode, tree, 0);
	size_t bytep = 0,
			bitp = 0;
	free(currentCode);

	unsigned char buf[BUFSIZE];  // max tree space ~ 320B; 
	memset(buf, 0, BUFSIZE);
	encodeTree(buf, tree, &bytep, &bitp);
	fwrite(buf, 1, bytep, out);
	memmove(buf, buf + bytep, BUFSIZE - bytep);
	memset(buf + BUFSIZE - bytep, 0, bytep);

	fseek(in, (4 == arg) ? 0 : 1, SEEK_SET); // arg == argc from main; arg - global var
	encodeMessage(out, in, codes, buf, bitp);

	for (size_t i = 0; i < 256; ++i)
		free(codes[i]);  // NULL ptr will do nothing
}

static void writeIntBytes(unsigned int a, FILE* out) {
	unsigned char buf[4];
	buf[0] = (unsigned char)(a >> 24);
	buf[1] = (unsigned char)(a >> 16);
	buf[2] = (unsigned char)(a >> 8);
	buf[3] = (unsigned char)a;
	fwrite(buf, 1, 4, out);
}

void encode(FILE* out, FILE* in, int arg) {
	Freq freq;
	freq.count = 0;
	memset(freq.table, 0, sizeof(unsigned int) * 256);
	unsigned int count = getFreq(&freq, in);
	writeIntBytes(count, out);
	
	Node* place = malloc(sizeof(Node) * (freq.count * 2 - 1));
	if (NULL == place)
		exit(0);
	Node* tree = createTree(place, freq.table, freq.count);
	
	encodeFile(out, in, tree, freq.count, arg);

	free(place);
}
