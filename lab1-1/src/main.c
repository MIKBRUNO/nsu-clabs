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
	createTemplate(&template, tmplStr, tmplSize);

	char buf[BUFFER_SIZE];
	size_t textSize = fread(buf, 1, BUFFER_SIZE, stdin);
	printf("%u ", (unsigned int)template.hash);
	size_t idx = 0;
	idx = searchTemplate(&template, buf, textSize, idx);
	while (BUFFER_SIZE == textSize) {
		memcpy(buf, buf + textSize - tmplSize + 1, tmplSize - 1);
		textSize = fread(buf + tmplSize - 1, 1, textSize - tmplSize + 1, stdin) + tmplSize - 1;
		idx = searchTemplate(&template, buf, textSize, idx);
	};

	return 0;
}
