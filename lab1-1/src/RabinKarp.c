#include "RabinKarp.h"
#include <string.h>
#include <stdio.h>

void createTemplate(Template* t, const char* string, const size_t size, size_t(*hash)(const char* str, const size_t size)) {
	t->string = string;
	t->len = size;
	t->hash = hash(string, t->len);
}

static size_t powu(size_t base, size_t exp) {
	size_t res = 1;
	while (exp > 0) {
		if (exp & 1)
			res *= base;
		exp >>= 1;
		base *= base;
	}
	return res;
}

size_t hash(const char* str, const size_t size) {
	size_t i = 0u;
	size_t h = 0u;
	while (i < size) {
		h += (str[i] % 3u) * (powu(3u, i));
		++i;
	}
	return h;
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
					const char* text, size_t textSize, size_t idx,
					size_t(*hash)(const char* str, const size_t size)
) {
	size_t i = 0;
	size_t j = 0;
	char buf[16];
	while (i + template->len - 1 < textSize) {
		if (hash(text + i, template->len) == template->hash) {
			j = 0;
			while (j < template->len) {
				fputs(utoa10(idx + i + j + 1u, buf), stdout);
				if (template->string[j] != text[i + j])
					break;
				++j;
			}
		}
		++i;
	}
	return idx + i;
}
