#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "BigFloat.h"
#include "badInputAssert.h"

static unsigned int charToDigit(unsigned int c) {
	c = tolower(c);
	if (isdigit(c))
		c = 0 + (c - '0');
	else if (isalpha(c))
		c = 10 + (c - 'a');
	else {
		assert(0);
	}
	return c;
}

static char digitToChar(unsigned int d) {
	if (d < 10)
		return '0' + (char)d;
	else {
		return (char)(d - 10) + 'a';
	}
}

static void reverseString(char* str, unsigned int len) {
	unsigned int i = 0;
	while (i < len / 2) {
		unsigned int c = str[i] + str[(len - 1) - i];
		str[i] = str[(len - 1) - i];
		str[(len - 1) - i] = (char)c - str[i];
		++i;
	}
}

void reprToValue(BigFloat* res, char* repr, unsigned int base) {
	unsigned int len = strlen(repr);
	assert((base <= 16) && (base >= 2) && (len <= 13) && (len >= 1));
	BigFloat number = { 0, 0 };
	unsigned int i = 0;
	while ((i < len) && (repr[i] != '.')) {
		unsigned int digit = charToDigit(repr[i]);
		assert(digit < base);
		number.integer *= base;
		number.integer += digit;
		++i;
	}
	assert(i > 0);  // intLen > 0 (intLen == i)
	if (repr[i] == '.') {
		++i;
		unsigned int fractionalLen = len - i;
		assert(fractionalLen > 0);
		while (i < len) {
			number.fractional *= base;
			unsigned int digit = charToDigit(repr[i]);
			assert(digit < base);
			number.fractional += digit;
			++i;
		}
		number.fractional = number.fractional / pow(base, fractionalLen);
	}
	*res = number;
}

void valueToRepr(char* res, BigFloat *value, unsigned int base) {
	assert((base <= 16) && (base >= 2));
	unsigned long long integer = value -> integer;
	double fractional = value -> fractional;
	unsigned int i = 0;
	do {
		res[i] = digitToChar(integer % base);
		integer /= base;
		++i;
	} while (integer > 0);
	unsigned int intLen = i;
	reverseString(res, intLen);
	if (fractional != 0.) {
		res[i] = '.';
		while ((fractional > 0) && ((i - intLen) <= 12)) {
			++i;
			fractional *= base;
			unsigned int digit = (unsigned int)fractional;
			fractional -= digit;
			res[i] = digitToChar(digit);
		}
		while (res[i] == '0')
			--i;
		++i;
	}
	res[i] = '\0';
}
