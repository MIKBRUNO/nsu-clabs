#include <ctype.h>
#include <stdlib.h>
#include "BigFloat.h"
#include "badInputAssert.h"

static int charToDigit(int c) {
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

static char digitToChar(char d) {
	if (d < 10)
		return '0' + d;
	else {
		return (d - 10) + 'a';
	}
}

static void swap(char* pa, char* pb) {
	char a = *pa;
	char b = *pb;
	char c = a + b;
	a = c - a;
	b = c - a;
	*pa = a;
	*pb = b;
}

static unsigned stringLen(char* str) {
	unsigned i = 0;
	while (str[i] != '\0')
		++i;
	return i;
}

static void reverseString(char* arr, unsigned len) {
	unsigned i = 0;
	while (i < len / 2) {
		swap(&(arr[i]), &(arr[(len - 1) - i]));
		++i;
	}
}

static double power(double a, int p) {
	double res = 1;
	if (p >= 0) {
		int i = 0;
		while (i < p) {
			res *= a;
			++i;
		}
	}
	else {
		p = abs(p);
		int i = 0;
		while (i < p) {
			res /= a;
			++i;
		}
	}
	return res;
}

void reprToValue(BigFloat* res, char* repr, unsigned base) {
	unsigned len = stringLen(repr);
	assert((base <= 16) && (base >= 2) && (len <= 13) && (len >= 1));
	BigFloat number = { 0, 0 };
	unsigned i = 0;
	while ((i < len) && (repr[i] != '.')) {
		unsigned digit = charToDigit(repr[i]);
		assert(digit < base);
		number.integer *= base;
		number.integer += digit;
		++i;
	}
	assert(i > 0);  // intLen > 0 (intLen == i)
	if (repr[i] == '.') {
		++i;
		unsigned fractionalLen = len - i;
		assert(fractionalLen > 0);
		while (i < len) {
			number.fractional *= base;
			unsigned digit = charToDigit(repr[i]);
			assert(digit < base);
			number.fractional += digit;
			++i;
		}
		number.fractional = number.fractional / power(base, fractionalLen);
	}
	*res = number;
}

void valueToRepr(char* repr, BigFloat *value, unsigned base) {
	assert((base <= 16) && (base >= 2));
	unsigned long long integer = value -> integer;
	double fractional = value -> fractional;
	unsigned i = 0;
	do {
		repr[i] = digitToChar((char)(integer % base));
		integer /= base;
		++i;
	} while (integer > 0);
	unsigned intLen = i;
	reverseString(repr, intLen);
	if (fractional != 0.) {
		repr[i] = '.';
		while ((fractional > 0) && ((i - intLen) <= 12)) {
			++i;
			fractional *= base;
			unsigned digit = (int)fractional;
			fractional -= digit;
			repr[i] = digitToChar((char)digit);
		}
		while (repr[i] == '0')
			--i;
		++i;
	}
	repr[i] = '\0';
}