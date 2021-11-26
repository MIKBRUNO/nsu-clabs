#include "RabinKarp.h"
#include <string.h>
#include <stdio.h>

static inline size_t powu(size_t base, size_t exp) {
	size_t res = 1;
	while (exp > 0) {
		if (exp & 1)
			res *= base;
		exp >>= 1;
		base *= base;
	}
	return res;
}

static inline size_t hash(const char* str, const size_t size) {
	size_t i = 0u;
	size_t h = 0u;
	while (i < size) {
		h += ((unsigned int)str[i] % 3u) * (powu(3u, i));
		++i;
	}
	return h;
}

void createTemplate(Template* t, const char* string, const size_t size) {
	t->string = string;
	t->len = size;
	t->hash = hash(string, t->len);
}

static char* utoa10(size_t u, char* buf) {
	size_t i = 0u;
	buf[9] = ' ';
	buf[10] = 0;
	while (u > 0) {
		buf[8 - i] = '0' + (u % 10);
		u /= 10;
		++i;
	}
	return buf + 9 - i;
}

size_t searchTemplate(
					const Template* template,
					const char* text, size_t textSize, size_t idx
) {
	size_t i = 0;
	size_t h = hash(text + i, template->len - 1);
	size_t three = powu(3, template->len - 1);
	char buf[16];
	while (i + template->len - 1 < textSize) {
		h += ((unsigned int)text[i + template->len - 1] % 3) * three;
		if (h == template->hash) {
			size_t j = 0;
			fputs(utoa10(idx + i + j + 1u, buf), stdout);
			while ((j < template->len - 1) && (template->string[j] == text[i + j])) {
				++j;
				fputs(utoa10(idx + i + j + 1u, buf), stdout);
			}
		}
		h -= (unsigned int)text[i] % 3;
		h /= 3;
		++i;
	}
	return idx + i;
}
