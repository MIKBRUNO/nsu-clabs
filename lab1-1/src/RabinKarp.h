#pragma once
#include <stdlib.h>
#define TEMPLATE_LEN 16
#define BUFFER_SIZE 4096

typedef struct Template_s Template;
struct Template_s {
	const char* string;
	size_t len;
	size_t hash;
};
extern void createTemplate(Template* t, const char* string, const size_t size);

extern size_t searchTemplate(
	const Template* template,
	const char* text, size_t textSize,
	size_t idx);
