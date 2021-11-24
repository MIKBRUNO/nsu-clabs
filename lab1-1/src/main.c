#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "RabinKarp.h"

int main(void) {
	char tmplStr[TEMPLATE_LEN + 2];
	if (!fgets(tmplStr, TEMPLATE_LEN + 2, stdin))
		return 0;
	size_t tmplSize = strlen(tmplStr) - 1;
	tmplStr[tmplSize] = 0;
	Template template;
	createTemplate(&template, tmplStr, tmplSize, hash);

	char buf[BUFFER_SIZE];
	size_t textSize = fread(buf, 1, BUFFER_SIZE, stdin);
	printf("%u ", (unsigned int)template.hash);
	size_t idx = 0;
	idx = searchTemplate(&template, buf, textSize, idx, hash);
	while (BUFFER_SIZE == textSize) {
		memcpy(buf, buf + textSize - template.len + 1, template.len - 1);
		textSize = fread(buf + template.len - 1, 1, textSize - template.len + 1, stdin) + template.len - 1;
		idx = searchTemplate(&template, buf, textSize, idx, hash);
	};

	return 0;
}