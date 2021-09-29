#pragma once

typedef struct BigFloat BigFloat;

struct BigFloat {
	unsigned long long integer;
	double fractional;
};
